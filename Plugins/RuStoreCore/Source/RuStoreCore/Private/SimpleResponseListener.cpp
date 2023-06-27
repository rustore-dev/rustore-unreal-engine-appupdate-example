#include "SimpleResponseListener.h"

FURuStoreError* SimpleResponseListener::ConvertError(AndroidJavaObject* errorObject)
{
    FURuStoreError* error = new FURuStoreError();

    error->name = errorObject->CallJavaClassFString("getSimpleName");
    error->description = errorObject->CallFString("getMessage");

    return error;
}

SimpleResponseListener::SimpleResponseListener(FString className, FString interfaceName, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess, TFunction<void(RuStoreListener*)> onFinish)
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

SimpleResponseListener::~SimpleResponseListener()
{
    if (javaWrapper != nullptr)
    {
        javaWrapper->CallVoid("DisposeCppPointer");
        delete javaWrapper;
    }
}

AndroidJavaObject* SimpleResponseListener::GetJWrapper()
{
    return javaWrapper;
}

void SimpleResponseListener::OnFailure(AndroidJavaObject* errorObject)
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

void SimpleResponseListener::OnSuccess()
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener]() {
        if (!listener.expired())
        {
            this->_onSuccess(this->GetId());
            this->_onFinish(this);
        }
    });
}
