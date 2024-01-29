// Copyright Epic Games, Inc. All Rights Reserved.

#include "UpdateFlowResultListenerImpl.h"

using namespace RuStoreSDK;

int UpdateFlowResultListenerImpl::ConvertResponse(int response)
{
    return response + 1;
}

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
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_appupdate_wrappers_UpdateFlowResultListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<UpdateFlowResultListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_appupdate_wrappers_UpdateFlowResultListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jint result)
    {
        auto castobj = reinterpret_cast<UpdateFlowResultListenerImpl*>(pointer);
        castobj->OnSuccess((int)result);
    }
}
#endif
