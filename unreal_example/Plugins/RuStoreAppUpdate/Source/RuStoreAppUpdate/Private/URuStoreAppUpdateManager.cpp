// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreAppUpdateManager.h"
#include "AppUpdateInfoResponseListenerImpl.h"
#include "UpdateFlowResultListenerImpl.h"
#include "AppUpdateErrorListenerImpl.h"
#include "URuStoreCore.h"

using namespace RuStoreSDK;

const FString URuStoreAppUpdateManager::PluginVersion = "1.0";
URuStoreAppUpdateManager* URuStoreAppUpdateManager::_instance = nullptr;
bool URuStoreAppUpdateManager::_bIsInstanceInitialized = false;

bool URuStoreAppUpdateManager::GetIsInitialized()
{
    return bIsInitialized;
}

URuStoreAppUpdateManager* URuStoreAppUpdateManager::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreAppUpdateManager>(GetTransientPackage());
    }
    return _instance;
}

void URuStoreAppUpdateManager::SetAllowNativeErrorHandling(bool value)
{
    _bAllowNativeErrorHandling = value;

    if (bIsInitialized)
    {
        _clientWrapper->CallVoid("setErrorHandling", value);
    }
}

bool URuStoreAppUpdateManager::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/appupdate/RuStoreUnityAppUpdateManager");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init", FString("unreal"));

    bIsInitialized = true;

    RegisterListener(this);

    return true;
}

void URuStoreAppUpdateManager::Dispose()
{
    if (bIsInitialized)
    {
        UnregisterListener(this);

        bIsInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreAppUpdateManager::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

long URuStoreAppUpdateManager::GetAppUpdateInfo(TFunction<void(long, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new AppUpdateInfoResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("getAppUpdateInfo", listener->GetJWrapper());

    return listener->GetId();
}

bool URuStoreAppUpdateManager::CheckIsImmediateUpdateAllowed()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (!bIsInitialized) return false;

    return _clientWrapper->CallBool("isImmediateUpdateAllowed");
}

int64 URuStoreAppUpdateManager::RegisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener)
{
    if (!URuStoreCore::IsPlatformSupported()) return 0;
    if (!bIsInitialized) return 0;

    if (!stateListeners.Contains(stateListener.GetInterface()))
    {
        auto listener = ListenerBind(new InstallStateUpdateListenerImpl(
            [stateListener](long listenerId, TSharedPtr<FURuStoreInstallState, ESPMode::ThreadSafe> state) {
                ((IRuStoreInstallStateUpdateListenerInterface*)stateListener.GetInterface())->OnStateUpdated_Implementation(listenerId, *state);
            }
        ));

        stateListeners.Add(stateListener.GetInterface(), listener);

        _clientWrapper->CallVoid("registerListener", listener->GetJWrapper());

        return listener->GetId();
    }

    return 0;
}

bool URuStoreAppUpdateManager::UnregisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (!bIsInitialized) return false;

    if (stateListeners.Contains(stateListener.GetInterface()))
    {
        auto listener = stateListeners[stateListener.GetInterface()];
        _clientWrapper->CallVoid("unregisterListener", listener->GetJWrapper());

        ListenerUnbind(listener);

        return true;
    }

    return false;
}

long URuStoreAppUpdateManager::StartUpdateFlow(EURuStoreAppUpdateOptions appUpdateOptions, TFunction<void(long, EURuStoreUpdateFlowResult)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto _onSuccess = [onSuccess](long requestId, int result) { onSuccess(requestId, (EURuStoreUpdateFlowResult)(result)); };

    auto listener = ListenerBind(new UpdateFlowResultListenerImpl(_onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));

    switch (appUpdateOptions)
    {
    case EURuStoreAppUpdateOptions::DELAYED:
        _clientWrapper->CallVoid("startUpdateFlowDelayed", listener->GetJWrapper());
        break;
    case EURuStoreAppUpdateOptions::SILENT:
        _clientWrapper->CallVoid("startUpdateFlowSilent", listener->GetJWrapper());
        break;
    case EURuStoreAppUpdateOptions::IMMEDIATE:
        _clientWrapper->CallVoid("startUpdateFlowImmediate", listener->GetJWrapper());
        break;
    default:
        _clientWrapper->CallVoid("startUpdateFlowDelayed", listener->GetJWrapper());
    }

    return listener->GetId();
}

long URuStoreAppUpdateManager::CompleteUpdate(EURuStoreAppUpdateOptions appUpdateOptions, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new AppUpdateErrorListenerImpl(onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));

    switch (appUpdateOptions)
    {
    case EURuStoreAppUpdateOptions::FLEXIBLE:
        _clientWrapper->CallVoid("completeUpdateFlexible", listener->GetJWrapper());
        break;
    case EURuStoreAppUpdateOptions::SILENT:
        _clientWrapper->CallVoid("completeUpdateSilent", listener->GetJWrapper());
        break;
    default:
        _clientWrapper->CallVoid("completeUpdateFlexible", listener->GetJWrapper());
    }

    return listener->GetId();
}

void URuStoreAppUpdateManager::GetAppUpdateInfo(int64& requestId)
{
    requestId = GetAppUpdateInfo(
        [this](long requestId, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe> response) {
            OnGetAppUpdateInfoResponse.Broadcast(requestId, *response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnGetAppUpdateInfoError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreAppUpdateManager::StartUpdateFlow(int64& requestId, EURuStoreAppUpdateOptions appUpdateOptions)
{
    requestId = StartUpdateFlow(
        appUpdateOptions,
        [this](long requestId, EURuStoreUpdateFlowResult response) {
            OnStartUpdateFlowResponse.Broadcast(requestId, response);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnStartUpdateFlowError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreAppUpdateManager::CompleteUpdate(int64& requestId, EURuStoreAppUpdateOptions appUpdateOptions)
{
    requestId = CompleteUpdate(
        appUpdateOptions,
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnCompleteUpdateError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreAppUpdateManager::OnStateUpdated_Implementation(int64 listenerId, FURuStoreInstallState& state)
{
    OnStateUpdatedInstanceEvent.Broadcast(listenerId, state);
}
