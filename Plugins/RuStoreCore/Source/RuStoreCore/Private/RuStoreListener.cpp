#include "RuStoreListener.h"

long RuStoreListener::counter = 0;

RuStoreListener::RuStoreListener()
{
	id = ++counter;
}

RuStoreListener::~RuStoreListener() { }

long RuStoreListener::GetId()
{
	return id;
}

void RuStoreListener::SetWeakPtr(weak_ptr<RuStoreListener> value)
{
	weakPtr = value;
}

weak_ptr<RuStoreListener> RuStoreListener::GetWeakPtr()
{
	return weakPtr;
}

void RuStoreListenerContainer::ListenerBind(RuStoreListener* item)
{
	shared_ptr<RuStoreListener> sharedPtr(item);
	sharedPtr->SetWeakPtr(sharedPtr);
	listeners.Emplace(sharedPtr);
}

void RuStoreListenerContainer::ListenerUnbind(RuStoreListener* item)
{
	listeners.RemoveAll([&](const shared_ptr<RuStoreListener>& item) { return item->GetId() == item->GetId(); });
}

void RuStoreListenerContainer::ListenerRemoveAll()
{
	listeners.Empty();
}
