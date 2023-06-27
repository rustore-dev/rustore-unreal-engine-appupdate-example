#pragma once

#include "CoreMinimal.h"

#include "AndroidJavaClass.h"
#include "CallbackHandler.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"

template <typename T>
class SimpleResponseListenerT : public RuStoreListener
{
private:
    TFunction<void(long, FURuStoreError*)> _onFailure;
    TFunction<void(long, T)> _onSuccess;
    TFunction<void(RuStoreListener*)> _onFinish;

    FString className = "";
    FString interfaceName = "";

    AndroidJavaObject* javaWrapper = nullptr;

protected:
    SimpleResponseListenerT(FString className, FString interfaceName, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long, T)> onSuccess, TFunction<void(RuStoreListener*)> onFinish)
    {
        _onFailure = onFailure;
        _onSuccess = onSuccess;
        _onFinish = onFinish;

        this->className = className;
        this->interfaceName = interfaceName;

        long cppPointer = 0;
#if PLATFORM_ANDROID
        cppPointer = (long)this;
#endif
        javaWrapper = new AndroidJavaObject(className, cppPointer, false);
        javaWrapper->SetInterfaceName(interfaceName);
    }

    ~SimpleResponseListenerT()
    {
        if (javaWrapper != nullptr)
        {
            javaWrapper->CallVoid("DisposeCppPointer");
            delete javaWrapper;
        }
    }

    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject)
    {
        FURuStoreError* error = new FURuStoreError();

        error->name = errorObject->CallJavaClassFString("getSimpleName");
        error->description = errorObject->CallFString("getMessage");

        return error;
    }

public:
    AndroidJavaObject* GetJWrapper()
    {
        return javaWrapper;
    }
    
    void OnFailure(AndroidJavaObject* errorObject)
    {
        auto error = TSharedPtr<FURuStoreError>(ConvertError(errorObject));
        delete errorObject;

        auto listener = GetWeakPtr();
        CallbackHandler::AddCallback([this, listener, error]() {
            if (!listener.expired())
            {
                this->_onFailure(this->GetId(), error.Get());
                this->_onFinish(this);
            }
        });
    }

    void OnSuccess(T response)
    {
        auto listener = GetWeakPtr();
        CallbackHandler::AddCallback([this, listener, response]() {
            if (!listener.expired())
            {
                this->_onSuccess(this->GetId(), response);
                this->_onFinish(this);
            }
        });
    }
};
