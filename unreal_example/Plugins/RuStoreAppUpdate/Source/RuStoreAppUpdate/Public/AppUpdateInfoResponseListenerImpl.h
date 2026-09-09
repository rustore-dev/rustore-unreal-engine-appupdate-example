#pragma once

#include "FURuStoreAppUpdateInfo.h"
#include "ResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREAPPUPDATE_API AppUpdateInfoResponseListenerImpl : public ResponseListener<FURuStoreAppUpdateInfo>
    {
    public:
        AppUpdateInfoResponseListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreAppUpdateInfo, ESPMode::ThreadSafe>)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : ResponseListener<FURuStoreAppUpdateInfo>("ru/rustore/unrealsdk/appupdate/wrappers/AppUpdateInfoResponseListenerWrapper", "ru/rustore/unrealsdk/appupdate/callbacks/AppUpdateInfoResponseListener", onSuccess, onFailure, onFinish)
        {
        }

        virtual ~AppUpdateInfoResponseListenerImpl() { }

    protected:
        FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
        FURuStoreAppUpdateInfo* ConvertResponse(AndroidJavaObject* responseObject) override;
    };
}
