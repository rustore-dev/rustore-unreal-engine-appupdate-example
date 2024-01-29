// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "FURuStoreAppUpdateInfo.h"
#include "EURuStoreAppUpdateOptions.h"
#include "EURuStoreUpdateFlowResult.h"
#include "InstallStateUpdateListenerImpl.h"
#include "RuStoreListener.h"
#include "URuStoreInstallStateUpdateListenerInterface.h"
#include "URuStoreAppUpdateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetAppUpdateInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetAppUpdateInfoResponseDelegate, int64, requestId, FURuStoreAppUpdateInfo, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreStartUpdateFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreStartUpdateFlowResponseDelegate, int64, requestId, EURuStoreUpdateFlowResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCompleteUpdateErrorDelegate, int64, requestId, FURuStoreError, error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreOnStateUpdatedInstanceDelegate, int64, listenerId, FURuStoreInstallState, state);

using namespace RuStoreSDK;

UCLASS(Blueprintable)
class RUSTOREAPPUPDATE_API URuStoreAppUpdateManager : public UObject, public IRuStoreInstallStateUpdateListenerInterface, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreAppUpdateManager* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

    TMap<void*, TSharedPtr<RuStoreListener, ESPMode::ThreadSafe>> stateListeners;

public:
    static const FString PluginVersion;

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    static URuStoreAppUpdateManager* Instance();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void SetAllowNativeErrorHandling(bool value);

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void Dispose();

    void ConditionalBeginDestroy();

    long GetAppUpdateInfo(TFunction<void(long, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long StartUpdateFlow(EURuStoreAppUpdateOptions appUpdateOptions, TFunction<void(long, EURuStoreUpdateFlowResult)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long CompleteUpdate(TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool CheckIsImmediateUpdateAllowed();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    int64 RegisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener);

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool UnregisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener);

    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void GetAppUpdateInfo(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreGetAppUpdateInfoErrorDelegate OnGetAppUpdateInfoError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreGetAppUpdateInfoResponseDelegate OnGetAppUpdateInfoResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void StartUpdateFlow(int64& requestId, EURuStoreAppUpdateOptions appUpdateOptions);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreStartUpdateFlowErrorDelegate OnStartUpdateFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreStartUpdateFlowResponseDelegate OnStartUpdateFlowResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void CompleteUpdate(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreCompleteUpdateErrorDelegate OnCompleteUpdateError;


    // URuStoreInstallStateUpdateListenerInterface
    void OnStateUpdated_Implementation(int64 listenerId, FURuStoreInstallState& state) override;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreOnStateUpdatedInstanceDelegate OnStateUpdatedInstanceEvent;
};
