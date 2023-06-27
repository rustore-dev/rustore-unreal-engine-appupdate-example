#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"
#include "UObject/ScriptMacros.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include <functional>

#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "FUAppUpdateInfo.h"
#include "EUUpdateFlowResult.h"
#include "InstallStateUpdateListener.h"
#include "RuStoreListener.h"
#include "URuStoreAppUpdateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAppUpdateInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAppUpdateInfoResponseDelegate, int64, requestId, FUAppUpdateInfo, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartUpdateFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartUpdateFlowResponseDelegate, int64, requestId, EUUpdateFlowResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCompleteUpdateErrorDelegate, int64, requestId, FURuStoreError, error);

UCLASS(Blueprintable)
class RUSTOREAPPUPDATE_API URuStoreAppUpdateManager : public UObject, public IInstallStateUpdateListener, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreAppUpdateManager* _instance;
    static bool _isInstanceInitialized;

    bool _allowNativeErrorHandling;

    AndroidJavaObject* _clientWrapper = nullptr;

    TMap<IInstallStateUpdateListener*, InstallStateUpdateListener*> stateListeners;

public:
    static const FString PluginVersion;

    UPROPERTY(BlueprintReadOnly, Category = "RuStore AppUpdate Manager")
    bool isInitialized;

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    static URuStoreAppUpdateManager* Instance();

    void SetAllowNativeErrorHandling(bool value);

    URuStoreAppUpdateManager();
    ~URuStoreAppUpdateManager();

    void BeginDestroy();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void Dispose();

    // IInstallStateUpdateListener
    void OnStateUpdated(FUInstallState state) override;

    long GetAppUpdateInfo(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUAppUpdateInfo*)> onSuccess);
    bool RegisterListener(IInstallStateUpdateListener* listener);
    bool UnregisterListener(IInstallStateUpdateListener* listener);
    long StartUpdateFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, EUUpdateFlowResult)> onSuccess);
    long CompleteUpdate(TFunction<void(long, FURuStoreError*)> onFailure);


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void GetAppUpdateInfo(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FGetAppUpdateInfoErrorDelegate OnGetAppUpdateInfoError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FGetAppUpdateInfoResponseDelegate OnGetAppUpdateInfoResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void StartUpdateFlow(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FStartUpdateFlowErrorDelegate OnStartUpdateFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FStartUpdateFlowResponseDelegate OnStartUpdateFlowResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void CompleteUpdate(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FCompleteUpdateErrorDelegate OnCompleteUpdateError;
};
