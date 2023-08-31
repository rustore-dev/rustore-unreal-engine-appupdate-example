// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaMethodSignature.h"

using namespace RuStoreSDK;

template <typename T>
FString JavaMethodSignature::getName(T) { return TEXT(""); }
FString JavaMethodSignature::getName(IAndroidClasses* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(AndroidJavaObject* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(JavaActivity* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(JavaApplication* obj) { return FString::Printf(TEXT("L%s;"), *obj->GetName()); }
FString JavaMethodSignature::getName(void) { return TEXT("V"); }
FString JavaMethodSignature::getName(bool) { return TEXT("Z"); }
FString JavaMethodSignature::getName(unsigned char) { return TEXT("B"); }
FString JavaMethodSignature::getName(char) { return TEXT("C"); }
FString JavaMethodSignature::getName(short) { return TEXT("S"); }
FString JavaMethodSignature::getName(int) { return TEXT("I"); }
FString JavaMethodSignature::getName(long) { return TEXT("J"); }
FString JavaMethodSignature::getName(float) { return TEXT("F"); }
FString JavaMethodSignature::getName(double) { return TEXT("D"); }
FString JavaMethodSignature::getName(FString&) { return TEXT("Ljava/lang/String;"); }
FString JavaMethodSignature::getName(TArray<FString>&) { return TEXT("[Ljava/lang/String;"); }
FString JavaMethodSignature::getName(TArray<uint8>&) { return TEXT("[B"); }
FString JavaMethodSignature::getName(TArray<uint8>*) { return TEXT("[B"); }
