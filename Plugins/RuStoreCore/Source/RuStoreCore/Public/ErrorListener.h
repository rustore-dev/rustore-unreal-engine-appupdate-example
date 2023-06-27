#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "CallbackHandler.h"

class RUSTORECORE_API ErrorListener : public RuStoreListener
{
private:
    TFunction<void(long, FURuStoreError*)> _onFailure;
    TFunction<void(RuStoreListener*)> _onFinish;

    FString className = "";
    FString interfaceName = "";

    AndroidJavaObject* javaWrapper = nullptr;

protected:
    ErrorListener(FString className, FString interfaceName, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(RuStoreListener*)> onFinish);
    ~ErrorListener();

    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject);

public:
    AndroidJavaObject* GetJWrapper();

    void OnFailure(AndroidJavaObject* errorObject);
};
