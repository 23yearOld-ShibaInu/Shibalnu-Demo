//
// Created by Trust on 12/25/20.
//

#ifndef SHIBALNUFFMPEGRTMP_TRUSTPLAYER_H
#define SHIBALNUFFMPEGRTMP_TRUSTPLAYER_H

#include <cstring>
#include "VideoChannel.h"
#include "AudioChannel.h"
#include "JNICallBack.h"

#include "Mr_Li_Log.h"

extern "C"{
    #include <libavformat/avformat.h>
};
class TrustPlayer {
public:
    TrustPlayer(const char *string,JNICallBack * jniCallBack);

    virtual ~TrustPlayer();


    void prepare();

    void prepare_();


    void start();
    void start_();
    void setRenderCallback(RenderCallback renderCallback);
    int getDuration();
private:
    char * data_source = 0;
    pthread_t pid_prepare = 0;
    pthread_t pid_start = 0;
    AVFormatContext *avFormatContext = 0;
    JNICallBack * jniCallBack = 0;
    VideoChannel * videoChannel = 0;
    AudioChannel * audioChannel = 0;
    RenderCallback renderCallback = 0;
    bool isPlayer = 0;
    int duration = 0;
};


#endif //SHIBALNUFFMPEGRTMP_TRUSTPLAYER_H
