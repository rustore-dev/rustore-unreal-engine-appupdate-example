// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API CallbackHandler
    {
    public:
        static void AddCallback(TFunction<void()> callback);
    };
}
