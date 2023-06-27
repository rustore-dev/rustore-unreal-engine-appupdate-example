#pragma once

#include "SimpleResponseListenerT.h"

class RUSTOREAPPUPDATE_API UpdateFlowResultListenerImpl : public SimpleResponseListenerT<int>
{
public:
    UpdateFlowResultListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, int)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : SimpleResponseListenerT<int>("com/Plugins/RuStoreAppUpdate/UpdateFlowResultListenerWrapper", "ru/rustore/unitysdk/appupdate/callbacks/UpdateFlowResultListener", onFailure, onSuccess, onFinish)
    {
    }

    virtual ~UpdateFlowResultListenerImpl() {}

protected:
    FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
};
