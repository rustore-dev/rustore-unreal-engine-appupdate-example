// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallStatus.generated.h"

UENUM(BlueprintType)
enum class EURuStoreInstallStatus : uint8
{
    UNKNOWN UMETA(DisplayName = "UNKNOWN"),
    DOWNLOADED UMETA(DisplayName = "DOWNLOADED"),
    DOWNLOADING UMETA(DisplayName = "DOWNLOADING"),
    FAILED UMETA(DisplayName = "FAILED"),
    INSTALLING UMETA(DisplayName = "INSTALLING"),
    PENDING UMETA(DisplayName = "PENDING")
};
