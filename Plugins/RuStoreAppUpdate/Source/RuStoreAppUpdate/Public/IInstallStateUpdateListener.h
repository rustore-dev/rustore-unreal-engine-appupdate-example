#pragma once

#include "CoreMinimal.h"
#include "FUInstallState.h"

class IInstallStateUpdateListener {
public:
	virtual void OnStateUpdated(FUInstallState state) = 0;
};
