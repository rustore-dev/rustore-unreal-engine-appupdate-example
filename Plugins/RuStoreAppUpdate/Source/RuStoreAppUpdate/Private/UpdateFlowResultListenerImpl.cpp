#include "UpdateFlowResultListenerImpl.h"

FURuStoreError* UpdateFlowResultListenerImpl::ConvertError(AndroidJavaObject* errorObject)
{
    auto error = SimpleResponseListenerT::ConvertError(errorObject);

    if (error->name == "RuStoreInstallException")
    {
        auto errorCode = errorObject->GetInt("code");
        error->description = FString::FromInt(errorCode);
    }

    return error;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_UpdateFlowResultListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto castobj = reinterpret_cast<SimpleResponseListenerT<int>*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_UpdateFlowResultListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jint result)
    {
        auto castobj = reinterpret_cast<SimpleResponseListenerT<int>*>(pointer);
        castobj->OnSuccess((int)result);
    }
}
#endif
