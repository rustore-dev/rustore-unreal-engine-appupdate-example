// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API RuStoreListener
	{
	private:
		static long counter;
		long id = 0;
		TWeakPtr<RuStoreListener, ESPMode::ThreadSafe> weakPtr;

		FString className = "";
		FString interfaceName = "";
		AndroidJavaObject* javaWrapper = nullptr;

	public:
		RuStoreListener(FString className, FString interfaceName, bool bAsGlobalRef = false);
		virtual ~RuStoreListener();

		long GetId();
		void SetWeakPtr(TWeakPtr<RuStoreListener, ESPMode::ThreadSafe> value);
		TWeakPtr<RuStoreListener, ESPMode::ThreadSafe> GetWeakPtr();

		AndroidJavaObject* GetJWrapper();
	};

	class RUSTORECORE_API RuStoreListenerContainer
	{
	private:
		TArray<TSharedPtr<RuStoreListener, ESPMode::ThreadSafe>> listeners;

	public:
		TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> ListenerBind(RuStoreListener* item);
		void ListenerUnbind(long id);
		void ListenerUnbind(RuStoreListener* item);
		void ListenerUnbind(TSharedPtr<RuStoreListener, ESPMode::ThreadSafe> item);
		void ListenerRemoveAll();
	};
}
