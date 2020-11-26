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

    private var onPreparedListener: OnPreparedListener? = null

    init {
        nativeHandle = nativeInit()
    }

    fun setDataSource(url: String) {
        setDataSource(nativeHandle, url)
    }

    fun prepare() {
        nativePrepare(nativeHandle)
    }

    fun start() {
        nativeStart(nativeHandle)
    }

    fun onCallJavaPrepared() {
        onPreparedListener?.onPrepare()
    }

    fun setOnPreparedListener(onPreparedListener: OnPreparedListener?) {
        this.onPreparedListener = onPreparedListener;
    }

    private external fun nativeInit(): Long
    private external fun setDataSource(nativeHandle: Long, url: String)
    private external fun nativePrepare(nativeHandle: Long)
    private external fun nativeStart(nativeHandle: Long)

}