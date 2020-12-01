package com.tck.player


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import com.tck.player.databinding.ActivityMainBinding
import java.io.File

class MainActivity : AppCompatActivity() {

    companion object{
        const val TAG="tck6666"
    }

    private lateinit var binding: ActivityMainBinding

    private lateinit var myMusicPlayer: MyMusicPlayer
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
        )
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        //3.2.2.1 23
        myMusicPlayer = MyMusicPlayer()

        myMusicPlayer.setOnPreparedListener(object : OnPlayerListenerAdapter() {
            override fun onPrepare() {
                super.onPrepare()
                Log.d(TAG, "onPrepare")
                myMusicPlayer.start()
            }

            override fun onLoad(load: Boolean) {
                super.onLoad(load)
                if (load) {
                    Log.d(TAG, "加载中...")
                } else {
                    Log.d(TAG, "播放中...")
                }
            }

            override fun onPause() {
                super.onPause()
                Log.d(TAG, "暂停中...")
            }

            override fun onResume() {
                super.onResume()
                Log.d(TAG, "播放中...")
            }
        })
        binding.btnStartPlay.setOnClickListener {
            open()
        }

        binding.btnPausePlay.setOnClickListener {
            pause()
        }

        binding.btnResumePlay.setOnClickListener {
            resume()
        }
    }

    private fun pause(){
        myMusicPlayer.pause()
    }

    private fun resume(){
        myMusicPlayer.resume()
    }

    private fun open() {
        myMusicPlayer.setDataSource("${cacheDir}${File.separator}1.mp3")
        myMusicPlayer.prepare()
    }


}