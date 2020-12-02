package com.tck.player

import android.util.Log

/**
 *<p>description:</p>
 *<p>created on: 2020/12/1 16:59</p>
 * @author tck
 * @version v3.7.5
 *
 */
open class OnPlayerListenerAdapter : OnPlayerListener {
    override fun onLoad(load: Boolean) {

    }

    override fun onPrepare() {

    }

    override fun onPause() {

    }

    override fun onResume() {

    }

    override fun onTimeInfo(currentTime: Int, totalTime: Int) {

    }

    override fun onError(code: Int, msg: String) {
        Log.d("tck6666", "OnPlayerListener-->onError:code=$code,msg=$msg")
    }
}