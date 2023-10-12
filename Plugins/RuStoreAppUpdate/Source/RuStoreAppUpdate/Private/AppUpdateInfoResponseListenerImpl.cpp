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
    response->availableVersionCode = responseObject->GetInt("availableVersionCode");

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_appupdate_wrappers_AppUpdateInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto castobj = reinterpret_cast<ResponseListener<FURuStoreAppUpdateInfo>*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_appupdate_wrappers_AppUpdateInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<ResponseListener<FURuStoreAppUpdateInfo>*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnSuccess(obj);
    }
}
#endif
