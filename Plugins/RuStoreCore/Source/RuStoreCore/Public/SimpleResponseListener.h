#pragma once

#include "CoreMinimal.h"
#include "CallbackHandler.h"
#include "AndroidJavaObject.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"

class RUSTORECORE_API SimpleResponseListener : public RuStoreListener
{
private:
    TFunction<void(long requestId, FURuStoreError*)> _onFailure;
    TFunction<void(long requestId)> _onSuccess;
    TFunction<void(RuStoreListener*)> _onFinish;

    FString className = "";
    FString interfaceName = "";

    AndroidJavaObject* javaWrapper = nullptr;

protected:
    SimpleResponseListener(FString className, FString interfaceName, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess, TFunction<void(RuStoreListener*)> onFinish);
    virtual ~SimpleResponseListener();

    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject);

public:
    AndroidJavaObject* GetJWrapper();

    void OnFailure(AndroidJavaObject* errorObject);
    void OnSuccess();
};
