// Copyright Epic Games, Inc. All Rights Reserved.

#include "JavaMethodSignature.h"

using namespace RuStoreSDK;

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
