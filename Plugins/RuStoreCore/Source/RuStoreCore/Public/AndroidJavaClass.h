// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API AndroidJavaClass
    {
    private:
    #if PLATFORM_ANDROID
        jclass javaClass;
    #endif
        FString _className;
        FString _classSignature;

    public:
        AndroidJavaClass(FString className);
        virtual ~AndroidJavaClass();

        AndroidJavaObject* GetStaticAJObject(const FString fieldName)
        {
            AndroidJavaObject* result = nullptr;

    #if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            jfieldID javaFieldID = env->GetStaticFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*_classSignature));
            jobject javaObject = env->NewGlobalRef(env->GetStaticObjectField(javaClass, javaFieldID));
            result = new AndroidJavaObject(javaClass, javaObject);
            result->UpdateToGlobalRef();
    #endif

            return result;
        }

        template <typename... Args>
        void CallStaticVoid(const FString methodName, Args... args)
        {
    #if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeVoid(args...);
            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            env->CallStaticVoidMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
    #endif
        }

        template <typename... Args>
        FString CallStaticFString(const FString methodName, Args... args)
        {
            FString result = "";
    #if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeFString(args...);
            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));

            FString tag = "rustore";
            FString msg = methodSignature;
            __android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*msg));

            jstring strResult = (jstring)env->CallStaticObjectMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
            result = FJavaHelper::FStringFromParam(env, strResult);
    #endif
            return result;
        }
    };
}
