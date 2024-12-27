// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallErrorCode.generated.h"

/*!
@brief Код ошибки во время скачивания обновления.
*/
UENUM(BlueprintType)
enum class EURuStoreInstallErrorCode : uint8
{
    /*!
    @brief Неизвестная ошибка.
    */
    ERROR_UNKNOWN UMETA(DisplayName = "ERROR_UNKNOWN"),//4001

    /*!
    @brief Ошибка при скачивании.
    */
    ERROR_DOWNLOAD UMETA(DisplayName = "ERROR_DOWNLOAD"),
    
    /*!
    @brief Установка заблокированна системой.
    */
    ERROR_BLOCKED UMETA(DisplayName = "ERROR_BLOCKED"),
    
    /*!
    @brief Некорректный APK обновления.
    */
    ERROR_INVALID_APK UMETA(DisplayName = "ERROR_INVALID_APK"),
    
    /*!
    @brief Конфликт с текущей версией приложения.
    */
    ERROR_CONFLICT UMETA(DisplayName = "ERROR_CONFLICT"),
    
    /*!
    @brief Недостаточно памяти на устройстве.
    */
    ERROR_STORAGE UMETA(DisplayName = "ERROR_STORAGE"),
    
    /*!
    @brief Несовместимо с устройством.
    */
    ERROR_INCOMPATIBLE UMETA(DisplayName = "ERROR_INCOMPATIBLE"),
    
    /*!
    @brief Приложение не куплено.
    */
    ERROR_APP_NOT_OWNED UMETA(DisplayName = "ERROR_APP_NOT_OWNED"),
    
    /*!
    @brief Внутренняя ошибка.
    */
    ERROR_INTERNAL_ERROR UMETA(DisplayName = "ERROR_INTERNAL_ERROR"),
    
    /*!
    @brief Пользователь отказался от установки обновления.
    */
    ERROR_ABORTED UMETA(DisplayName = "ERROR_ABORTED"),
    
    /*!
    @brief APK для запуска установки не найден.
    */
    ERROR_APK_NOT_FOUND UMETA(DisplayName = "ERROR_APK_NOT_FOUND"),
    
    /*!
    @brief Запуск обновления запрещён. Например, в первом методе вернулся ответ о том, что обновление недоступно, но пользователь вызывает второй метод.
    */
    ERROR_EXTERNAL_SOURCE_DENIED UMETA(DisplayName = "ERROR_EXTERNAL_SOURCE_DENIED"),
    
    /*!
    @brief Ошибка отправки intent на открытие активити.
    */
    ERROR_ACTIVITY_SEND_INTENT UMETA(DisplayName = "ERROR_ACTIVITY_SEND_INTENT"),//9901
    
    /*!
    @brief Неизвестная ошибка отрытия активити.
    */
    ERROR_ACTIVITY_UNKNOWN UMETA(DisplayName = "ERROR_ACTIVITY_UNKNOWN"),
};
