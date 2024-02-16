// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAndroidClasses.h"

namespace RuStoreSDK
{
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
}
