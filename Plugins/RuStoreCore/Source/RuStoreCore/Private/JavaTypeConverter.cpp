#include "JavaTypeConverter.h"

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
    const char* charString = env->GetStringUTFChars(data, JNI_FALSE);
    FString fString(charString);
    env->ReleaseStringUTFChars(data, charString);

    return fString;
}
#endif
