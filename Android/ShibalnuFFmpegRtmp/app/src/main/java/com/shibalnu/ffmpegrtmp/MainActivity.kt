package com.shibalnu.ffmpegrtmp

import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {
    private val PATH = Environment.getExternalStorageDirectory()
        .toString() + File.separator + "test.mp4"
//    private var path="rtmp://58.200.131.2:1935/livetv/hunantv"

    private var path1 = Environment.getExternalStorageDirectory()
        .toString() + File.separator + "speak.mp4"
    private val playerUtils:PlayerUtils = PlayerUtils()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
//        val msg = "speech&laucher|跳转&蓝牙页面;关闭&ble;退出&蓝牙页面;跳转&地图页面".trim()



        playerUtils.setSurfaceHolder(surface_view)
        val path = PATH
        playerUtils.mdataSource = path!!
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
