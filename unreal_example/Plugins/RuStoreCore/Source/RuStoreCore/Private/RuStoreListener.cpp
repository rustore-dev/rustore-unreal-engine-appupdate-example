// Copyright Epic Games, Inc. All Rights Reserved.

#include "RuStoreListener.h"

using namespace RuStoreSDK;

long RuStoreListener::counter = 0;

RuStoreListener::RuStoreListener(FString className, FString interfaceName, bool bAsGlobalRef)
{
	id = ++counter;

	this->className = className;
	this->interfaceName = interfaceName;

	long cppPointer = 0;
#if PLATFORM_ANDROID
	cppPointer = (long)this;
#endif
	javaWrapper = new AndroidJavaObject(className, cppPointer, bAsGlobalRef);
	javaWrapper->SetInterfaceName(interfaceName);
}

RuStoreListener::~RuStoreListener()
{
	if (javaWrapper != nullptr)
	{
		javaWrapper->CallVoid("DisposeCppPointer");
		delete javaWrapper;
	}
}

long RuStoreListener::GetId()
{
	return id;
}

void RuStoreListener::SetWeakPtr(TWeakPtr<RuStoreListener, ESPMode::ThreadSafe> value)
{
	weakPtr = value;
}

TWeakPtr<RuStoreListener, ESPMode::ThreadSafe> RuStoreListener::GetWeakPtr()
{
	return weakPtr;
}

AndroidJavaObject* RuStoreListener::GetJWrapper()
{
	return javaWrapper;
}

TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> RuStoreListenerContainer::ListenerBind(RuStoreListener* item)
{
	TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> sharedPtr(item);
	sharedPtr->SetWeakPtr(sharedPtr);
	listeners.Emplace(sharedPtr);

	return sharedPtr;
}

void RuStoreListenerContainer::ListenerUnbind(long id)
{
	listeners.RemoveAll([&](const TSharedPtr<RuStoreListener, ESPMode::ThreadSafe>& item) { return item->GetId() == id; });
}

void RuStoreListenerContainer::ListenerUnbind(RuStoreListener* item)
{
	ListenerUnbind(item->GetId());
}

void RuStoreListenerContainer::ListenerUnbind(TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> item)
{
	ListenerUnbind(item->GetId());
}

void RuStoreListenerContainer::ListenerRemoveAll()
{
	listeners.Empty();
}
