package com.tck.player


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.WindowManager
import com.tck.player.R.layout.activity_main
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private lateinit var myPlayer: MyPlayer
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
        )
        setContentView(activity_main)

        //3.2.2.1 23
        myPlayer = MyPlayer()
        myPlayer.setSurfaceView(surfaceView)

        btn_start_play.setOnClickListener {
            open()
        }
    }

    private fun open() {

    }


}