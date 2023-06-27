#pragma once

#include "CoreMinimal.h"
#include "RuStoreListener.h"
#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "CallbackHandler.h"
#include <memory>

using namespace std;

template<typename T>
class ResponseListener : public RuStoreListener
{
private:
    TFunction<void(long requestId, FURuStoreError*)> _onFailure;
    TFunction<void(long requestId, T*)> _onSuccess;
    TFunction<void(RuStoreListener*)> _onFinish;
    
    FString className = "";
    FString interfaceName = "";

protected:
    AndroidJavaObject* javaWrapper = nullptr;

    ResponseListener(FString className, FString interfaceName, TFunction<void(long requestId, FURuStoreError*)> onFailure, TFunction<void(long requestId, T*)> onSuccess, TFunction<void(RuStoreListener*)> onFinish)
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

public:
    AndroidJavaObject* GetJWrapper()
    {
        return javaWrapper;
    }

    virtual T* ConvertResponse(AndroidJavaObject* responseObject) = 0;
    virtual FURuStoreError* ConvertError(AndroidJavaObject* errorObject)
    {
        FURuStoreError* error = new FURuStoreError();

        error->name = errorObject->CallJavaClassFString("getSimpleName");
        error->description = errorObject->CallFString("getMessage");

        return error;
    }
    
    virtual ~ResponseListener()
    {
        if (javaWrapper != nullptr)
        {
            javaWrapper->CallVoid("DisposeCppPointer");
            delete javaWrapper;
        }
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

    void OnSuccess(AndroidJavaObject* responseObject)
    {
        auto response = TSharedPtr<T>(ConvertResponse(responseObject));
        delete responseObject;

        auto listener = GetWeakPtr();
        CallbackHandler::AddCallback([this, listener, response]() {
            if (!listener.expired())
            {
                this->_onSuccess(this->GetId(), response.Get());
                this->_onFinish(this);
            }
        });
    }
};
