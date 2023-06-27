#pragma once

#include "CoreMinimal.h"
#include "EUUpdateFlowResult.generated.h"

UENUM(BlueprintType)
enum class EUUpdateFlowResult : uint8
{
    RESULT_OK UMETA(DisplayName = "RESULT_OK"),
    RESULT_CANCELED UMETA(DisplayName = "RESULT_CANCELED")
};
