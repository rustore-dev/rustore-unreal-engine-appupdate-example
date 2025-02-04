// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EURuStoreAppUpdateOptions.generated.h"

/*!
@brief Тип процедуры обновления.
*/
UENUM(BlueprintType)
enum class EURuStoreAppUpdateOptions : uint8
{
    DELAYED UMETA(DisplayName = "DELAYED"),
    
    /*!
    @brief
        Тихое обновление.
        UI-диалог обновления не будет показан.
        В случае успешного обновления приложение будет закрыто.
    */
    SILENT UMETA(DisplayName = "SILENT"),
    
    /*!
    @brief Принудительное обновление.
    */
    IMMEDIATE UMETA(DisplayName = "IMMEDIATE"),
    
    /*!
    @brief
        Гибкое обновление.
        Пользователю будет показан UI-диалог обновления.
        В случае успешного обновления приложение будет перезапущено.
    */
    FLEXIBLE UMETA(DisplayName = "FLEXIBLE")
};
