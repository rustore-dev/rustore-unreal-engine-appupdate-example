// Copyright Epic Games, Inc. All Rights Reserved.

#include "InstallStateUpdateListenerImpl.h"
#include "CallbackHandler.h"

using namespace RuStoreSDK;

InstallStateUpdateListenerImpl::~InstallStateUpdateListenerImpl()
{
}

void InstallStateUpdateListenerImpl::OnStateUpdated(AndroidJavaObject* stateObject)
{
    auto state = MakeShared<FURuStoreInstallState, ESPMode::ThreadSafe>();
    state->bytesDownloaded = stateObject->GetLong("bytesDownloaded");
    state->totalBytesToDownload = stateObject->GetLong("totalBytesToDownload");

    state->percentDownloaded = (state->totalBytesToDownload > 0)
        ? (double)state->bytesDownloaded / (double)state->totalBytesToDownload
        : 0;

    state->installErrorCode = (EURuStoreInstallErrorCode)(stateObject->GetInt("installErrorCode") - 4001);
    state->installStatus = (EURuStoreInstallStatus)stateObject->GetInt("installStatus");

    delete stateObject;

    auto listener = GetWeakPtr();
    CallbackHandler::AddCallback([this, listener, state]() {
        if (listener.IsValid())
        {
            this->_onStateUpdated(this->GetId(), state);
        }
    });
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_InstallStateUpdateListenerWrapper_NativeOnStateUpdated(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<InstallStateUpdateListenerImpl*>(pointer);
        castobj->OnStateUpdated(obj);
    }
}
#endif
