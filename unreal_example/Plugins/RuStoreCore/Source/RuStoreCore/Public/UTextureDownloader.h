// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/Texture2D.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UTextureDownloader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompleteTextureDownloadOutputPin, UTexture2D*, texture2D);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFailureTextureDownloadOutputPin);

UCLASS()
class RUSTORECORE_API UTextureDownloader : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

private:
    void Start(const FString url, UTextureDownloader* object);
    UTexture2D* DownloadImageAsTexture2D(FString url);

public:
    UPROPERTY(BlueprintAssignable)
    FCompleteTextureDownloadOutputPin Complete;

    UPROPERTY(BlueprintAssignable)
    FFailureTextureDownloadOutputPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Texture Downloader")
    static UTextureDownloader* DownloadImage(FString url);
};
