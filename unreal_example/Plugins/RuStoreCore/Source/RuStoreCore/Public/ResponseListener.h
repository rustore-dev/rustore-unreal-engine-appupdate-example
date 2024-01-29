// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ErrorListener.h"

namespace RuStoreSDK
{
    template<typename T>
    class ResponseListener : public ErrorListener
    {
    private:
        TFunction<void(long requestId, TSharedPtr<T, ESPMode::ThreadSafe>)> _onSuccess;

    protected:
        ResponseListener(
            FString className,
            FString interfaceName,
            TFunction<void(long requestId, TSharedPtr<T, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ErrorListener(className, interfaceName, onFailure, onFinish)
        {
            _onSuccess = onSuccess;
        }

        virtual ~ResponseListener() { }

        virtual T* ConvertResponse(AndroidJavaObject* responseObject) = 0;

    public:
        void OnSuccess(AndroidJavaObject* responseObject)
        {
            auto response = TSharedPtr<T, ESPMode::ThreadSafe>(ConvertResponse(responseObject));
            delete responseObject;

            auto listener = GetWeakPtr();
            CallbackHandler::AddCallback([this, listener, response]() {
                if (listener.IsValid())
                {
                    this->_onSuccess(this->GetId(), response);
                    this->_onFinish(this);
                }
            });
        }
    };
}
