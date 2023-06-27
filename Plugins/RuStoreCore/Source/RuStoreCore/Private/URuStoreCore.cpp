#include "URuStoreCore.h"
#include "AndroidJavaClass.h"
#include <memory>

using namespace std;

URuStoreCore* URuStoreCore::_instance = nullptr;
bool URuStoreCore::_isInstanceInitialized = false;

bool URuStoreCore::getIsInitialized() { return isInitialized; }

URuStoreCore* URuStoreCore::Instance()
{
    if (!_isInstanceInitialized)
    {
        _isInstanceInitialized = true;
        _instance = NewObject<URuStoreCore>(GetTransientPackage());
    }
    return _instance;
}

URuStoreCore::URuStoreCore()
{
}

URuStoreCore::~URuStoreCore()
{
}

bool URuStoreCore::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (isInitialized) return false;

    _instance->AddToRoot();

    unrealPlayer = new UnrealPlayerImpl();

    auto clientJavaClass = make_shared<AndroidJavaClass>("ru/rustore/unitysdk/core/PlayerProvider");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("setExternalProvider", unrealPlayer->GetPlayer());

    isInitialized = true;

    return isInitialized;
}

void URuStoreCore::Dispose()
{
    if (isInitialized)
    {
        isInitialized = false;
        delete unrealPlayer;
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreCore::BeginDestroy()
{
    Super::BeginDestroy();

    LogInfo("rustore", "RuStore Core begin destroy");

    Dispose();
    if (_isInstanceInitialized) _isInstanceInitialized = false;
}

bool URuStoreCore::IsPlatformSupported()
{
#if PLATFORM_ANDROID
    return true;
#endif
    return false;
}

bool URuStoreCore::IsPlatformSupported(TFunction<void(long requestId, FURuStoreError*)> onFailure)
{
    if (IsPlatformSupported()) return true;

    FURuStoreError* error = new FURuStoreError();
    error->name = "RuStore Error";
    error->description = "Unsupported platform";
    
    onFailure(-1, error);
    
    return false;
}

void URuStoreCore::ShowToast(FString message)
{
    auto javaClass = make_shared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto activity = make_shared<JavaActivity>();

    javaClass->CallStaticVoid("showToast", activity.get(), message);
}

void URuStoreCore::LogInfo(FString tag, FString message)
{
#if PLATFORM_ANDROID
	__android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

bool URuStoreCore::CompareId(int64 A, int64 B)
{
    return (A == B && A != 0);
}
