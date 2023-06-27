#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#include <jni.h>
#endif

#include "IAndroidClasses.h"

class RUSTORECORE_API JavaActivity : public IAndroidClasses
{
#if PLATFORM_ANDROID
private:
    jobject activity;
#endif

public:
    JavaActivity();
    virtual ~JavaActivity();

    FString GetName() override;

#if PLATFORM_ANDROID
    jobject GetJObject();
#endif
};
