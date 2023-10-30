// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"

//#define RuStoreDebug "RuStoreDebug"

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
#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, _classSignature);
#endif

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

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, methodSignature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            env->CallStaticVoidMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
    #endif
        }

        template <typename... Args>
        bool CallStaticBool(const FString methodName, Args... args)
        {
            bool result = false;
#if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeBool(args...);

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, methodSignature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            result = env->CallStaticBooleanMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
#endif
            return result;
        }

        template <typename... Args>
        FString CallStaticFString(const FString methodName, Args... args)
        {
            FString result = "";
    #if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeFString(args...);

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, methodSignature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            jstring strResult = (jstring)env->CallStaticObjectMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
            result = FJavaHelper::FStringFromParam(env, strResult);
    #endif
            return result;
        }

        template <typename... Args>
        AndroidJavaObject* CallStaticAJObject(const FString methodName, const FString signature, Args... args)
        {
            AndroidJavaObject* result = nullptr;
#if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeSpecificAJObject(signature, args...);

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, methodSignature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));

            jobject localRef = (jobject)env->CallStaticObjectMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);
            result = new AndroidJavaObject(localRef);
            result->UpdateToGlobalRef();
#endif
            return result;
        }

        template <typename... Args>
        TArray<uint8>* CallStaticByteArray(const FString methodName, Args... args)
        {
            TArray<uint8>* result = new TArray<uint8>();
#if PLATFORM_ANDROID
            JNIEnv* env = FAndroidApplication::GetJavaEnv();
            FString methodSignature = JavaMethodSignature::MakeByteArray(args...);

#ifdef RuStoreDebug
            _LogInfo(RuStoreDebug, methodSignature);
#endif

            jmethodID javaMethodId = env->GetStaticMethodID(javaClass, TCHAR_TO_ANSI(*methodName), TCHAR_TO_ANSI(*methodSignature));
            jbyteArray jArray = (jbyteArray)env->CallStaticObjectMethod(javaClass, javaMethodId, JavaTypeConverter::SetValue(env, args)...);

            int length = env->GetArrayLength(jArray);
            jbyte* data = env->GetByteArrayElements(jArray, nullptr);
            
            for (int i = 0; i < length; i++)
            {
                result->Add(static_cast<uint8>(data[i]));
            }

            env->ReleaseByteArrayElements(jArray, data, 0);
#endif
            return result;
        }
    };
}
