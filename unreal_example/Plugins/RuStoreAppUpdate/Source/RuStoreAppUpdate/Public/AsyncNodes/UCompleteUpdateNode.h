// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "EURuStoreAppUpdateOptions.h"
#include "URuStoreAppUpdateManager.h"
#include "UCompleteUpdateNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompleteUpdatePin, FURuStoreError, error);

UCLASS()
class RUSTOREAPPUPDATE_API UCompleteUpdateNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FCompleteUpdatePin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore AppUpdate Manager")
    static UCompleteUpdateNode* CompleteUpdateAsync(URuStoreAppUpdateManager* target, EURuStoreAppUpdateOptions appUpdateOptions);
};
