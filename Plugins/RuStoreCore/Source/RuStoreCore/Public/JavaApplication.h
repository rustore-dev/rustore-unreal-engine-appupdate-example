// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAndroidClasses.h"

namespace RuStoreSDK
{
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
}
