package ru.rustore.unitysdk.appupdate.callbacks;

public interface UpdateFlowResultListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess(int result);
}