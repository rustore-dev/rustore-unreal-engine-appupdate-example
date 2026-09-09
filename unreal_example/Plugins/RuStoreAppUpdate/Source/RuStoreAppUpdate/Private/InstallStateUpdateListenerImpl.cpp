#include "InstallStateUpdateListenerImpl.h"
#include "CallbackHandler.h"
#include "AndroidJavaObjectFactory.h"

namespace RuStoreSDK
{
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

        
        int installErrorCode = stateObject->GetInt("installErrorCode");
        if (installErrorCode < 9901)
            installErrorCode -= 4001;
        else
            installErrorCode -= 9901 + 12;

        state->installErrorCode = (EURuStoreInstallErrorCode)installErrorCode;
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
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_appupdate_wrappers_InstallStateUpdateListenerWrapper_NativeOnStateUpdated(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromObject(result);

        auto castobj = reinterpret_cast<RuStoreSDK::InstallStateUpdateListenerImpl*>(pointer);
        castobj->OnStateUpdated(obj);
    }
}
#endif
