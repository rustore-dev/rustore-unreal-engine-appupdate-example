// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.h"
#include "FURuStoreFeatureAvailabilityResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTORECORE_API FURuStoreFeatureAvailabilityResult
{
	GENERATED_USTRUCT_BODY()

	FURuStoreFeatureAvailabilityResult()
	{
		isAvailable = false;
	}

	UPROPERTY(BlueprintReadWrite)
	bool isAvailable;
	
	UPROPERTY(BlueprintReadWrite)
	FURuStoreError cause;
};
