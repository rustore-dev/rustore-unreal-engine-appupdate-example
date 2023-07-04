// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#if PLATFORM_ANDROID
#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#include <jni.h>
#endif

namespace RuStoreSDK
{
    class IAndroidClasses
    {
    public:
        virtual FString GetName() = 0;

#if PLATFORM_ANDROID
        virtual jobject GetJObject() = 0;
#endif
    };
}
