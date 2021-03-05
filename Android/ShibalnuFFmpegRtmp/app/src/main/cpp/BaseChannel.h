//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_BASECHANNEL_H
#define SHIBALNUFFMPEGRTMP_BASECHANNEL_H

#include "safe_queue.h"
#include "pthread.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

extern "C"{
#include "ffmpeg/include/libavcodec/avcodec.h"
#include <libavutil/time.h>
#include <libswresample/swresample.h>
};
typedef void (*RenderCallback) (uint8_t *, int, int, int);
class BaseChannel {
public:
    int stram_index;
    AVCodecContext * avCodecContext;
    BaseChannel(int stram_index, AVCodecContext *pContext,AVRational time_base){
        this->stram_index = stram_index;
        this->avCodecContext = pContext;
        this->time_base = time_base;
        packets.setReleaseCallback(releaseAVPacket);
        frames.setReleaseCallback(releaseAVFrame);
    }

    /**
 * 释放AVPacket 队列
 * @param avPacket
 */
    static void releaseAVPacket(AVPacket ** avPacket) {
        if (avPacket) {
            av_packet_free(avPacket);
            *avPacket = 0;
        }
    }


    static void releaseAVFrame(AVFrame ** pAvFrame){
        if(pAvFrame){
            av_frame_free(pAvFrame);
            *pAvFrame = 0;
        }
    }

//    virtual ~BaseChannel();
    //音频 aac  视频 h264
    SafeQueue<AVPacket *> packets;

    //音频 pcm  视频 yuv
    SafeQueue<AVFrame *> frames;
    bool isPlay = 1;

    pthread_t  pid_decode = 0;
    pthread_t  pid_play = 0;
    void setRenderCallback(RenderCallback renderCallback);

    RenderCallback renderCallback;

    //时间基 FFmpeg内部的时间
    //例如： 以视频为例：24fps == 一秒钟24帧 时间基就表示 每一帧 == 时间基(1/24)
    AVRational time_base;
    double audioTime;//每一帧，音频计算后的时间值
    double videoTime;//每一帧，视频计算后的时间值
};


#endif //SHIBALNUFFMPEGRTMP_BASECHANNEL_H
