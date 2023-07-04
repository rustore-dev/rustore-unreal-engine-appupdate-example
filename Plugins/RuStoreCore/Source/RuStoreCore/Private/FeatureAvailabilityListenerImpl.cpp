// Copyright Epic Games, Inc. All Rights Reserved.

#include "FeatureAvailabilityListenerImpl.h"

using namespace RuStoreSDK;

FeatureAvailabilityListenerImpl::~FeatureAvailabilityListenerImpl()
{
    FString tag = "rustore_debug";
    FString msg = "~FeatureAvailabilityListenerImpl";
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*msg));
#endif
}

FURuStoreFeatureAvailabilityResult* FeatureAvailabilityListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
{
    FString resultType = "";

    AndroidJavaObject* javaClassObject = responseObject->CallAJClass("getClass");

    FString str = javaClassObject->CallFString("getName");
    TArray<FString> _className;
    str.ParseIntoArray(_className, TEXT("$"), true);
    if (_className.Num() > 0) resultType = _className.Last();

    delete javaClassObject;

    auto response = new FURuStoreFeatureAvailabilityResult();

    if (resultType == "Unavailable")
    {
        response->isAvailable = false;

        auto causeObject = responseObject->GetAJObject("cause", "Lru/rustore/sdk/core/exception/RuStoreException;");

        response->cause.name = causeObject->CallJavaClassFString("getSimpleName");
        response->cause.description = causeObject->CallFString("getMessage");
    }
    else
    {
        if (resultType == "Available")
        {
            response->isAvailable = true;
        }
        else
        {
            response->isAvailable = false;
            response->cause.name = "Error";
            response->cause.description = "Invalid response type";
        }
    }

    return response;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreCore_FeatureAvailabilityListenerWrapper_NativeOnFailure(JNIEnv* env, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<FeatureAvailabilityListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreCore_FeatureAvailabilityListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<FeatureAvailabilityListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
