// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaTypeConverter.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
jobjectArray JavaTypeConverter::SetValue(JNIEnv* env, TArray<FString>& data)
{
    jobjectArray javaStringArray = (jobjectArray)env->NewObjectArray(data.Num(), FJavaWrapper::JavaStringClass, nullptr);
    for (int i = 0; i < data.Num(); i++)
    {
        env->SetObjectArrayElement(javaStringArray, i, SetValue(env, data[i]));
    }
    
    return javaStringArray;
}

FString JavaTypeConverter::Convert(JNIEnv* env, jstring data)
{
    return FJavaHelper::FStringFromParam(env, data);
}
#endif
