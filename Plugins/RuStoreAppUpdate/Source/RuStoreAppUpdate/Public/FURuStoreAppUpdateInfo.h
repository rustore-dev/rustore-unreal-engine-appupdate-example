// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreUpdateAvailability.h"
#include "EURuStoreInstallStatus.h"
#include "FURuStoreAppUpdateInfo.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREAPPUPDATE_API FURuStoreAppUpdateInfo
{
    GENERATED_USTRUCT_BODY()
    
    FURuStoreAppUpdateInfo()
    {
        updateAvailability = EURuStoreUpdateAvailability::UNKNOWN;
        installStatus = EURuStoreInstallStatus::UNKNOWN;
        availableVersionCode = 0;
    }

    UPROPERTY(BlueprintReadOnly)
    EURuStoreUpdateAvailability updateAvailability;
    
    UPROPERTY(BlueprintReadOnly)
    EURuStoreInstallStatus installStatus;
    
    UPROPERTY(BlueprintReadOnly)
    int availableVersionCode;
};
