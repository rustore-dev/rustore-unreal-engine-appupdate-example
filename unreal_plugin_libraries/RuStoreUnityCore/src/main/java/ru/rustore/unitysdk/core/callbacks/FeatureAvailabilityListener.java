package ru.rustore.unitysdk.core.callbacks;

import ru.rustore.sdk.core.feature.model.FeatureAvailabilityResult;

public interface FeatureAvailabilityListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess(FeatureAvailabilityResult response);
}