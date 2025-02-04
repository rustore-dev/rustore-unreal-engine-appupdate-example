// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FURuStoreInstallState.h"
#include "URuStoreInstallStateUpdateListenerInterface.generated.h"

/*!
@brief Класс-адаптер для использования интерфейса IRuStoreLogListenerInterface в Blueprints.
*/
UINTERFACE(Blueprintable)
class RUSTOREAPPUPDATE_API URuStoreInstallStateUpdateListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/*!
@brief Интерфейс слушателя колбэков установки обновления.
*/
class IRuStoreInstallStateUpdateListenerInterface
{
	GENERATED_BODY()

public:
	/*!
	@brief Обработчик колбэка установки обновления.
	@param listenerId ID слушателя.
	@param state Объект, описывающий текущий статус установки обновления.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore InstallStateUpdate Listener Interface")
	void OnStateUpdated(int64 listenerId, FURuStoreInstallState& state);
};
