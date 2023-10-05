// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreCore;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult;
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener;

public class FeatureAvailabilityListenerWrapper implements IRuStoreListener, FeatureAvailabilityListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer, FeatureAvailabilityResult response);

    public FeatureAvailabilityListenerWrapper(long cppPointer) {
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
    public void OnSuccess(FeatureAvailabilityResult response) {
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
