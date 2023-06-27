#pragma once

#include "CoreMinimal.h"
#include "EUInstallStatus.generated.h"

UENUM(BlueprintType)
enum class EUInstallStatus : uint8
{
    UNKNOWN UMETA(DisplayName = "UNKNOWN"),
    DOWNLOADED UMETA(DisplayName = "DOWNLOADED"),
    DOWNLOADING UMETA(DisplayName = "DOWNLOADING"),
    FAILED UMETA(DisplayName = "FAILED"),
    INSTALLING UMETA(DisplayName = "INSTALLING"),
    PENDING UMETA(DisplayName = "PENDING")
};
