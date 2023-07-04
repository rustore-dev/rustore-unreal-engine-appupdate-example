// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleResponseListener.h"

using namespace RuStoreSDK;

SimpleResponseListener::~SimpleResponseListener()
{
}

void SimpleResponseListener::OnSuccess()
{
    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener]() {
        if (listener.IsValid())
        {
            this->_onSuccess(this->GetId());
            this->_onFinish(this);
        }
    });
}
