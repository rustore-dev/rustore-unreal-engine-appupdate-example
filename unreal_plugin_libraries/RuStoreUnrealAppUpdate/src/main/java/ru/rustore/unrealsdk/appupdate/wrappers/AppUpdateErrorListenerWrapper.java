package ru.rustore.unrealsdk.appupdate.wrappers;

import ru.rustore.unrealsdk.core.IRuStoreListener;
import ru.rustore.unrealsdk.core.callbacks.ErrorListener;

public class AppUpdateErrorListenerWrapper implements IRuStoreListener, ErrorListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);

    public AppUpdateErrorListenerWrapper(long cppPointer) {
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

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
