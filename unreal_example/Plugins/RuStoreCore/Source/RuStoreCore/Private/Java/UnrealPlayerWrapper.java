package com.Plugins.RuStoreCore;

import android.app.Activity;
import android.util.Log;
import ru.rustore.unrealsdk.core.IPlayerProvider;

public class UnrealPlayerWrapper implements IRuStoreListener, IPlayerProvider {

    private native Activity NativeOnActivityRequest();

    public UnrealPlayerWrapper(long cppPointer) {
    }

    public Activity getCurrentActivity() {
        return NativeOnActivityRequest();
    }

    public void DisposeCppPointer() {
    }
}
