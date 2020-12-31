//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_BASECHANNEL_H
#define SHIBALNUFFMPEGRTMP_BASECHANNEL_H

#include "safe_queue.h"
#include "pthread.h"

extern "C"{
#include "ffmpeg/include/libavcodec/avcodec.h"
};

class BaseChannel {
public:
    int stram_index;
    AVCodecContext * avCodecContext;
    BaseChannel(int stram_index, AVCodecContext *pContext){
        this->stram_index = stram_index;
        this->avCodecContext = pContext;
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

    pthread_t  pid_video_decode = 0;
    pthread_t  pid_video_play = 0;
};


#endif //SHIBALNUFFMPEGRTMP_BASECHANNEL_H
