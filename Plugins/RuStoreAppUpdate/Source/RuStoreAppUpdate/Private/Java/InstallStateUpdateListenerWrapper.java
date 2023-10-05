// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreAppUpdate;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.sdk.appupdate.model.InstallState;
import ru.rustore.sdk.appupdate.listener.InstallStateUpdateListener;

public class InstallStateUpdateListenerWrapper implements IRuStoreListener, InstallStateUpdateListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnStateUpdated(long pointer, InstallState state);

    public InstallStateUpdateListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void onStateUpdated(InstallState state) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnStateUpdated(cppPointer, state);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
