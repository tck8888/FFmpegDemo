package com.tck.player

/**
 *<p>description:</p>
 *<p>created on: 2020/12/1 19:52</p>
 * @author tck
 * @version v3.7.5
 *
 */
object TimeUtil {


    fun secondsToStr(_seconds: Int): String {
        val hours = _seconds / 3600
        val minutes = (_seconds - hours * 3600) / 60
        val seconds = _seconds - hours * 3600 - minutes * 60

        var timeStr = ""

        timeStr += if (hours > 10) {
            "$hours:"
        } else {
            "0$hours:"
        }
        timeStr += if (minutes > 10) {
            "$minutes:"
        } else {
            "0$minutes:"
        }
        timeStr += if (seconds > 10) {
            "$seconds"
        } else {
            "0$seconds"
        }
        return timeStr
    }
}