// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidJavaObject.h"
#include "JavaMethodSignature.h"

using namespace RuStoreSDK;

AndroidJavaObject::AndroidJavaObject(FString className, bool bAsGlobalRef)
{
#if PLATFORM_ANDROID
    env = FAndroidApplication::GetJavaEnv();
    javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));

    FString methodSignature = "()V";
    jmethodID constructor = FJavaWrapper::FindMethod(env, javaClass, "<init>", TCHAR_TO_ANSI(*methodSignature), false);

    javaObject = env->NewObject(javaClass, constructor);
    if (bAsGlobalRef) javaObject = env->NewGlobalRef(javaObject);

    bIsGlobalRef = bAsGlobalRef;
#endif
}

AndroidJavaObject::AndroidJavaObject(FString className, long cppPointer, bool bAsGlobalRef)
{
#if PLATFORM_ANDROID
    env = FAndroidApplication::GetJavaEnv();
    javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));

    if (cppPointer != 0)
    {
        FString methodSignature = "(J)V";
        jmethodID constructor = FJavaWrapper::FindMethod(env, javaClass, "<init>", TCHAR_TO_ANSI(*methodSignature), false);

        javaObject = env->NewObject(javaClass, constructor, (jlong)cppPointer);
        if (bAsGlobalRef) javaObject = env->NewGlobalRef(javaObject);

        bIsGlobalRef = bAsGlobalRef;
    }
    else
    {
        this->className = className;
        javaObject = NULL;

        bIsGlobalRef = false;
    }
#endif
}

#if PLATFORM_ANDROID
AndroidJavaObject::AndroidJavaObject(jthrowable throwable)
{
    env = FAndroidApplication::GetJavaEnv();
    javaClass = env->GetObjectClass(throwable);
    javaObject = (jobject)throwable;
}

AndroidJavaObject::AndroidJavaObject(jobject javaObject)
{
    env = FAndroidApplication::GetJavaEnv();
    javaClass = !env->IsSameObject(javaObject, nullptr) ? env->GetObjectClass(javaObject) : nullptr;
    this->javaObject = javaObject;
}

AndroidJavaObject::AndroidJavaObject(jobject javaObject, FString asInterface)
{
    env = FAndroidApplication::GetJavaEnv();
    javaClass = !env->IsSameObject(javaObject, nullptr) ? env->GetObjectClass(javaObject) : nullptr;
    this->javaObject = javaObject;
    className = asInterface;
}

AndroidJavaObject::AndroidJavaObject(jclass javaClass, jobject javaObject)
{
    env = FAndroidApplication::GetJavaEnv();
    this->javaClass = javaClass;
    this->javaObject = javaObject;
}

jobject AndroidJavaObject::GetJObject()
{
    return javaObject;
}
#endif

AndroidJavaObject::~AndroidJavaObject()
{
#if PLATFORM_ANDROID
    if (!env->IsSameObject(javaObject, nullptr))
    {
        if (bIsGlobalRef) env->DeleteGlobalRef(javaObject);
    }
    if (bIsAttachThread) CurrentJavaVM()->DetachCurrentThread();
#endif
}

void AndroidJavaObject::SetInterfaceName(FString asInterface)
{
    className = asInterface;
}

bool AndroidJavaObject::AttachCurrentThread()
{
#if PLATFORM_ANDROID
    JNIEnv* newEnv = nullptr;
    jint attachResult = CurrentJavaVM()->AttachCurrentThread(&env, nullptr);
    bIsAttachThread = (attachResult == JNI_OK);
    if (bIsAttachThread) env = newEnv;
#endif

    return bIsAttachThread;
}

AndroidJavaObject* AndroidJavaObject::UpdateToGlobalRef()
{
#if PLATFORM_ANDROID
    javaObject = env->NewGlobalRef(javaObject);
#endif
	bIsGlobalRef = true;

    return this;
}

FString AndroidJavaObject::GetName()
{
    if (className == "") className = ExtractName();

    return className;
}

FString AndroidJavaObject::ExtractName()
{
    FString nameFString = "";

#if PLATFORM_ANDROID
    jmethodID getNameMethodId = env->GetMethodID(javaClass, "getClass", "()Ljava/lang/Class;");
    jobject classObject = env->CallObjectMethod(javaObject, getNameMethodId);
    jclass objectClass = env->GetObjectClass(classObject);

    jmethodID getNameId = env->GetMethodID(objectClass, "getName", "()Ljava/lang/String;");
    jstring nameJString = (jstring)FJavaWrapper::CallObjectMethod(env, classObject, getNameId);
    nameFString = FJavaHelper::FStringFromParam(env, nameJString);
#endif

    return nameFString.Replace(TEXT("."), TEXT("/"));
}

template<typename T>
T* AndroidJavaObject::Get(FString fieldName)
{
#if PLATFORM_ANDROID
    jfieldID javaFieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), "L");

    T* result = nullptr;
    if (javaFieldId != nullptr)
    {
        result = (T*)env->GetObjectField(javaObject, javaFieldId);
    }

    return result;
#endif
    return nullptr;
}

int AndroidJavaObject::GetInt(FString fieldName)
{
    int result = 0;
#if PLATFORM_ANDROID
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*JavaMethodSignature::getName(result)));
    result = (int)env->GetIntField(javaObject, fieldId);
#endif
    return result;
}

int AndroidJavaObject::GetLong(FString fieldName)
{
    long result = 0;
#if PLATFORM_ANDROID
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*JavaMethodSignature::getName(result)));
    result = (long)env->GetLongField(javaObject, fieldId);
