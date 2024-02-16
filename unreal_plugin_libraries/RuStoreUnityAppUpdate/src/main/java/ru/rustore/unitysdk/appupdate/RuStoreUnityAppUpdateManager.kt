package ru.rustore.unitysdk.appupdate;

import ru.rustore.sdk.appupdate.listener.InstallStateUpdateListener
import ru.rustore.sdk.appupdate.manager.RuStoreAppUpdateManager
import ru.rustore.sdk.appupdate.manager.factory.RuStoreAppUpdateManagerFactory
import ru.rustore.sdk.appupdate.model.AppUpdateInfo
import ru.rustore.sdk.appupdate.model.AppUpdateOptions
import ru.rustore.sdk.appupdate.model.AppUpdateType
import ru.rustore.unitysdk.appupdate.callbacks.AppUpdateInfoResponseListener
import ru.rustore.unitysdk.appupdate.callbacks.UpdateFlowResultListener
import ru.rustore.unitysdk.core.PlayerProvider
import ru.rustore.unitysdk.core.callbacks.ErrorListener

object RuStoreUnityAppUpdateManager {

    private lateinit var updateManager: RuStoreAppUpdateManager
    private var appUpdateInfo: AppUpdateInfo? = null
    private var isInitialized:Boolean = false
    
    fun init(metricType: String) {
        PlayerProvider.getCurrentActivity()?.run {
            updateManager = RuStoreAppUpdateManagerFactory.create(
                context = application,
                internalConfig = mapOf("type" to metricType)
            )
            isInitialized = true
        }
    }

    fun getAppUpdateInfo(listener: AppUpdateInfoResponseListener) {
        updateManager.getAppUpdateInfo().addOnSuccessListener { result ->
            appUpdateInfo = result
            listener.OnSuccess(result)
        }.addOnFailureListener {
            throwable -> listener.OnFailure(throwable)
        }
    }

    fun isImmediateUpdateAllowed() : Boolean {
        appUpdateInfo?.let {
            return it.isUpdateTypeAllowed(AppUpdateType.IMMEDIATE)
        }
        return false;
    }

    fun registerListener(listener: InstallStateUpdateListener) {
        updateManager.registerListener(listener)
    }

    fun unregisterListener(listener: InstallStateUpdateListener) {
        updateManager.unregisterListener(listener)
    }

    @Deprecated("This function is deprecated. Use the new functions startUpdateFlowDelayed, startUpdateFlowSilent or startUpdateImmediate.")
    fun startUpdateFlow(listener: UpdateFlowResultListener) {
        appUpdateInfo?.let {
            updateManager.startUpdateFlow(it, AppUpdateOptions.Builder().build())
                .addOnSuccessListener {
                    resultCode -> listener.OnSuccess(resultCode)
                }
                .addOnFailureListener {
                    throwable -> listener.OnFailure(throwable)
                }
        }
    }

    fun startUpdateFlowImmediate(listener: UpdateFlowResultListener) {
        startUpdateFlow(listener, AppUpdateOptions.Builder().appUpdateType(AppUpdateType.IMMEDIATE).build())
    }

    fun startUpdateFlowSilent(listener: UpdateFlowResultListener) {
        startUpdateFlow(listener, AppUpdateOptions.Builder().appUpdateType(AppUpdateType.SILENT).build())
    }

    fun startUpdateFlowDelayed(listener: UpdateFlowResultListener) {
        startUpdateFlow(listener, AppUpdateOptions.Builder().build())
    }

    private fun startUpdateFlow(listener: UpdateFlowResultListener, appUpdateOptions: AppUpdateOptions) {
        appUpdateInfo?.let {
            updateManager.startUpdateFlow(it, appUpdateOptions)
                .addOnSuccessListener {
                        resultCode -> listener.OnSuccess(resultCode)
                }
                .addOnFailureListener {
                        throwable -> listener.OnFailure(throwable)
                }
        }
    }

    fun completeUpdate(listener: ErrorListener) {
        updateManager.completeUpdate().addOnFailureListener {
            throwable -> listener.OnFailure(throwable)
        }
    }
}
