// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreUpdateFlowResult.generated.h"

UENUM(BlueprintType)
enum class EURuStoreUpdateFlowResult : uint8
{
    RESULT_OK UMETA(DisplayName = "RESULT_OK"),
    RESULT_CANCELED UMETA(DisplayName = "RESULT_CANCELED"),
    ACTIVITY_NOT_FOUND UMETA(DisplayName = "ACTIVITY_NOT_FOUND")
};
