// Copyright Epic Games, Inc. All Rights Reserved.

#include "CallbackHandler.h"
#include "Async/Async.h"

using namespace RuStoreSDK;

void CallbackHandler::AddCallback(TFunction<void()> callback)
{
    AsyncTask(ENamedThreads::GameThread, callback);
}
