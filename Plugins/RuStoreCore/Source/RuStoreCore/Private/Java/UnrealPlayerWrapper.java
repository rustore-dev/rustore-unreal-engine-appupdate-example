package com.Plugins.RuStoreCore;

import android.app.Activity;
import ru.rustore.unitysdk.core.IPlayerProvider;

import android.util.Log;

public class UnrealPlayerWrapper implements IPlayerProvider {

    private native Activity NativeOnActivityRequest();

    public UnrealPlayerWrapper() {
    }

    @Override
    public void init(long cppPointer) {
    }

    @Override
    public Activity getCurrentActivity() {
        return NativeOnActivityRequest();
    }
}
