package com.Plugins.RuStoreCore;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener;
import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult;

import android.util.Log;

public class FeatureAvailabilityListenerWrapper implements IResponseListenerWrapper, FeatureAvailabilityListener
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
                Log.e("rustore", "FeatureAvailabilityResult: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess(FeatureAvailabilityResult response) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "FeatureAvailabilityResult: Success message");
                NativeOnSuccess(cppPointer, response);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            Log.e("rustore", "FeatureAvailabilityResult: Dispose pointer");
            cppPointer = 0;
        }
    }
}
