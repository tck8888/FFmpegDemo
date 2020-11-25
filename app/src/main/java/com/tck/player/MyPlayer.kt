package com.tck.player

import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

/**
 *
 * description:

 * @date 2020/11/24 23:18

 * @author tck88
 *
 * @version v1.0.0
 *
 */
class MyPlayer : SurfaceHolder.Callback {
    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    private var surfaceHolder: SurfaceHolder? = null

    fun setSurfaceView(surfaceView: SurfaceView) {
        if (surfaceHolder != null) {
            surfaceHolder?.removeCallback(this)
        }
        surfaceHolder=surfaceView.holder
        surfaceHolder?.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        TODO("Not yet implemented")
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        TODO("Not yet implemented")
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        TODO("Not yet implemented")
    }
}