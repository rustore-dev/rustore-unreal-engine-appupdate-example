#pragma once

#include "ErrorListener.h"

class RUSTOREAPPUPDATE_API AppUpdateErrorListenerImpl : public ErrorListener
{
public:
    AppUpdateErrorListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ErrorListener("com/Plugins/RuStoreAppUpdate/AppUpdateErrorListenerWrapper", "ru/rustore/unitysdk/core/callbacks/ErrorListener", onFailure, onFinish)
    {
    }

    virtual ~AppUpdateErrorListenerImpl() {}

protected:
    FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
};
