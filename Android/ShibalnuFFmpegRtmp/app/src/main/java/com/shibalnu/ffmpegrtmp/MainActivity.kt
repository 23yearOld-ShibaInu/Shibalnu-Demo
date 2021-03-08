package com.shibalnu.ffmpegrtmp

import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.view.View
import android.widget.SeekBar
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {
    private val PATH = Environment.getExternalStorageDirectory()
        .toString() + File.separator + "test.mp4"
//    private var path="rtmp://58.200.131.2:1935/livetv/hunantv"

    private var path1 = Environment.getExternalStorageDirectory()
        .toString() + File.separator + "speak.mp4"


    private var duration = 0
    private var isTouch = false
    private var isSeek = false

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
                //直播的话 duration = 0
                //本地视频文件 duration != 0
                if (duration!=0) {
                    runOnUiThread {
                        seek_bar.visibility = View.VISIBLE
                    }
                }

                playerUtils.start()
            }

            override fun onError(error: String) { showLog(error) }
            override fun onProgress(progress: Int) {

                if (!isTouch) {
                    runOnUiThread {
                        val duration = playerUtils.getDuration()
                        if(duration !=0){
                            if(isSeek){
                                isSeek = false
                                return@runOnUiThread
                            }
                            seek_bar.progress = progress * 100 / duration
                        }
                    }
                }

            }

        }

        seek_bar.setOnSeekBarChangeListener(object :SeekBar.OnSeekBarChangeListener{
            override fun onProgressChanged(seekBar: SeekBar?, p1: Int, p2: Boolean) {
                    showLog("onProgressChanged :${seekBar?.progress} p1:$p1 p2:$p2")
            }

            override fun onStartTrackingTouch(p0: SeekBar?) {
                isTouch = true
            }

            override fun onStopTrackingTouch(p0: SeekBar?) {
                isSeek = true
                isTouch = false
            }

        })
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
