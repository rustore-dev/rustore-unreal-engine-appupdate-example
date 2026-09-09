#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API AndroidJavaObjectFactory
	{
	public:
		static AndroidJavaObject* CreateFromClassName(const FString& className, bool bMakeGlobalRef = true);

		static AndroidJavaObject* CreateForListener(const FString& className, const FString& interfaceName, intptr_t cppPointer, bool bMakeGlobalRef = true);

#if PLATFORM_ANDROID
		static AndroidJavaObject* CreateFromThrowable(jthrowable throwable);
		static AndroidJavaObject* CreateFromObject(jobject javaObject);
		static AndroidJavaObject* CreateFromClassAndObject(jclass javaClass, jobject javaObject);
#endif

		static AndroidJavaObject* CreateFromStaticField(const FString& fieldName, const FString& className);

		static AndroidJavaObject* CreateNullStub(const FString& interfaceName);
	};
}
