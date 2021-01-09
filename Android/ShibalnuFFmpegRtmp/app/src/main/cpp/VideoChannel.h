//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H
#define SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H

#include "BaseChannel.h"

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/time.h>
}



class VideoChannel : public BaseChannel {

public:
    VideoChannel(int stream_index,
                 AVCodecContext *pContext);


    virtual ~VideoChannel();

    void start();

    void stop();

    void video_decode();

    void video_player();
};


#endif //SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H
