package ru.rustore.unitysdk.core

import android.app.Activity

interface IPlayerProvider {
    fun getCurrentActivity(): Activity
}
