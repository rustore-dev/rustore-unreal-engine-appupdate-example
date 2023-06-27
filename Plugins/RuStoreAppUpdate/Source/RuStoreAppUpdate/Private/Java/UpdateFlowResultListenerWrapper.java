package com.Plugins.RuStoreAppUpdate;

import ru.rustore.unitysdk.appupdate.callbacks.UpdateFlowResultListener;

import android.util.Log;

public class UpdateFlowResultListenerWrapper implements UpdateFlowResultListener
{
    private long cppPointer;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, int response);

    public UpdateFlowResultListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        Log.e("rustore", "AppUpdateInfo: Error message");
        NativeOnFailure(cppPointer, throwable);
    }

    @Override
    public void OnSuccess(int response) {
        Log.e("rustore", "AppUpdateInfo: Success message");
        NativeOnSuccess(cppPointer, response);
    }
}
