#include "ErrorListener.h"

ErrorListener::ErrorListener(FString className, FString interfaceName, TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(RuStoreListener*)> onFinish)
{
    _onFailure = onFailure;
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

ErrorListener::~ErrorListener()
{
    if (javaWrapper != nullptr)
    {
        javaWrapper->CallVoid("DisposeCppPointer");
        delete javaWrapper;
    }
}

AndroidJavaObject* ErrorListener::GetJWrapper()
{
    return javaWrapper;
}

FURuStoreError* ErrorListener::ConvertError(AndroidJavaObject* errorObject)
{
    auto error = new FURuStoreError();

    error->name = errorObject->CallJavaClassFString("getSimpleName");
    error->description = errorObject->CallFString("getMessage");

    return error;
}

void ErrorListener::OnFailure(AndroidJavaObject* errorObject)
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
