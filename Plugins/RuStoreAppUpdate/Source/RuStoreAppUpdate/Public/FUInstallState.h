#pragma once

#include "CoreMinimal.h"
#include "EUInstallStatus.h"
#include "EUInstallErrorCode.h"
#include "FUInstallState.generated.h"

USTRUCT(BlueprintType)
struct FUInstallState
{
    GENERATED_USTRUCT_BODY()
    
    FUInstallState()
    {
        bytesDownloaded = 0;
        totalBytesToDownload = 0;
        installStatus = EUInstallStatus::UNKNOWN;
        installErrorCode = EUInstallErrorCode::ERROR_UNKNOWN;
    }

    // long
    UPROPERTY(BlueprintReadWrite)
    int bytesDownloaded;

    // long
    UPROPERTY(BlueprintReadWrite)
    int totalBytesToDownload;

    UPROPERTY(BlueprintReadWrite)
    EUInstallStatus installStatus;

    UPROPERTY(BlueprintReadWrite)
    EUInstallErrorCode installErrorCode;
};
