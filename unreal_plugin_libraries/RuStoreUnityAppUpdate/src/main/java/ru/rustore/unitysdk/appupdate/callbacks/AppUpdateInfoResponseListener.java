package ru.rustore.unitysdk.appupdate.callbacks;

import ru.rustore.sdk.appupdate.model.AppUpdateInfo;

public interface AppUpdateInfoResponseListener {

    public void OnFailure(Throwable throwable);
    public void OnSuccess(AppUpdateInfo appUpdateInfo);
}