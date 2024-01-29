package ru.rustore.unitysdk.core.wrappers

import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult
import ru.rustore.unitysdk.core.IRuStoreListener
import ru.rustore.unitysdk.core.callbacks.FeatureAvailabilityListener

class FeatureAvailabilityListenerWrapper(cppPointer: Long) : IRuStoreListener, FeatureAvailabilityListener {
    private val mutex = Any()
    private var cppPointer: Long = 0
    private external fun NativeOnFailure(pointer: Long, throwable: Throwable)
    private external fun NativeOnSuccess(pointer: Long, response: FeatureAvailabilityResult)

    init {
        this.cppPointer = cppPointer
    }

    override fun OnFailure(throwable: Throwable) {
        synchronized(mutex) {
            if (cppPointer != 0L) {
                NativeOnFailure(cppPointer, throwable)
            }
        }
    }

    override fun OnSuccess(response: FeatureAvailabilityResult) {
        synchronized(mutex) {
            if (cppPointer != 0L) {
                NativeOnSuccess(cppPointer, response)
            }
        }
    }

    override fun DisposeCppPointer() {
        synchronized(mutex) { cppPointer = 0 }
    }
}
