#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.generated.h"

USTRUCT(BlueprintType)
struct RUSTORECORE_API FURuStoreError
{
	GENERATED_USTRUCT_BODY()

	FURuStoreError()
	{
		name = "";
		description = "";
	}

	UPROPERTY(BlueprintReadOnly)
	FString name;

	UPROPERTY(BlueprintReadOnly)
	FString description;
};
