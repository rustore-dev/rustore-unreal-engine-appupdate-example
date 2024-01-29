// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaActivity.h"

using namespace RuStoreSDK;

JavaActivity::JavaActivity()
{
#if PLATFORM_ANDROID
    activity = FJavaWrapper::GameActivityThis;
#endif
}

JavaActivity::~JavaActivity()
{
}

FString JavaActivity::GetName()
{
    return "android/app/Activity";
}

#if PLATFORM_ANDROID
jobject JavaActivity::GetJObject()
{
    return activity;
}
#endif
