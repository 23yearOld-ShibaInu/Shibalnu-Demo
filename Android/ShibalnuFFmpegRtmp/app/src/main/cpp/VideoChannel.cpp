//
// Created by Trust on 12/27/20.
//

#include "VideoChannel.h"

void * task_video_decode (void * pvoid){
    VideoChannel * videoChannel = static_cast<VideoChannel *>(pvoid);
    videoChannel->video_decode();
    return  0;
}

void * task_video_play (void * pvoid){
    VideoChannel * videoChannel = static_cast<VideoChannel *>(pvoid);
    videoChannel->video_player();
    return  0;
}

VideoChannel::VideoChannel(int stream_index,AVCodecContext *pContext) : BaseChannel(stream_index, pContext) {

}

VideoChannel::~VideoChannel() {

}


//从队列取出 未解码的数据
//1:解码
//2:播放
void VideoChannel::start() {
    //通知队列开始执行
    this->packets.setFlag(1);
    this->frames.setFlag(1);

    //解码线程
    pthread_create(&pid_video_decode,0,task_video_decode,this);
    //播放线程
    pthread_create(&pid_video_play,0,task_video_play,this);
}

void VideoChannel::stop() {

}

void VideoChannel::video_decode() {
    AVPacket * avPacket;
    while (isPlay){
        int ret = this->packets.pop(avPacket);
        if(!isPlay){
            break;
        }

        if(!ret){
            continue;
        }

        //取出未解码数据
        ret = avcodec_send_packet(this->avCodecContext,avPacket);

        if(ret){
            //失败
            break;
        }

        AVFrame * avFrame = av_frame_alloc();
        ret = avcodec_receive_frame(this->avCodecContext,avFrame);
        if(ret == AVERROR(EAGAIN)){
            //代表 I帧完整 帧取的不完整  P B 会进入这里 直到去到完整的为止
            continue;
        }else if(ret != 0){
            //释放工作
            break;
        }


        //取到了 原始数据
        this->frames.push(avFrame);
    }

    //释放

}

void VideoChannel::video_player() {
    //最原始的视频数据 不能直接显示 yuv
    //yuv -> rgba
    //转化上下文
    SwsContext * swsContext = sws_getContext(
            //原始宽高格式
            this->avCodecContext->width,
            this->avCodecContext->height,
            this->avCodecContext->pix_fmt,
            //显示目标的信息 (最好和原始保持一致)
            this->avCodecContext->width,
            this->avCodecContext->height,
            AV_PIX_FMT_RGBA,
            //速率
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
            );
    AVFrame * avFrame = 0;
    while (isPlay){

        int ret = frames.pop(avFrame);
    }
}

