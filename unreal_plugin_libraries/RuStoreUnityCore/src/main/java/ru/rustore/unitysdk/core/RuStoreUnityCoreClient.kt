package ru.rustore.unitysdk.core

import android.app.Activity
import ru.rustore.sdk.core.util.RuStoreUtils

object RuStoreUnityCoreClient {

    fun isRuStoreInstalled(activity: Activity): Boolean =
        RuStoreUtils.isRuStoreInstalled(activity)

    fun openRuStoreDownloadInstruction(activity: Activity) =
        RuStoreUtils.openRuStoreDownloadInstruction(activity)

    fun openRuStore(activity: Activity) =
        RuStoreUtils.openRuStore(activity)

    fun openRuStoreAuthorization(activity: Activity) =
        RuStoreUtils.openRuStoreAuthorization(activity)
}
