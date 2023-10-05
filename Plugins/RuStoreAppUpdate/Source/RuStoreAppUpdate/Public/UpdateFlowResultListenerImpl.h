// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SimpleResponseListenerT.h"

namespace RuStoreSDK
{
    class RUSTOREAPPUPDATE_API UpdateFlowResultListenerImpl : public SimpleResponseListenerT<int>
    {
    public:
        UpdateFlowResultListenerImpl(
            TFunction<void(long, int)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListenerT<int>("com/Plugins/RuStoreAppUpdate/UpdateFlowResultListenerWrapper", "ru/rustore/unitysdk/appupdate/callbacks/UpdateFlowResultListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~UpdateFlowResultListenerImpl() { }

    protected:
        int ConvertResponse(int response) override;
        FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
    };
}
