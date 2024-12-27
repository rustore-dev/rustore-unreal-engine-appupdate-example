// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreUpdateAvailability.h"
#include "EURuStoreInstallStatus.h"
#include "FURuStoreAppUpdateInfo.generated.h"

/*!
@brief Информция о доступном обновлении.
*/
USTRUCT(BlueprintType)
struct RUSTOREAPPUPDATE_API FURuStoreAppUpdateInfo
{
    GENERATED_USTRUCT_BODY()
    
    /*!
    @brief Конструктор.
    */
    FURuStoreAppUpdateInfo()
    {
        updateAvailability = EURuStoreUpdateAvailability::UNKNOWN;
        installStatus = EURuStoreInstallStatus::UNKNOWN;
        availableVersionCode = 0;
    }

    /*!
    @brief Доступность обновления.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStoreUpdateAvailability updateAvailability;
    
    /*!
    @brief Статус установки обновления, если пользователь уже устанавливает обновление в текущий момент времени.
    */
    UPROPERTY(BlueprintReadOnly)
    EURuStoreInstallStatus installStatus;
    
    /*!
    @brief Код версии обновления.
    */
    UPROPERTY(BlueprintReadOnly)
    int64 availableVersionCode;
};
