#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.h"
#include "FUFeatureAvailabilityResult.generated.h"

USTRUCT(BlueprintType)
struct RUSTORECORE_API FUFeatureAvailabilityResult
{
	GENERATED_USTRUCT_BODY()

	FUFeatureAvailabilityResult()
	{
		isAvailable = false;
	}

	UPROPERTY(BlueprintReadWrite)
	bool isAvailable;
	
	UPROPERTY(BlueprintReadWrite)
	FURuStoreError cause;
};
