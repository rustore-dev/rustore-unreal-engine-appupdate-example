#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"

class UnrealPlayerImpl
{
private:
	AndroidJavaObject* player;

public:
	UnrealPlayerImpl();
	~UnrealPlayerImpl();

	AndroidJavaObject* GetPlayer();
};
