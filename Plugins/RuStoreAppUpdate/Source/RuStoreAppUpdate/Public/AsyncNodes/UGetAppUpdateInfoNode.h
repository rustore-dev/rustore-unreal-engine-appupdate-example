// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreAppUpdateManager.h"
#include "UGetAppUpdateInfoNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAppUpdateInfoPin, FURuStoreAppUpdateInfo, response, FURuStoreError, error);

UCLASS()
class RUSTOREAPPUPDATE_API UGetAppUpdateInfoNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FGetAppUpdateInfoPin Success;

    UPROPERTY(BlueprintAssignable)
    FGetAppUpdateInfoPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore AppUpdate Manager")
    static UGetAppUpdateInfoNode* GetAppUpdateInfoAsync(URuStoreAppUpdateManager* target);
};
