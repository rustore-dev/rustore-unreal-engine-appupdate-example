// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ErrorListener.h"

namespace RuStoreSDK
{
    template <typename T>
    class SimpleResponseListenerT : public ErrorListener
    {
    private:
        TFunction<void(long, T)> _onSuccess;

    protected:
        SimpleResponseListenerT(
            FString className,
            FString interfaceName,
            TFunction<void(long, T)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ErrorListener(className, interfaceName, onFailure, onFinish)
        {
            _onSuccess = onSuccess;
        }

        virtual ~SimpleResponseListenerT() { }

        virtual T ConvertResponse(T response)
        {
            return response;
        }

    public:
        void OnSuccess(T response)
        {
            auto _response = ConvertResponse(response);

            auto listener = GetWeakPtr();
            CallbackHandler::AddCallback([this, listener, _response]() {
                if (listener.IsValid())
                {
                    this->_onSuccess(this->GetId(), _response);
                    this->_onFinish(this);
                }
            });
        }
    };
}
