#include "AndroidJavaObjectFactory.h"

using namespace RuStoreSDK;

AndroidJavaObject* AndroidJavaObjectFactory::CreateFromClassName(const FString& className, bool bMakeGlobalRef)
{
#if PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));
	if (javaClass == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateFromClassName: class not found: %s"), *className));
		return nullptr;
	}

	FString methodSignature = "()V";
	jmethodID constructor = FJavaWrapper::FindMethod(env, javaClass, "<init>", TCHAR_TO_ANSI(*methodSignature), false);
	if (constructor == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateFromClassName: constructor not found for class %s"), *className));
		return nullptr;
	}

	jobject localObject = env->NewObject(javaClass, constructor);
	if (localObject == nullptr || env->ExceptionCheck())
	{
		if (env->ExceptionCheck()) env->ExceptionClear();
		_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateFromClassName: NewObject failed for class %s"), *className));
		return nullptr;
	}

	jobject javaObject = bMakeGlobalRef ? env->NewGlobalRef(localObject) : localObject;
	if (bMakeGlobalRef) env->DeleteLocalRef(localObject);

	return new AndroidJavaObject(env, javaClass, javaObject, "", bMakeGlobalRef);
#else
	return new AndroidJavaObject(className);
#endif
}

AndroidJavaObject* AndroidJavaObjectFactory::CreateForListener(const FString& className, const FString& interfaceName, intptr_t cppPointer, bool bMakeGlobalRef)
{
#if PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	jclass javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));
	if (javaClass == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateForListener: class not found: %s"), *className));
		return nullptr;
	}

	if (cppPointer != 0)
	{
		FString methodSignature = "(J)V";
		jmethodID constructor = FJavaWrapper::FindMethod(env, javaClass, "<init>", TCHAR_TO_ANSI(*methodSignature), false);
		if (constructor == nullptr)
		{
			_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateForListener: constructor not found for class %s"), *className));
			return nullptr;
		}

		jobject localObject = env->NewObject(javaClass, constructor, (jlong)cppPointer);
		if (localObject == nullptr || env->ExceptionCheck())
		{
			if (env->ExceptionCheck()) env->ExceptionClear();
			_LogError("AndroidJavaObjectFactory", FString::Printf(TEXT("CreateForListener: NewObject failed for class %s"), *className));
			return nullptr;
		}

		jobject javaObject = bMakeGlobalRef ? env->NewGlobalRef(localObject) : localObject;
		if (bMakeGlobalRef) env->DeleteLocalRef(localObject);

		return new AndroidJavaObject(env, javaClass, javaObject, interfaceName, bMakeGlobalRef);
	}
	else
	{
		return new AndroidJavaObject(env, javaClass, nullptr, interfaceName, false);
	}
#else
	return new AndroidJavaObject(interfaceName);
#endif
}

#if PLATFORM_ANDROID
AndroidJavaObject* AndroidJavaObjectFactory::CreateFromThrowable(jthrowable throwable)
{
	if (throwable == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", TEXT("CreateFromThrowable: throwable is null"));
		return nullptr;
	}

	JNIEnv* env = FAndroidApplication::GetJavaEnv();

	jclass localClass = env->GetObjectClass(throwable);
	jclass globalClass = (jclass)env->NewGlobalRef(localClass);
	env->DeleteLocalRef(localClass);

	jobject globalObject = env->NewGlobalRef((jobject)throwable);

	return new AndroidJavaObject(env, globalClass, globalObject, "", true, true);
}

AndroidJavaObject* AndroidJavaObjectFactory::CreateFromObject(jobject javaObject)
{
	if (javaObject == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", TEXT("CreateFromObject: javaObject is null"));
		return nullptr;
	}

	JNIEnv* env = FAndroidApplication::GetJavaEnv();

	// javaClass: локальную ссылку глобализируем и удаляем
	jclass localClass = env->GetObjectClass(javaObject);
	jclass globalClass = (jclass)env->NewGlobalRef(localClass);
	env->DeleteLocalRef(localClass);

	// javaObject: глобализируем, но НЕ удаляем — caller владеет входным local ref
	jobject globalObject = env->NewGlobalRef(javaObject);

	return new AndroidJavaObject(env, globalClass, globalObject, "", true, true);
}

AndroidJavaObject* AndroidJavaObjectFactory::CreateFromClassAndObject(jclass javaClass, jobject javaObject)
{
	if (javaObject == nullptr)
	{
		_LogError("AndroidJavaObjectFactory", TEXT("CreateFromClassAndObject: javaObject is null"));
		return nullptr;
	}

	JNIEnv* env = FAndroidApplication::GetJavaEnv();

	// Оба параметра: создаём независимые global refs, входные ссылки НЕ удаляем —
	// caller владеет ими и должен вызвать DeleteLocalRef при необходимости
	jclass globalClass = (jclass)env->NewGlobalRef(javaClass);
	jobject globalObject = env->NewGlobalRef(javaObject);

	return new AndroidJavaObject(env, globalClass, globalObject, "", true, true);
}
#endif

AndroidJavaObject* AndroidJavaObjectFactory::CreateFromStaticField(const FString& fieldName, const FString& className)
{
	return AndroidJavaObject::GetStaticAJObject(fieldName, className);
}

AndroidJavaObject* AndroidJavaObjectFactory::CreateNullStub(const FString& interfaceName)
{
#if PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	return new AndroidJavaObject(env, nullptr, nullptr, interfaceName, false);
#else
	return new AndroidJavaObject(interfaceName);
#endif
}
