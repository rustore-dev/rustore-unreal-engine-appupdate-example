#include "AppUpdateInfoResponseListenerImpl.h"
#include "AndroidJavaObjectFactory.h"

namespace RuStoreSDK
{
    FURuStoreError* AppUpdateInfoResponseListenerImpl::ConvertError(AndroidJavaObject* errorObject)
    {
        auto error = ResponseListener::ConvertError(errorObject);

        if (error->name == "RuStoreInstallException")
        {
            auto errorCode = errorObject->GetInt("code");
            error->description = FString::FromInt(errorCode);
        }

        return error;
    }

    FURuStoreAppUpdateInfo* AppUpdateInfoResponseListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
    {
        auto response = new FURuStoreAppUpdateInfo();

        response->updateAvailability = (EURuStoreUpdateAvailability)responseObject->GetInt("updateAvailability");
        response->installStatus = (EURuStoreInstallStatus)responseObject->GetInt("installStatus");
        response->availableVersionCode = responseObject->GetLong("availableVersionCode");

        return response;
    }
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_appupdate_wrappers_AppUpdateInfoResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromThrowable(throwable);

        auto castobj = reinterpret_cast<RuStoreSDK::AppUpdateInfoResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_appupdate_wrappers_AppUpdateInfoResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer, jobject result)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromObject(result);

        auto castobj = reinterpret_cast<RuStoreSDK::AppUpdateInfoResponseListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
