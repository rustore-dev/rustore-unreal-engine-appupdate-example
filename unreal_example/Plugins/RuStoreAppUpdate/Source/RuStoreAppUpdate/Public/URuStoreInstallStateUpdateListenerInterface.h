// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FURuStoreInstallState.h"
#include "URuStoreInstallStateUpdateListenerInterface.generated.h"

UINTERFACE(Blueprintable)
class RUSTOREAPPUPDATE_API URuStoreInstallStateUpdateListenerInterface : public UInterface
{
	GENERATED_BODY()
};

class IRuStoreInstallStateUpdateListenerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "RuStore InstallStateUpdate Listener Interface")
	void OnStateUpdated(int64 listenerId, FURuStoreInstallState& state);
};
