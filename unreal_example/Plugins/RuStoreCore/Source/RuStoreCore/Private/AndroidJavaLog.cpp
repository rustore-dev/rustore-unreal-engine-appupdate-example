// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidJavaLog.h"
#include "IAndroidClasses.h"

void RuStoreSDK::_LogVerbose(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_VERBOSE, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void RuStoreSDK::_LogDebug(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_DEBUG, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void RuStoreSDK::_LogInfo(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void RuStoreSDK::_LogWarn(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_WARN, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}

void RuStoreSDK::_LogError(FString tag, FString message)
{
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_ERROR, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*message));
#endif
}
