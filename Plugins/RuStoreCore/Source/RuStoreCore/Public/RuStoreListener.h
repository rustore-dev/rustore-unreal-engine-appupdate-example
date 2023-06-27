#pragma once

#include "CoreMinimal.h"
#include <memory>

using namespace std;

class RUSTORECORE_API RuStoreListener
{
private:
	static long counter;

	long id = 0;
	weak_ptr<RuStoreListener> weakPtr;

public:
	RuStoreListener();
	virtual ~RuStoreListener();

	long GetId();
	void SetWeakPtr(weak_ptr<RuStoreListener> value);
	weak_ptr<RuStoreListener> GetWeakPtr();
};

class RUSTORECORE_API RuStoreListenerContainer
{
private:
	TArray<shared_ptr<RuStoreListener>> listeners;

public:
	void ListenerBind(RuStoreListener* item);
	void ListenerUnbind(RuStoreListener* item);
	void ListenerRemoveAll();
};
