package com.tck.player


/**
 *
 * description:

 * @date 2020/11/24 23:18

 * @author tck88
 *
 * @version v1.0.0
 *
 */
class MyMusicPlayer {

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    private val nativeHandle: Long

    private var onPlayerListener: OnPlayerListener? = null

    init {
        nativeHandle = nativeInit()
    }

    fun setDataSource(url: String) {
        setDataSource(nativeHandle, url)
    }

    fun prepare() {
        onPlayerListener?.onLoad(true)
        Thread { nativePrepare(nativeHandle) }.start()
    }

    fun start() {
        Thread { nativeStart(nativeHandle) }.start()
    }

    fun pause() {
        nativePause(nativeHandle)
        onPlayerListener?.onPause()
    }

    fun resume() {
        nativeResume(nativeHandle)
        onPlayerListener?.onResume()
    }

    fun onCallJavaPrepared() {
        onPlayerListener?.onPrepare()
    }

    fun onCallLoad(load: Boolean) {
        onPlayerListener?.onLoad(load)
    }

    fun setOnPreparedListener(onPlayerListener: OnPlayerListener?) {
        this.onPlayerListener = onPlayerListener;
    }

    private external fun nativeInit(): Long
    private external fun setDataSource(nativeHandle: Long, url: String)
    private external fun nativePrepare(nativeHandle: Long)
    private external fun nativeStart(nativeHandle: Long)
    private external fun nativePause(nativeHandle: Long)
    private external fun nativeResume(nativeHandle: Long)

}