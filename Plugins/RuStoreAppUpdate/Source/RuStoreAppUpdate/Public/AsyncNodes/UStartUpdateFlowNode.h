// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "EURuStoreAppUpdateOptions.h"
#include "URuStoreAppUpdateManager.h"
#include "UStartUpdateFlowNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartUpdateFlowPin, EURuStoreUpdateFlowResult, response, FURuStoreError, error);

UCLASS()
class RUSTOREAPPUPDATE_API UStartUpdateFlowNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

private:
    static const EURuStoreUpdateFlowResult errorResponse;

public:
    UPROPERTY(BlueprintAssignable)
    FStartUpdateFlowPin Success;

    UPROPERTY(BlueprintAssignable)
    FStartUpdateFlowPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore AppUpdate Manager")
    static UStartUpdateFlowNode* StartUpdateFlowAsync(URuStoreAppUpdateManager* target, EURuStoreAppUpdateOptions appUpdateOptions);
};
