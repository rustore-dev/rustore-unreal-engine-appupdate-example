#pragma once

#include "CoreMinimal.h"
#include "EUUpdateAvailability.h"
#include "EUInstallStatus.h"
#include "FUAppUpdateInfo.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREAPPUPDATE_API FUAppUpdateInfo
{
    GENERATED_USTRUCT_BODY()
    
    FUAppUpdateInfo()
    {
        updateAvailability = EUUpdateAvailability::UNKNOWN;
        installStatus = EUInstallStatus::UNKNOWN;
        availableVersionCode = 0;
    }

    UPROPERTY(BlueprintReadOnly)
    EUUpdateAvailability updateAvailability;
    
    UPROPERTY(BlueprintReadOnly)
    EUInstallStatus installStatus;
    
    UPROPERTY(BlueprintReadOnly)
    int availableVersionCode;
};
