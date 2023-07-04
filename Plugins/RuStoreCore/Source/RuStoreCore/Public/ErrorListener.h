// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CallbackHandler.h"
#include "ErrorConverter.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API ErrorListener : public RuStoreListener
    {
    protected:
        TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> _onFailure;
        TFunction<void(RuStoreListener*)> _onFinish;

        ErrorListener(
            FString className,
            FString interfaceName,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : RuStoreListener(className, interfaceName)
        {
            _onFailure = onFailure;
            _onFinish = onFinish;
        }
        virtual ~ErrorListener();

        virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject);

    public:
        void OnFailure(AndroidJavaObject* errorObject);
    };
}
