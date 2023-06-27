#include "URuStoreAppUpdateManager.h"
#include "AppUpdateInfoResponseListenerImpl.h"
#include "UpdateFlowResultListenerImpl.h"
#include "AppUpdateErrorListenerImpl.h"
#include "URuStoreCore.h"

using namespace std;

const FString URuStoreAppUpdateManager::PluginVersion = "0.1";

URuStoreAppUpdateManager* URuStoreAppUpdateManager::_instance = nullptr;
bool URuStoreAppUpdateManager::_isInstanceInitialized = false;

bool URuStoreAppUpdateManager::getIsInitialized() { return isInitialized; }

URuStoreAppUpdateManager::URuStoreAppUpdateManager()
{
}

URuStoreAppUpdateManager::~URuStoreAppUpdateManager()
{
}

URuStoreAppUpdateManager* URuStoreAppUpdateManager::Instance()
{
    if (!_isInstanceInitialized)
    {
        _isInstanceInitialized = true;
        _instance = NewObject<URuStoreAppUpdateManager>(GetTransientPackage());
    }
    return _instance;
}

void URuStoreAppUpdateManager::SetAllowNativeErrorHandling(bool value)
{
    _allowNativeErrorHandling = value;

    if (isInitialized)
    {
        _clientWrapper->CallVoid("setErrorHandling", value);
    }
}

bool URuStoreAppUpdateManager::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (isInitialized) return false;

    URuStoreCore::Instance()->Init();

    AndroidJavaClass* clientJavaClass = new AndroidJavaClass("ru/rustore/unitysdk/appupdate/RuStoreUnityAppUpdateManager");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init");

    isInitialized = true;

    return isInitialized;
}

void URuStoreAppUpdateManager::Dispose()
{
    if (isInitialized)
    {
        isInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }

    URuStoreCore::LogInfo("rustore_debug", "URuStoreAppUpdateManager Dispose");
}

void URuStoreAppUpdateManager::BeginDestroy()
{
    Super::BeginDestroy();

    URuStoreCore::LogInfo("rustore_debug", "URuStoreAppUpdateManager begin destroy");

    Dispose();
    if (_isInstanceInitialized) _isInstanceInitialized = false;
}

void URuStoreAppUpdateManager::OnStateUpdated(FUInstallState state)
{

}

long URuStoreAppUpdateManager::GetAppUpdateInfo(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, FUAppUpdateInfo*)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new AppUpdateInfoResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("getAppUpdateInfo", listener->GetJWrapper());

    return listener->GetId();
}

bool URuStoreAppUpdateManager::RegisterListener(IInstallStateUpdateListener* listener)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (!isInitialized) return false;

    InstallStateUpdateListener* stateListener = stateListeners.FindRef(listener);
    if (!stateListener)
    {
        stateListener = new InstallStateUpdateListener(listener);
        stateListeners.Add(listener, stateListener);
        _clientWrapper->CallVoid("registerListener", stateListener->jlistener);
        
        return true;
    }

    return false;
}

bool URuStoreAppUpdateManager::UnregisterListener(IInstallStateUpdateListener* listener)
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (!isInitialized) return false;

    InstallStateUpdateListener* stateListener = stateListeners.FindRef(listener);
    if (stateListener)
    {
        auto item = stateListeners[listener];
        _clientWrapper->CallVoid("unregisterListener", item->jlistener);
        stateListeners.Remove(listener);

        return true;
    }

    return false;
}

long URuStoreAppUpdateManager::StartUpdateFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, EUUpdateFlowResult)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new UpdateFlowResultListenerImpl(
        onFailure,
        [this, onSuccess](long requestId, int result) {
            if (onSuccess != nullptr)
            {
                onSuccess(requestId, (EUUpdateFlowResult)(result+1));
            }
        },
        [this](RuStoreListener* item) { ListenerUnbind(item); }
    );
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("startUpdateFlow", listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreAppUpdateManager::CompleteUpdate(TFunction<void(long, FURuStoreError*)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new AppUpdateErrorListenerImpl(onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("completeUpdate", listener->GetJWrapper());

    return listener->GetId();
}

void URuStoreAppUpdateManager::GetAppUpdateInfo(int64& requestId)
{
    requestId = GetAppUpdateInfo(
        [this](long requestId, FURuStoreError* error) {
            OnGetAppUpdateInfoError.Broadcast(requestId, *error);
        },
        [this](long requestId, FUAppUpdateInfo* response) {
            OnGetAppUpdateInfoResponse.Broadcast(requestId, *response);
        }
    );
}

void URuStoreAppUpdateManager::StartUpdateFlow(int64& requestId)
{
    requestId = StartUpdateFlow(
        [this](long requestId, FURuStoreError* error) {
            OnStartUpdateFlowError.Broadcast(requestId, *error);
        },
        [this](long requestId, EUUpdateFlowResult response) {
            OnStartUpdateFlowResponse.Broadcast(requestId, response);
        }
    );
}

void URuStoreAppUpdateManager::CompleteUpdate(int64& requestId)
{
    requestId = CompleteUpdate(
        [this](long requestId, FURuStoreError* error) {
            OnCompleteUpdateError.Broadcast(requestId, *error);
        }
    );
}
