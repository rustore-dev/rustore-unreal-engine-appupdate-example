// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaTypeConverter.h"

using namespace RuStoreSDK;

#if PLATFORM_ANDROID
jbyteArray JavaTypeConverter::SetValue(JNIEnv* env, TArray<uint8>& data)
{
    jbyteArray byteArray = (jbyteArray)env->NewByteArray(data.Num());
    uint8* dataPtr = data.GetData();
    env->SetByteArrayRegion(byteArray, 0, data.Num(), reinterpret_cast<const jbyte*>(dataPtr));

    return byteArray;
}

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