#endif
    return result;
}

bool AndroidJavaObject::GetBool(FString fieldName)
{
    bool result = 0;
#if PLATFORM_ANDROID
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*JavaMethodSignature::getName(result)));
    result = (long)env->GetBooleanField(javaObject, fieldId);
#endif
    return result;
}

FString AndroidJavaObject::GetFString(FString fieldName)
{
    FString result = "";
#if PLATFORM_ANDROID
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*JavaMethodSignature::getName(result)));
    jstring strResult = (jstring)env->GetObjectField(javaObject, fieldId);
    if (strResult != nullptr)
    {
        result = FJavaHelper::FStringFromParam(env, strResult);
    }
#endif
    return result;
}

int AndroidJavaObject::GetEnum(FString fieldName, FString signature)
{
    int result = 0;
#if PLATFORM_ANDROID
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*JavaMethodSignature::getName(result)));
    result = (int)env->GetIntField(javaObject, fieldId);
#endif
    return result;
}

TArray<uint8>* AndroidJavaObject::GetByteArray(FString fieldName)
{
    TArray<uint8>* result = new TArray<uint8>();

#if PLATFORM_ANDROID
    FString signature = JavaMethodSignature::getName(result);
    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*signature));
    
#ifdef RuStoreDebug
    _LogInfo(RuStoreDebug, signature);
#endif
    
    jbyteArray jArray = (jbyteArray)env->GetObjectField(javaObject, fieldId);
    int length = env->GetArrayLength(jArray);
    jbyte* data = env->GetByteArrayElements(jArray, nullptr);
    for (int i = 0; i < length; i++) {
        result->Add(static_cast<uint8>(data[i]));
    }
    env->ReleaseByteArrayElements(jArray, data, 0);
#endif

    return result;
}

AndroidJavaObject* AndroidJavaObject::GetStaticAJObject(FString fieldName, FString className)
{
    AndroidJavaObject* result = nullptr;

#if PLATFORM_ANDROID
    JNIEnv* env = FAndroidApplication::GetJavaEnv();
    jclass javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));

    FString javaClassSignature = "L" + className + ";";
    jfieldID javaFieldID = env->GetStaticFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*javaClassSignature));
    jobject localRef = env->GetStaticObjectField(javaClass, javaFieldID);

	if (localRef != nullptr)
	{
		result = new AndroidJavaObject(javaClass, localRef);
		result->UpdateToGlobalRef();
	}
#endif

    return result;
}

AndroidJavaObject* AndroidJavaObject::GetAJObject(FString fieldName, FString signature)
{
    if (signature == "")
    {
        AndroidJavaObject* _javaClass = this->CallAJClass("getClass");
        FString _signature = "L" + _javaClass->CallFString("getName") + ";";
        signature = _signature.Replace(TEXT("."), TEXT("/"));
        delete _javaClass;
    }

    AndroidJavaObject* result = nullptr;

#if PLATFORM_ANDROID
#ifdef RuStoreDebug
	_LogInfo(RuStoreDebug, signature);
#endif

    jfieldID fieldId = env->GetFieldID(javaClass, TCHAR_TO_ANSI(*fieldName), TCHAR_TO_ANSI(*signature));
    
    jobject localRef = env->GetObjectField(javaObject, fieldId);
    if (localRef != nullptr)
    {
        result = new AndroidJavaObject(localRef);
        result->UpdateToGlobalRef();
    }
#endif

    return result;
}

AndroidJavaObject* AndroidJavaObject::GetAJObjectArrayElement(int i)
{
	AndroidJavaObject* result = nullptr;

#if PLATFORM_ANDROID
	jobjectArray arr = reinterpret_cast<jobjectArray>(javaObject);
	jobject element = env->GetObjectArrayElement(arr, i);

	if (element != nullptr)
	{
		result = new AndroidJavaObject(element);
		result->UpdateToGlobalRef();
	}
#endif

    return result;
}

FString AndroidJavaObject::GetFStringArrayElement(int i)
{
    FString result = "";

#if PLATFORM_ANDROID
    jobjectArray arr = reinterpret_cast<jobjectArray>(javaObject);
    jstring strResult = (jstring)env->GetObjectArrayElement(arr, i);

    if (strResult != nullptr)
    {
        result = FJavaHelper::FStringFromParam(env, strResult);
    }
#endif

    return result;
}

FString RuStoreSDK::AndroidJavaObject::ConvertToFString()
{
    FString result = "";

#if PLATFORM_ANDROID
    jstring strResult = (jstring)javaObject;
    result = FJavaHelper::FStringFromParam(env, strResult);
#endif

    return result;
}

FString AndroidJavaObject::CallJavaClassFString(FString methodName)
{
    FString nameFString = "";

#if PLATFORM_ANDROID
    jmethodID getNameMethodId = env->GetMethodID(javaClass, "getClass", "()Ljava/lang/Class;");
    jobject classObject = env->CallObjectMethod(javaObject, getNameMethodId);
    jclass objectClass = env->GetObjectClass(classObject);

    jmethodID nameMethodId = env->GetMethodID(objectClass, TCHAR_TO_ANSI(*methodName), "()Ljava/lang/String;");
    jstring nameJString = (jstring)env->CallObjectMethod(classObject, nameMethodId);
    nameFString = FJavaHelper::FStringFromParam(env, nameJString);

    return nameFString;
#endif

    return FString();
}
