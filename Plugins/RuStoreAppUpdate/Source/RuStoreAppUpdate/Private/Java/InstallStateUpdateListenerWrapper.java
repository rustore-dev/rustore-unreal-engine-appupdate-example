package com.Plugins.RuStoreAppUpdate;

import ru.rustore.sdk.appupdate.model.InstallState;
import ru.rustore.sdk.appupdate.listener.InstallStateUpdateListener;

import android.util.Log;

public class InstallStateUpdateListenerWrapper implements InstallStateUpdateListener
{
    private long cppPointer;

    private native void NativeOnStateUpdated(long pointer, InstallState state);

    public InstallStateUpdateListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void onStateUpdated(InstallState state) {
        Log.e("rustore", "InstallState: On state updated");
        NativeOnStateUpdated(cppPointer, state);
    }
}
