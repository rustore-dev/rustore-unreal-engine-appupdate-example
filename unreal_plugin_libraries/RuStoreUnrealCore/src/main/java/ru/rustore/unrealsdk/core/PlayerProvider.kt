package ru.rustore.unrealsdk.core

import android.app.Activity

object PlayerProvider {

    private var externalProvider: IPlayerProvider? = null

    fun getCurrentActivity(): Activity? {
        return externalProvider?.getCurrentActivity()
    }

    fun setExternalProvider(provider: IPlayerProvider) {
        externalProvider = provider
    }
}
