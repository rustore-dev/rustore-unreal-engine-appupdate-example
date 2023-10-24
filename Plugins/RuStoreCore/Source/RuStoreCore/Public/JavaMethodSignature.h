// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IAndroidClasses.h"

namespace RuStoreSDK
{
    class RUSTORECORE_API JavaMethodSignature
    {
    public:
        template <typename T>
        static FString getName(T);
        static FString getName(IAndroidClasses* obj);
        static FString getName(void);
        static FString getName(bool);
        static FString getName(unsigned char);
        static FString getName(char);
        static FString getName(short);
        static FString getName(int);
        static FString getName(long);
        static FString getName(float);
        static FString getName(double);
        static FString getName(FString&);
        static FString getName(TArray<FString>&);
        static FString getName(TArray<uint8>&);
        static FString getName(TArray<uint8>*);

        template <typename T>
        static FString getNames(T* obj) {
            return getName((IAndroidClasses*)obj);
        }

        template <typename T>
        static FString getNames(T obj) {
            return getName(obj);
        }

        static FString getNames(FString obj) {
            return getName(obj);
        }

        static FString getNames(TArray<uint8>* obj) {
            return getName(obj);
        }

        template <typename... Args>
        static FString Constuct(Args... args)
        {
            FString body = "";
            for (const auto& arg : TArray<FString>{ args... })
            {
                body += arg;
            }

            return FString::Printf(TEXT("(%s)"), *body);
        }

        template <typename... Args>
        static FString MakeVoid(Args... args)
        {
            return Constuct(getNames(args)...) + "V";
        }

        template <typename... Args>
        static FString MakeBool(Args... args)
        {
            return Constuct(getNames(args)...) + "Z";
        }

        template <typename... Args>
        static FString MakeByte(Args... args)
        {
            return Constuct(getNames(args)...) + "B";
        }

        template <typename... Args>
        static FString MakeInt(Args... args)
        {
            return Constuct(getNames(args)...) + "I";
        }

        template <typename... Args>
        static FString MakeLong(Args... args)
        {
            return Constuct(getNames(args)...) + "J";
        }

        template <typename... Args>
        static FString MakeFString(Args... args)
        {
            return Constuct(getNames(args)...) + "Ljava/lang/String;";
        }

        template <typename... Args>
        static FString MakeAJClass(Args... args)
        {
            return Constuct(getNames(args)...) + "Ljava/lang/Class;";
        }

        template <typename... Args>
        static FString MakeAJObject(Args... args)
        {
            return Constuct(getNames(args)...) + "Ljava/lang/Object;";
        }

        template <typename... Args>
        static FString MakeSpecificAJObject(FString signature, Args... args)
        {
            return Constuct(getNames(args)...) + signature;
        }

        template <typename... Args>
        static FString MakeByteArray(Args... args)
        {
            return Constuct(getNames(args)...) + "[B";
        }
    };
}
