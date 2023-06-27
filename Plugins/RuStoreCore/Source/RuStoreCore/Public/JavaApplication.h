#pragma once

#include "CoreMinimal.h"

#if PLATFORM_ANDROID
#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#include <jni.h>
#endif

#include "IAndroidClasses.h"

class RUSTORECORE_API JavaApplication : public IAndroidClasses
{
#if PLATFORM_ANDROID
private:
    jobject application;
#endif

public:
    JavaApplication();
    virtual ~JavaApplication();

    FString GetName() override;

#if PLATFORM_ANDROID
    jobject GetJObject() override;
#endif
};
