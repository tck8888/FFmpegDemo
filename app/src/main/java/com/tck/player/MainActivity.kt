package com.tck.player


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import com.tck.player.R.layout.activity_main
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {

    private lateinit var myMusicPlayer: MyMusicPlayer
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
        )
        setContentView(activity_main)

        //3.2.2.1 23
        myMusicPlayer = MyMusicPlayer()

        myMusicPlayer.setOnPreparedListener(object : OnPreparedListener {
            override fun onPrepare() {
                Log.d("tck6666", "onPrepare")
            }
        })
        btn_start_play.setOnClickListener {
            open()
        }
    }

    private fun open() {
        Thread {
            myMusicPlayer.setDataSource("${cacheDir}${File.separator}1.mp3")
            myMusicPlayer.prepare()
        }.start()
    }


}