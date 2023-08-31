// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppUpdateInfoResponseListenerImpl.h"

using namespace RuStoreSDK;

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

FURuStoreAppUpdateInfo* AppUpdateInfoResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    auto response = new FURuStoreAppUpdateInfo();

    response->updateAvailability = (EURuStoreUpdateAvailability)responseObject->GetInt("updateAvailability");
    response->installStatus = (EURuStoreInstallStatus)responseObject->GetInt("installStatus");
    response->availableVersionCode = responseObject->GetLong("availableVersionCode");

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_AppUpdateInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<AppUpdateInfoResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_AppUpdateInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<AppUpdateInfoResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
