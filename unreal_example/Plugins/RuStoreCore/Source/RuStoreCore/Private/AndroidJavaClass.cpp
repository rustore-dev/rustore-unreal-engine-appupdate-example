// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidJavaClass.h"

using namespace RuStoreSDK;

AndroidJavaClass::AndroidJavaClass(FString className)
{
#if PLATFORM_ANDROID
    javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));

    _className = className;
    _classSignature = FString::Printf(TEXT("L%s;"), *_className);


#ifdef RuStoreDebug
    _LogInfo(RuStoreDebug, _classSignature);
#endif
#endif
}

AndroidJavaClass::~AndroidJavaClass()
{
}
