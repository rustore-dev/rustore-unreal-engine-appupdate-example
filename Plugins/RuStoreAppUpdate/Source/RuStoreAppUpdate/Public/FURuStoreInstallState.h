// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallStatus.h"
#include "EURuStoreInstallErrorCode.h"
#include "FURuStoreInstallState.generated.h"

USTRUCT(BlueprintType)
struct RUSTOREAPPUPDATE_API FURuStoreInstallState
{
    GENERATED_USTRUCT_BODY()
    
    FURuStoreInstallState()
    {
        bytesDownloaded = 0;
        totalBytesToDownload = 0;
        percentDownloaded = 0;
        installStatus = EURuStoreInstallStatus::UNKNOWN;
        installErrorCode = EURuStoreInstallErrorCode::ERROR_UNKNOWN;
    }

    UPROPERTY(BlueprintReadWrite)
    int64 bytesDownloaded;

    UPROPERTY(BlueprintReadWrite)
    int64 totalBytesToDownload;

    UPROPERTY(BlueprintReadWrite)
    float percentDownloaded;

    UPROPERTY(BlueprintReadWrite)
    EURuStoreInstallStatus installStatus;

    UPROPERTY(BlueprintReadWrite)
    EURuStoreInstallErrorCode installErrorCode;
};
