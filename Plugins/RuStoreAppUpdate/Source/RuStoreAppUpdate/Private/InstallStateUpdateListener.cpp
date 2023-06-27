#include "InstallStateUpdateListener.h"
#include "CallbackHandler.h"

InstallStateUpdateListener::InstallStateUpdateListener(IInstallStateUpdateListener* listener)
{
    _listener = listener;

#if PLATFORM_ANDROID
    cppPointer = (long)this;
    jlistener = new AndroidJavaObject("com/Plugins/RuStoreAppUpdate/InstallStateUpdateListenerWrapper", cppPointer);
    jlistener->UpdateToGlobalRef();
    jlistener->SetInterfaceName("ru/rustore/sdk/appupdate/listener/InstallStateUpdateListener");
#endif
}

InstallStateUpdateListener::~InstallStateUpdateListener()
{
    if (jlistener != nullptr) jlistener->~AndroidJavaObject();
}

void InstallStateUpdateListener::OnStateUpdated(AndroidJavaObject* stateObject)
{
    FUInstallState state;
    state.bytesDownloaded = stateObject->GetLong("bytesDownloaded");
    state.totalBytesToDownload = stateObject->GetLong("totalBytesToDownload");
    state.installErrorCode = (EUInstallErrorCode)(stateObject->GetInt("installErrorCode") - 4001);
    state.installStatus = (EUInstallStatus)stateObject->GetInt("installStatus");

    stateObject->~AndroidJavaObject();

    CallbackHandler::AddCallback([this, state]() {
        if (_listener != nullptr)
        {
            _listener->OnStateUpdated(state);
        }
    });
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreAppUpdate_InstallStateUpdateListenerWrapper_NativeOnStateUpdated(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto castobj = reinterpret_cast<InstallStateUpdateListener*>(pointer);
        auto obj = new AndroidJavaObject(result);
        obj->UpdateToGlobalRef();
        castobj->OnStateUpdated(obj);
    }
}
#endif
