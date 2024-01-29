// Copyright Epic Games, Inc. All Rights Reserved.

#include "ErrorConverter.h"

using namespace RuStoreSDK;

FURuStoreError* ErrorConverter::Convert(AndroidJavaObject* errorObject)
{
    auto error = new FURuStoreError();

    error->name = errorObject->CallJavaClassFString("getSimpleName");
    error->description = errorObject->CallFString("getMessage");

    return error;
}
