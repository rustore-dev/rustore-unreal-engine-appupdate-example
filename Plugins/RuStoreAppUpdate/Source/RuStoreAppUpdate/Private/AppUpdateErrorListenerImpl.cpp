// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppUpdateErrorListenerImpl.h"

using namespace RuStoreSDK;

FURuStoreError* AppUpdateErrorListenerImpl::ConvertError(AndroidJavaObject* errorObject)
{
    auto error = ErrorListener::ConvertError(errorObject);

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
    JNIEXPORT void JNICALL Java_ru_rustore_unitysdk_appupdate_wrappers_AppUpdateErrorListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto castobj = reinterpret_cast<ErrorListener*>(pointer);
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();
        castobj->OnFailure(obj);
    }
}
#endif
