// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallErrorCode.generated.h"

UENUM(BlueprintType)
enum class EURuStoreInstallErrorCode : uint8
{
    ERROR_UNKNOWN UMETA(DisplayName = "ERROR_UNKNOWN"),//4001
    ERROR_DOWNLOAD UMETA(DisplayName = "ERROR_DOWNLOAD"),
    ERROR_BLOCKED UMETA(DisplayName = "ERROR_BLOCKED"),
    ERROR_INVALID_APK UMETA(DisplayName = "ERROR_INVALID_APK"),
    ERROR_CONFLICT UMETA(DisplayName = "ERROR_CONFLICT"),
    ERROR_STORAGE UMETA(DisplayName = "ERROR_STORAGE"),
    ERROR_INCOMPATIBLE UMETA(DisplayName = "ERROR_INCOMPATIBLE"),
    ERROR_APP_NOT_OWNED UMETA(DisplayName = "ERROR_APP_NOT_OWNED"),
    ERROR_INTERNAL_ERROR UMETA(DisplayName = "ERROR_INTERNAL_ERROR"),
    ERROR_ABORTED UMETA(DisplayName = "ERROR_ABORTED"),
    ERROR_APK_NOT_FOUND UMETA(DisplayName = "ERROR_APK_NOT_FOUND"),
    ERROR_EXTERNAL_SOURCE_DENIED UMETA(DisplayName = "ERROR_EXTERNAL_SOURCE_DENIED"),
};
