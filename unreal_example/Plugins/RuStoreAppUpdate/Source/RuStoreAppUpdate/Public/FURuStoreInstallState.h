// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreInstallStatus.h"
#include "EURuStoreInstallErrorCode.h"
#include "FURuStoreInstallState.generated.h"

/*!
@brief Описывает текущее состояние установки обновления.
*/
USTRUCT(BlueprintType)
struct RUSTOREAPPUPDATE_API FURuStoreInstallState
{
    GENERATED_USTRUCT_BODY()
    
    /*!
    @brief Конструктор.
    */
    FURuStoreInstallState()
    {
        bytesDownloaded = 0;
        totalBytesToDownload = 0;
        percentDownloaded = 0;
        installStatus = EURuStoreInstallStatus::UNKNOWN;
        installErrorCode = EURuStoreInstallErrorCode::ERROR_UNKNOWN;
    }

    /*!
    @brief Количество загруженных байт.
    */
    UPROPERTY(BlueprintReadWrite)
    int64 bytesDownloaded;

    /*!
    @brief Общее количество байт, которое необходимо скачать.
    */
    UPROPERTY(BlueprintReadWrite)
    int64 totalBytesToDownload;

    /*!
    @brief Процент загрузки.
    */
    UPROPERTY(BlueprintReadWrite)
    float percentDownloaded;

    /*!
    @brief Статус установки обновления, если пользователь уже устанавливает обновление в текущий момент времени.
    */
    UPROPERTY(BlueprintReadWrite)
    EURuStoreInstallStatus installStatus;

    /*!
    @brief Код ошибки во время скачивания обновления.
    */
    UPROPERTY(BlueprintReadWrite)
    EURuStoreInstallErrorCode installErrorCode;
};
