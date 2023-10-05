// Copyright Epic Games, Inc. All Rights Reserved.

#include "ErrorListener.h"

using namespace RuStoreSDK;

ErrorListener::~ErrorListener()
{
}

FURuStoreError* ErrorListener::ConvertError(AndroidJavaObject* errorObject)
{
    return ErrorConverter::Convert(errorObject);
}

void ErrorListener::OnFailure(AndroidJavaObject* errorObject)
{
    auto error = TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>(ConvertError(errorObject));
    delete errorObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, error]() {
        if (listener.IsValid())
        {
            this->_onFailure(this->GetId(), error);
            this->_onFinish(this);
        }
    });
}
