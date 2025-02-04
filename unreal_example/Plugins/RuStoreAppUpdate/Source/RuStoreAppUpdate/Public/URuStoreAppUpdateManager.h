// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "FURuStoreAppUpdateInfo.h"
#include "EURuStoreAppUpdateOptions.h"
#include "EURuStoreUpdateFlowResult.h"
#include "InstallStateUpdateListenerImpl.h"
#include "RuStoreListener.h"
#include "URuStoreInstallStateUpdateListenerInterface.h"
#include "URuStoreAppUpdateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetAppUpdateInfoErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreGetAppUpdateInfoResponseDelegate, int64, requestId, FURuStoreAppUpdateInfo, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreStartUpdateFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreStartUpdateFlowResponseDelegate, int64, requestId, EURuStoreUpdateFlowResult, response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreCompleteUpdateErrorDelegate, int64, requestId, FURuStoreError, error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRuStoreOnStateUpdatedInstanceDelegate, int64, listenerId, FURuStoreInstallState, state);

using namespace RuStoreSDK;

/*!
@brief
    Класс реализует API для трех способов обновлений.
    В настоящий момент поддерживаются: отложенное, тихое (без UI от RuStore) и принудительное обновление.
*/
UCLASS(Blueprintable)
class RUSTOREAPPUPDATE_API URuStoreAppUpdateManager : public UObject, public IRuStoreInstallStateUpdateListenerInterface, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreAppUpdateManager* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

    TMap<void*, TSharedPtr<RuStoreListener, ESPMode::ThreadSafe>> stateListeners;

public:
    /*!
    @brief Версия плагина.
    */
    static const FString PluginVersion;

    /*!
    @brief Проверка инициализации менеджера.
    @return Возвращает true, если синглтон инициализирован, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool GetIsInitialized();

    /*!
    @brief
        Получить экземпляр URuStoreAppUpdateManager.
    @return
        Возвращает указатель на единственный экземпляр URuStoreAppUpdateManager (реализация паттерна Singleton).
        Если экземпляр еще не создан, создает его.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    static URuStoreAppUpdateManager* Instance();

    /*!
    @brief Обработка ошибок в нативном SDK.
    @param value true — разрешает обработку ошибок, false — запрещает.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void SetAllowNativeErrorHandling(bool value);

    /*!
    @brief Выполняет инициализацию синглтона URuStoreAppUpdateManager.
    @return Возвращает true, если инициализация была успешно выполнена, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool Init();

    /*!
    @brief Деинициализация синглтона, если дальнейшая работа с объектом больше не планируется.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void Dispose();

    void ConditionalBeginDestroy();

    /*!
    @brief Выполняет проверку наличия обновлений.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает requestId типа long и объект FURuStoreAppUpdateInfo с информцаией о необходимости обновления.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long GetAppUpdateInfo(TFunction<void(long, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe>)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Запускает процедуру скачивания обновления приложения.
    @param appUpdateOptions Тип процедуры скачивания обновления.
    @param onSuccess
        Действие, выполняемое при успешном завершении операции.
        Возвращает объект EURuStoreUpdateFlowResult с информацией о результате операции обновления.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long StartUpdateFlow(EURuStoreAppUpdateOptions appUpdateOptions, TFunction<void(long, EURuStoreUpdateFlowResult)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    
    /*!
    @brief Запускает процедуру установки обновления.
    @param appUpdateOptions Тип процедуры завершения обновления.
    @param onFailure
        Действие, выполняемое в случае ошибки.
        Возвращает requestId типа long и объект типа FURuStoreError с информацией об ошибке.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    long CompleteUpdate(EURuStoreAppUpdateOptions appUpdateOptions, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);

    /*!
    @brief Выполняет проверку доступности принудительного обновления.
    @return Возвращает true, если принудительное обновление доступно, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool CheckIsImmediateUpdateAllowed();

    /*!
    @brief Выполняет регистрацию слушателя статуса скачивания обновления.
    @param stateListener Объект класса, реализующего интерфейс IRuStoreInstallStateUpdateListenerInterface.
    @return Возвращает уникальный в рамках одного запуска приложения requestId.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    int64 RegisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener);

    /*!
    @brief
        Если необходимости в слушателе больше нет, воспользуйтесь методом удаления слушателя UnregisterListener(),
        передав в метод ранее зарегистрированный слушатель.
    @param stateListener Объект класса, реализующего интерфейс IRuStoreInstallStateUpdateListenerInterface.
    @return Возвращает true, если переданный слушатель найден в списке слушателей и удалён, в противном случае — false.
    */
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    bool UnregisterListener(TScriptInterface<IRuStoreInstallStateUpdateListenerInterface> stateListener);

    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void GetAppUpdateInfo(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreGetAppUpdateInfoErrorDelegate OnGetAppUpdateInfoError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreGetAppUpdateInfoResponseDelegate OnGetAppUpdateInfoResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void StartUpdateFlow(int64& requestId, EURuStoreAppUpdateOptions appUpdateOptions);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreStartUpdateFlowErrorDelegate OnStartUpdateFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreStartUpdateFlowResponseDelegate OnStartUpdateFlowResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore AppUpdate Manager")
    void CompleteUpdate(int64& requestId, EURuStoreAppUpdateOptions appUpdateOptions);

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreCompleteUpdateErrorDelegate OnCompleteUpdateError;


    // URuStoreInstallStateUpdateListenerInterface
    void OnStateUpdated_Implementation(int64 listenerId, FURuStoreInstallState& state) override;

    UPROPERTY(BlueprintAssignable, Category = "RuStore AppUpdate Manager")
    FRuStoreOnStateUpdatedInstanceDelegate OnStateUpdatedInstanceEvent;
};
