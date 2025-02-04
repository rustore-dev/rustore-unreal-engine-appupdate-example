// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallStatus.generated.h"

/*!
@brief Статус установки обновления, если пользователь уже устанавливает обновление в текущий момент времени.
*/
UENUM(BlueprintType)
enum class EURuStoreInstallStatus : uint8
{
    /*!
    @brief Значение по умолчанию.
    */
    UNKNOWN UMETA(DisplayName = "UNKNOWN"),
    
    /*!
    @brief Скачано.
    */
    DOWNLOADED UMETA(DisplayName = "DOWNLOADED"),
    
    /*!
    @brief Скачивается.
    */
    DOWNLOADING UMETA(DisplayName = "DOWNLOADING"),
    
    /*!
    @brief Ошибка.
    */
    FAILED UMETA(DisplayName = "FAILED"),
    
    /*!
    @brief Установка.
    */
    INSTALLING UMETA(DisplayName = "INSTALLING"),
    
    /*!
    @brief В ожидании.
    */
    PENDING UMETA(DisplayName = "PENDING")
};
