// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAndroidClasses.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API JavaTypeConverter
    {
    public:
#if PLATFORM_ANDROID
        template<typename T>
        static T SetValue(JNIEnv* env, T& data) { return data; }

        template<typename T>
        static jobject SetValue(JNIEnv* env, T* data) { return ((IAndroidClasses*)data)->GetJObject(); }
        static jboolean SetValue(JNIEnv* env, bool data) { return static_cast<jboolean>(data); }
        static jbyte SetValue(JNIEnv* env, unsigned char data) { return static_cast<jbyte>(data); }
        static jchar SetValue(JNIEnv* env, char data) { return static_cast<jchar>(data); }
        static jshort SetValue(JNIEnv* env, short data) { return static_cast<jshort>(data); }
        static jint SetValue(JNIEnv* env, int data) { return static_cast<jint>(data); }
        static jlong SetValue(JNIEnv* env, long data) { return static_cast<jlong>(data); }
        static jfloat SetValue(JNIEnv* env, float data) { return static_cast<jfloat>(data); }
        static jdouble SetValue(JNIEnv* env, double data) { return static_cast<jdouble>(data); }
        static jstring SetValue(JNIEnv* env, FString& str) { return env->NewStringUTF(TCHAR_TO_UTF8(*str)); }
        static jbyteArray SetValue(JNIEnv* env, TArray<uint8>& data);
        static jobjectArray SetValue(JNIEnv* env, TArray<FString>& data);
        static FString Convert(JNIEnv* env, jstring data);
#endif
    };
}
