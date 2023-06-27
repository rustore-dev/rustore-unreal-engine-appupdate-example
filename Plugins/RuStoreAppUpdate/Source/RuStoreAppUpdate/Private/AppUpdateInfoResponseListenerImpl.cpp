#include "AppUpdateInfoResponseListenerImpl.h"

FURuStoreError* AppUpdateInfoResponseListenerImpl::ConvertError(AndroidJavaObject* errorObject)
{
    auto error = ResponseListener::ConvertError(errorObject);

    if (error->name == "RuStoreInstallException")
    {
        auto errorCode = errorObject->GetInt("code");
        error->description = FString::FromInt(errorCode);
    }

    return error;
}

FUAppUpdateInfo* AppUpdateInfoResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FUAppUpdateInfo();

    response->updateAvailability = (EUUpdateAvailability)responseObject->GetInt("updateAvailability");
    response->installStatus = (EUInstallStatus)responseObject->GetInt("installStatus");
    response->availableVersionCode = responseObject->GetInt("availableVersionCode");

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_AppUpdateInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto castobj = reinterpret_cast<ResponseListener<FUAppUpdateInfo>*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_AppUpdateInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<ResponseListener<FUAppUpdateInfo>*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnSuccess(obj);
    }
}
#endif
