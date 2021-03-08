//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H
#define SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H

#include "BaseChannel.h"
#include "AudioChannel.h"

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/time.h>
}



class VideoChannel : public BaseChannel {

public:
    VideoChannel(int stream_index, AVCodecContext *pContext, AVRational rational, int i,JNICallBack * jniCallBack);


    virtual ~VideoChannel();

    void start();

    void stop();

    void video_decode();

    void video_player();

    void setAudioChannel(AudioChannel * audioChannel);

private:
    int fps;
    AudioChannel * audioChannel;
};


#endif //SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H
