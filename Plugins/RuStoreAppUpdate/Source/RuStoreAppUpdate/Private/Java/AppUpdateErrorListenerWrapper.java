package com.Plugins.RuStoreAppUpdate;

import ru.rustore.unitysdk.core.callbacks.ErrorListener;

import android.util.Log;

public class AppUpdateErrorListenerWrapper implements ErrorListener
{
    private long cppPointer;

    private native void NativeOnFailure(long pointer, Throwable throwable);

    public AppUpdateErrorListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        Log.e("rustore", "AppUpdateInfo: Error message");
        NativeOnFailure(cppPointer, throwable);
    }
}
