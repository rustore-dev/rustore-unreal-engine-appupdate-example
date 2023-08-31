// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace RuStoreSDK
{
    void _LogVerbose(FString tag, FString message);
    void _LogDebug(FString tag, FString message);
    void _LogInfo(FString tag, FString message);
    void _LogWarn(FString tag, FString message);
    void _LogError(FString tag, FString message);
}
