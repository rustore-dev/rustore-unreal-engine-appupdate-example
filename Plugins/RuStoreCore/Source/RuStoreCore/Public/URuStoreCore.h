// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FURuStoreError.h"
#include "UnrealPlayerImpl.h"
#include "URuStoreCore.generated.h"

using namespace RuStoreSDK;

UCLASS(Blueprintable)
class RUSTORECORE_API URuStoreCore : public UObject
{
	GENERATED_BODY()

private:
	static URuStoreCore* _instance;
	static bool _bIsInstanceInitialized;

	bool bIsInitialized = false;
	AndroidJavaObject* _clientWrapper = nullptr;
	UnrealPlayerImpl* unrealPlayer = nullptr;

public:
	static const FString PluginVersion;

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	bool GetIsInitialized();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static URuStoreCore* Instance();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static bool IsPlatformSupported();
	static bool IsPlatformSupported(TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);

	void ConditionalBeginDestroy();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	void Dispose();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void ShowToast(FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogVerbose(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogDebug(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogInfo(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogWarn(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogError(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static bool CompareId(int64 A, int64 B);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void CopyToClipboard(FString text);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void GetFromClipboard(FString& text);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void GetStringResources(FString name, FString& value);
};
