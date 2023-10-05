// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ErrorListener.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API SimpleResponseListener : public ErrorListener
    {
    private:
        TFunction<void(long requestId)> _onSuccess;

    protected:
        SimpleResponseListener(
            FString className,
            FString interfaceName,
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ErrorListener(className, interfaceName, onFailure, onFinish)
        {
            _onSuccess = onSuccess;
        }

        virtual ~SimpleResponseListener();

    public:
        void OnSuccess();
    };
}
