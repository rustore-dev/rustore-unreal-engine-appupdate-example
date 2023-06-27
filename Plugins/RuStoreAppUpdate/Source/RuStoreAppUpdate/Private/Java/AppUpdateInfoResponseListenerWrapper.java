package com.Plugins.RuStoreAppUpdate;

import ru.rustore.unitysdk.appupdate.callbacks.AppUpdateInfoResponseListener;
import ru.rustore.sdk.appupdate.model.AppUpdateInfo;

import android.util.Log;

public class AppUpdateInfoResponseListenerWrapper implements AppUpdateInfoResponseListener
{
    private long cppPointer;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, AppUpdateInfo response);

    public AppUpdateInfoResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        Log.e("rustore", "AppUpdateInfo: Error message");
        NativeOnFailure(cppPointer, throwable);
    }

    @Override
    public void OnSuccess(AppUpdateInfo response) {
        Log.e("rustore", "AppUpdateInfo: Success message");
        NativeOnSuccess(cppPointer, response);
    }
}
