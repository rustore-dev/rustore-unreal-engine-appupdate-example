// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.generated.h"

/*!
@brief Информация об ошибке.
*/
USTRUCT(BlueprintType)
struct RUSTORECORE_API FURuStoreError
{
	GENERATED_USTRUCT_BODY()

	/*!
	@brief Конструктор.
	*/
	FURuStoreError()
	{
		name = "";
		description = "";
	}

	/*!
	@brief
		Название ошибки.
		Содержит имя simpleName класса ошибки.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString name;

	/*!
	@brief Сообщение ошибки.
	*/
	UPROPERTY(BlueprintReadOnly)
	FString description;
};
