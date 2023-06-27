#pragma once

#include "FUAppUpdateInfo.h"
#include "ResponseListener.h"

class RUSTOREAPPUPDATE_API AppUpdateInfoResponseListenerImpl : public ResponseListener<FUAppUpdateInfo>
{
public:
    AppUpdateInfoResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long, FUAppUpdateInfo*)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : ResponseListener<FUAppUpdateInfo>("com/Plugins/RuStoreAppUpdate/AppUpdateInfoResponseListenerWrapper", "ru/rustore/unitysdk/appupdate/callbacks/AppUpdateInfoResponseListener", onFailure, onSuccess, onFinish)
    {
    }

    virtual ~AppUpdateInfoResponseListenerImpl() {}

protected:
    FURuStoreError* ConvertError(AndroidJavaObject* errorObject) override;
    FUAppUpdateInfo* ConvertResponse(AndroidJavaObject* responseObject) override;
};
