// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreAppUpdateOptions.generated.h"

UENUM(BlueprintType)
enum class EURuStoreAppUpdateOptions : uint8
{
    DELAYED UMETA(DisplayName = "DELAYED"),
    SILENT UMETA(DisplayName = "SILENT"),
    IMMEDIATE UMETA(DisplayName = "IMMEDIATE"),
    FLEXIBLE UMETA(DisplayName = "FLEXIBLE")
};
