// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AndroidJavaObject.h"
#include "URuStoreInstallStateUpdateListenerInterface.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
    class InstallStateUpdateListenerImpl : public RuStoreListener
    {
    protected:
        TFunction<void(long, TSharedPtr<FURuStoreInstallState, ESPMode::ThreadSafe>)> _onStateUpdated;

    public:
        InstallStateUpdateListenerImpl(
            TFunction<void(long, TSharedPtr<FURuStoreInstallState, ESPMode::ThreadSafe>)> onStateUpdated
        ) : RuStoreListener("com/Plugins/RuStoreAppUpdate/InstallStateUpdateListenerWrapper", "ru/rustore/sdk/appupdate/listener/InstallStateUpdateListener")
        {
            _onStateUpdated = onStateUpdated;
        }

        virtual ~InstallStateUpdateListenerImpl();

        void OnStateUpdated(AndroidJavaObject* stateObject);
    };
}
