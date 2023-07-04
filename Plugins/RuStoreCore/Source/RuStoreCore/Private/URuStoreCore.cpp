// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreCore.h"
#include "AndroidJavaClass.h"

URuStoreCore* URuStoreCore::_instance = nullptr;
bool URuStoreCore::_bIsInstanceInitialized = false;

bool URuStoreCore::getIsInitialized() { return bIsInitialized; }

URuStoreCore* URuStoreCore::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreCore>(GetTransientPackage());
    }
    return _instance;
}

bool URuStoreCore::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    unrealPlayer = new UnrealPlayerImpl();

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/core/PlayerProvider");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("setExternalProvider", unrealPlayer->GetJWrapper());

    bIsInitialized = true;

    return bIsInitialized;
}

void URuStoreCore::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        delete unrealPlayer;
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreCore::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    LogInfo("rustore", "RuStore Core begin destroy");

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

bool URuStoreCore::IsPlatformSupported()
{
#if PLATFORM_ANDROID
    return true;
#endif
    return false;
}

bool URuStoreCore::IsPlatformSupported(TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (IsPlatformSupported()) return true;

    auto error = MakeShared<FURuStoreError, ESPMode::ThreadSafe>();
    error->name = "RuStore Error";
    error->description = "Unsupported platform";
    
    onFailure(0, error);
    
    return false;
}

void URuStoreCore::ShowToast(FString message)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto activity = MakeShared<JavaActivity>();

    javaClass->CallStaticVoid("showToast", &activity.Get(), message);
}

void URuStoreCore::LogVerbose(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_VERBOSE, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void URuStoreCore::LogDebug(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_DEBUG, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void URuStoreCore::LogInfo(FString tag, FString message)
{
#if PLATFORM_ANDROID
	__android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void URuStoreCore::LogWarn(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_WARN, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void URuStoreCore::LogError(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_ERROR, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

bool URuStoreCore::CompareId(int64 A, int64 B)
{
    return (A == B && A != 0);
}
