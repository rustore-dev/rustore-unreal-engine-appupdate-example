#pragma once

#include "ErrorListener.h"

namespace RuStoreSDK
{
    class RUSTOREAPPUPDATE_API AppUpdateErrorListenerImpl : public ErrorListener
    {
    public:
        AppUpdateErrorListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ErrorListener("ru/rustore/unrealsdk/appupdate/wrappers/AppUpdateErrorListenerWrapper", "ru/rustore/unrealsdk/core/callbacks/ErrorListener", onFailure, onFinish)
        {
        }

        virtual ~AppUpdateErrorListenerImpl() { }

    protected:
        FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
    };
}
