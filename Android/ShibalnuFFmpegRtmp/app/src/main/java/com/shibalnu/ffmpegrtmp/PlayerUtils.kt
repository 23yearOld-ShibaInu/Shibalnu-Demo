package com.shibalnu.ffmpegrtmp

import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

class PlayerUtils :SurfaceHolder.Callback{
    companion object {
        init {
            System.loadLibrary("trust-player")
        }
    }

    lateinit var mdataSource:String
    private var mSurfaceHolder: SurfaceHolder? = null
    var mPlayerCallBack:PlayerCallBack? = null

    fun setSurfaceHolder(view:SurfaceView){
        mSurfaceHolder?.removeCallback(this)

        mSurfaceHolder = view.holder
        mSurfaceHolder?.addCallback(this)
    }

    override fun surfaceChanged(p0: SurfaceHolder, p1: Int, p2: Int, p3: Int) {
    }

    override fun surfaceDestroyed(p0: SurfaceHolder) {
    }

    override fun surfaceCreated(surface: SurfaceHolder) {
        setSurfaceNative(surface.surface)
    }

    /**
     * 上层区域
     */

    fun prepare(){
        prepareNative(mdataSource)
    }

    fun start(){
        startNative()
    }

    fun stop(){
        stopNative()
    }

    fun release(){
        releaseNative()
    }


    /**
     * native区域
     */

    external fun prepareNative(dataStource:String)
    external fun startNative()
    external fun stopNative()
    external fun releaseNative()
    external fun getFFmpegVersion():String
    //底层操作surface对象
    external fun setSurfaceNative(surface: Surface)


    /**
     * native 调用上层
     */
    fun onPrepared(thread_id:Int){
        mPlayerCallBack?.onPrepared()
    }

    fun onError(thread_id:Int,errorCode:Int){
        val s = when (errorCode) {
            FFMPEG_CAN_NOT_OPEN_URL -> { "打不开视频源" }
            FFMPEG_CAN_NOT_FIND_STREAMS -> { "找不到媒体信息" }
            FFMPEG_FIND_DECODER_FAIL -> { "找不到解码器" }
            FFMPEG_ALLOC_CODEC_CONTEXT_FAIL -> { "无法根据解码器创建上下文" }
            FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL -> { "根据流量信息 配置上下文参数失败" }
            FFMPEG_OPEN_DECOOER_FAIL -> { "打开解码器失败" }
            FFMPEG_NO_MEDIA -> { "没有音频" }
            FFMPEG_READ_PACKETS_FAIL -> { "读取媒体数据包失败" }
            else -> { "" }
        }
        mPlayerCallBack?.onError(s)
    }

    interface PlayerCallBack{
        fun onPrepared()
        fun onError(error:String)
    }
}