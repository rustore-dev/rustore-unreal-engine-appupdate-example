#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"
#include "IInstallStateUpdateListener.h"

class InstallStateUpdateListener
{
private:
    long cppPointer;
    IInstallStateUpdateListener* _listener = nullptr;
    
public:
    AndroidJavaObject* jlistener = nullptr;

    InstallStateUpdateListener(IInstallStateUpdateListener* listener);
    ~InstallStateUpdateListener();

    void OnStateUpdated(AndroidJavaObject* stateObject);
};
