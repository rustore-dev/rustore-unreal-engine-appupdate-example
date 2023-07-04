// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreAppUpdate;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.unitysdk.appupdate.callbacks.AppUpdateInfoResponseListener;
import ru.rustore.sdk.appupdate.model.AppUpdateInfo;

public class AppUpdateInfoResponseListenerWrapper implements IRuStoreListener, AppUpdateInfoResponseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, AppUpdateInfo response);

    public AppUpdateInfoResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(AppUpdateInfo response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnSuccess(cppPointer, response);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
