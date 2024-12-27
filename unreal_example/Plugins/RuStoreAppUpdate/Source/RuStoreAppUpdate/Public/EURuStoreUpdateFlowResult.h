// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreUpdateFlowResult.generated.h"

/*!
@brief Информация о результате обновления.
*/
UENUM(BlueprintType)
enum class EURuStoreUpdateFlowResult : uint8
{
    /*!
    @brief Обновление выполнено, код может не быть получен, т. к. приложение в момент обновления завершается.
    */
    RESULT_OK UMETA(DisplayName = "RESULT_OK"),
    
    /*!
    @brief
        Флоу прервано пользователем, или произошла ошибка.
        Предполагается, что при получении этого кода следует завершить работу приложения.
    */
    RESULT_CANCELED UMETA(DisplayName = "RESULT_CANCELED"),
    
    /*!
    @brief RuStore не установлен, либо установлена версия, которая не поддерживает принудительное обновление (RuStore versionCode < 191).
    */
    ACTIVITY_NOT_FOUND UMETA(DisplayName = "ACTIVITY_NOT_FOUND")
};
