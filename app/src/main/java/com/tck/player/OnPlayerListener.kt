package com.tck.player

/**
 *<p>description:</p>
 *<p>created on: 2020/11/26 20:27</p>
 * @author tck
 *
 */
interface OnPlayerListener {

    fun onLoad(load: Boolean)

    fun onPrepare()

    fun onPause()

    fun onResume()

    fun onTimeInfo(currentTime:Int,totalTime:Int)
}