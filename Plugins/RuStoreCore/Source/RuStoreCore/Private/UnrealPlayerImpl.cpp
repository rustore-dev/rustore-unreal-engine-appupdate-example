#include "UnrealPlayerImpl.h"

UnrealPlayerImpl::UnrealPlayerImpl()
{
    player = new AndroidJavaObject("com/Plugins/RuStoreCore/UnrealPlayerWrapper", true);
    player->SetInterfaceName("ru/rustore/unitysdk/core/IPlayerProvider");
}

UnrealPlayerImpl::~UnrealPlayerImpl()
{
    delete player;
}

AndroidJavaObject* UnrealPlayerImpl::GetPlayer()
{
    return player;
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT jobject JNICALL Java_com_Plugins_RuStoreCore_UnrealPlayerWrapper_NativeOnActivityRequest(JNIEnv*, jobject)
    {
        return FJavaWrapper::GameActivityThis;
    }
}
#endif
