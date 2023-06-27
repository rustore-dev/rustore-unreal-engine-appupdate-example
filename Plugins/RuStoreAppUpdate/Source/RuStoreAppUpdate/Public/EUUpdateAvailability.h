#pragma once

#include "CoreMinimal.h"
#include "EUUpdateAvailability.generated.h"

UENUM(BlueprintType)
enum class EUUpdateAvailability : uint8
{
    UNKNOWN UMETA(DisplayName = "UNKNOWN"),
    UPDATE_NOT_AVAILABLE UMETA(DisplayName = "UPDATE_NOT_AVAILABLE"),
    UPDATE_AVAILABLE UMETA(DisplayName = "UPDATE_AVAILABLE"),
    DEVELOPER_TRIGGERED_UPDATE_IN_PROGRESS UMETA(DisplayName = "DEVELOPER_TRIGGERED_UPDATE_IN_PROGRESS")
};
