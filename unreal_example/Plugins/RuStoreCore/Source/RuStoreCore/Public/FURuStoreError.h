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

	virtual ~FURuStoreError() {}

	static const FString TypeName;
	virtual FString GetTypeName() { return TypeName; }

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
