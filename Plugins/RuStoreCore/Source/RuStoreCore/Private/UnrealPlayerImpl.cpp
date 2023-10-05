// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealPlayerImpl.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT jobject JNICALL Java_com_Plugins_RuStoreCore_UnrealPlayerWrapper_NativeOnActivityRequest(JNIEnv*, jobject)
    {
        return FJavaWrapper::GameActivityThis;
    }
}
#endif
