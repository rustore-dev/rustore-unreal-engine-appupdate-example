// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"
#include "FURuStoreError.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API ErrorConverter
    {
    public:
        static FURuStoreError* Convert(AndroidJavaObject* errorObject);
    };
}
