// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreUpdateAvailability.generated.h"

/*!
@brief Доступность обновления.
*/
UENUM(BlueprintType)
enum class EURuStoreUpdateAvailability : uint8
{
    /*!
    @brief Значение по умолчанию.
    */
    UNKNOWN UMETA(DisplayName = "UNKNOWN"),

    /*!
    @brief Обновление не требуется.
    */
    UPDATE_NOT_AVAILABLE UMETA(DisplayName = "UPDATE_NOT_AVAILABLE"),
    
    /*!
    @brief Обновление требуется загрузить или обновление уже загружено на устройство пользователя.
    */
    UPDATE_AVAILABLE UMETA(DisplayName = "UPDATE_AVAILABLE"),
    
    /*!
    @brief Обновление уже скачивается или установка уже запущена.
    */
    DEVELOPER_TRIGGERED_UPDATE_IN_PROGRESS UMETA(DisplayName = "DEVELOPER_TRIGGERED_UPDATE_IN_PROGRESS")
};
