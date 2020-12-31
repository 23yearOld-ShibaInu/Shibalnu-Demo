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

typedef void (*RenderCallback) (uint8_t *, int, int, int);

class VideoChannel : public BaseChannel {

public:
    VideoChannel(int stream_index,
                 AVCodecContext *pContext);


    virtual ~VideoChannel();

    void start();

    void stop();

    void video_decode();

    void video_player();

    void setRenderCallback(RenderCallback renderCallback);

private:
    RenderCallback renderCallback;
};


#endif //SHIBALNUFFMPEGRTMP_VIDEOCHANNEL_H
