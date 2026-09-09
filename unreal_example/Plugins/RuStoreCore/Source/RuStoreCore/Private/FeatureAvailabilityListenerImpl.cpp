#include "FeatureAvailabilityListenerImpl.h"
#include "AndroidJavaObjectFactory.h"

namespace RuStoreSDK
{
    FeatureAvailabilityListenerImpl::~FeatureAvailabilityListenerImpl()
    {
    }
    
    FURuStoreFeatureAvailabilityResult* FeatureAvailabilityListenerImpl::ConvertResponse(AndroidJavaObject* responseObject)
    {
        FString resultType = "";
    
        AndroidJavaObject* javaClassObject = responseObject->CallAJClass("getClass");
    
        FString str = javaClassObject->CallFString("getName");
        TArray<FString> _className;
        str.ParseIntoArray(_className, TEXT("$"), true);
        if (_className.Num() > 0) resultType = _className.Last();
    
        delete javaClassObject;
    
        auto response = new FURuStoreFeatureAvailabilityResult();
    
        if (resultType == "Unavailable")
        {
            response->isAvailable = false;
    
            auto causeObject = responseObject->GetAJObject("cause", "Lru/rustore/sdk/core/exception/RuStoreException;");
    
            response->cause.name = causeObject->CallJavaClassFString("getSimpleName");
            response->cause.description = causeObject->CallFString("getMessage");
        }
        else
        {
            if (resultType == "Available")
            {
                response->isAvailable = true;
            }
            else
            {
                response->isAvailable = false;
                response->cause.name = "Error";
                response->cause.description = "Invalid response type";
            }
        }
    
        return response;
    }
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_core_wrappers_FeatureAvailabilityListenerWrapper_NativeOnFailure(JNIEnv* env, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromThrowable(throwable);

        auto castobj = reinterpret_cast<RuStoreSDK::FeatureAvailabilityListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_core_wrappers_FeatureAvailabilityListenerWrapper_NativeOnSuccess(JNIEnv* env, jobject, jlong pointer, jobject result)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromObject(result);

        auto castobj = reinterpret_cast<RuStoreSDK::FeatureAvailabilityListenerImpl*>(pointer);
        castobj->OnSuccess(obj);
    }
}
#endif
