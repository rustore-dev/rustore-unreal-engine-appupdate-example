#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"
#include "UObject/ScriptMacros.h"
#include <functional>

#include "UnrealPlayerImpl.h"
#include "FURuStoreError.h"
#include "URuStoreCore.generated.h"

UCLASS(Blueprintable)
class RUSTORECORE_API URuStoreCore : public UObject
{
	GENERATED_BODY()

private:
	static URuStoreCore* _instance;
	static bool _isInstanceInitialized;

	AndroidJavaObject* _clientWrapper = nullptr;
	UnrealPlayerImpl* unrealPlayer = nullptr;

	bool isInitialized = false;

public:
	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	bool getIsInitialized();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static URuStoreCore* Instance();

	static bool IsPlatformSupported();
	static bool IsPlatformSupported(TFunction<void(long requestId, FURuStoreError*)> onFailure);

	URuStoreCore();
	~URuStoreCore();

	void BeginDestroy();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	void Dispose();

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void ShowToast(FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static void LogInfo(FString tag, FString message);

	UFUNCTION(BlueprintCallable, Category = "RuStore Core")
	static bool CompareId(int64 A, int64 B);
};
