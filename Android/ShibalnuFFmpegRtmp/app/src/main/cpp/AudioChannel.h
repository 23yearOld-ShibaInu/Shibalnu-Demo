//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_AUDIOCHANNEL_H
#define SHIBALNUFFMPEGRTMP_AUDIOCHANNEL_H

#include "BaseChannel.h"

class AudioChannel: public BaseChannel {
public:
    AudioChannel(int stream_index, AVCodecContext *avCodecContext, AVRational rational,JNICallBack * jniCallBack);
    virtual ~AudioChannel();
    void start();
    void stop();
    void audio_decode();
    void audio_player();
    int getPcm();

    uint8_t  * out_buffers = 0;

    int out_channels;
    int out_sample_size;
    int out_sample_rate;
    int out_buffers_size;
private:
    //引擎
    SLObjectItf engineObject;
    //引擎接口
    SLEngineItf engineInterface;
    //混音器
    SLObjectItf outputMixObject;
    //播放器
    SLObjectItf bqPlayerObject;
    //播放器接口
    SLPlayItf bqPlayerPlay;
    //获取播放器队列接口
    SLAndroidSimpleBufferQueueItf  bqPlayerBufferQueue;

    //重采样 == 音频转换
    SwrContext * swr_ctx;
};


#endif //SHIBALNUFFMPEGRTMP_AUDIOCHANNEL_H
