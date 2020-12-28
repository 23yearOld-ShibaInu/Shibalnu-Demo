package com.shibalnu.ffmpegrtmp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private var path="rtmp://58.200.131.2:1935/livetv/hunantv"

    private val playerUtils:PlayerUtils = PlayerUtils()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        playerUtils.mdataSource = path
        playerUtils.setSurfaceHolder(surface_view)
        playerUtils.mPlayerCallBack = object :PlayerUtils.PlayerCallBack{
            override fun onPrepared() {
                showLog("准备完成")
                playerUtils.start()
            }

            override fun onError(error: String) { showLog(error) }

        }
    }

    override fun onResume() {
        super.onResume()
        playerUtils.prepare()
    }

    override fun onPause() {
        super.onPause()
        playerUtils.stop()
    }

    override fun onDestroy() {
        super.onDestroy()
        playerUtils.release()
    }

    external fun stringFromJNI(): String

    private fun showLog(msg:String){
        Log.d("Trust",msg)
    }
}
