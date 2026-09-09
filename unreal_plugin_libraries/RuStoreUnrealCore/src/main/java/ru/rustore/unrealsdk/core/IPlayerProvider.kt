package ru.rustore.unrealsdk.core

import android.app.Activity

interface IPlayerProvider {
    fun getCurrentActivity(): Activity
}
