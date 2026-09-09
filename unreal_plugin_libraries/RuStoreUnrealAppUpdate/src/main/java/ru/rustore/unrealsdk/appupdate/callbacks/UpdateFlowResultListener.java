package ru.rustore.unrealsdk.appupdate.callbacks;

public interface UpdateFlowResultListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess(int result);
}
