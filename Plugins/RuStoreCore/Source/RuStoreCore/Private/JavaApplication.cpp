// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaApplication.h"

using namespace RuStoreSDK;

JavaApplication::JavaApplication()
{
#if PLATFORM_ANDROID
    JNIEnv* env = FAndroidApplication::GetJavaEnv();
    jobject activityInstance = FJavaWrapper::GameActivityThis;
    jclass activityClass = env->GetObjectClass(activityInstance);

    jmethodID getApplicationMethodId = env->GetMethodID(activityClass, "getApplication", "()Landroid/app/Application;");
    application = (jobject)env->CallObjectMethod(activityInstance, getApplicationMethodId);
#endif
}

JavaApplication::~JavaApplication()
{
}

FString JavaApplication::GetName()
{
    return "android/app/Application";
}

#if PLATFORM_ANDROID
jobject JavaApplication::GetJObject()
{
    return application;
}
#endif
