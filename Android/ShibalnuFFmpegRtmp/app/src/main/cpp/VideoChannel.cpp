//
// Created by Trust on 12/27/20.
//


#include "VideoChannel.h"


//丢包(丢帧)的函数指针 具体实现 frame
void dropAVFrame(queue<AVFrame *> &qq){
    if(!qq.empty()){
        //丢包
        AVFrame * frame = qq.front();
        BaseChannel::releaseAVFrame(&frame);//释放
        qq.pop();
    }
}


//丢包(丢帧)的函数指针 具体实现 packet
void dropAVPacket(queue<AVPacket *> &qq){
    if (!qq.empty()){
        AVPacket * packet = qq.front();
        //BaseChannel::releaseAVPacket(&packet);//有可能把关键帧丢了
        if(packet->flags != AV_PKT_FLAG_KEY){//不等于关键帧 丢掉
            BaseChannel::releaseAVPacket(&packet);
            qq.pop();
        }

    }
}

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

VideoChannel::VideoChannel(int stream_index, AVCodecContext *pContext, AVRational time_base, int fps,JNICallBack * jniCallBack)
        : BaseChannel(stream_index, pContext, time_base,jniCallBack) {
    this->fps = fps;

    this->frames.setSyncCallback(dropAVFrame);
    this->packets.setSyncCallback(dropAVPacket);
}

VideoChannel::~VideoChannel() {}


//从队列取出 未解码的数据
//1:解码
//2:播放
void VideoChannel::start() {
    isPlay = 1;
    //通知队列开始执行
    this->packets.setFlag(1);
    this->frames.setFlag(1);

    //解码线程
    pthread_create(&pid_decode,0,task_video_decode,this);
    //播放线程
    pthread_create(&pid_play,0,task_video_play,this);
}

void VideoChannel::stop() {

}

void VideoChannel::video_decode() {
    AVPacket * avPacket = 0;
    while (isPlay){

        // 生产快  消费慢
        // 消费速度比生成速度慢（生成100，只消费10个，这样队列会爆）
        // 内存泄漏点2，解决方案：控制队列大小q
        if (isPlay && frames.queueSize() > 100) {
            // 休眠 等待队列中的数据被消费
            av_usleep(10 * 1000);
            continue;
        }

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

        releaseAVPacket(&avPacket);

        AVFrame * avFrame = av_frame_alloc();
        ret = avcodec_receive_frame(this->avCodecContext,avFrame);
        if(ret == AVERROR(EAGAIN)){
            //代表 I帧完整 帧取的不完整  P B 会进入这里 直到  取到完整的为止
            releaseAVFrame(&avFrame);
            continue;
        }else if(ret != 0){
            //释放工作
            releaseAVFrame(&avFrame);
            break;
        }
        //取到了 原始数据
        this->frames.push(avFrame);
    }

    //释放
    releaseAVPacket(&avPacket);
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
            //速率 例子中的选项  稳定
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
            );



    uint8_t  * dst_data[4]; //rgba
    int dst_linesize[4];//垂直刷新的 rgba
    AVFrame * avFrame = 0;//存放原始数据 yuv

    //初始化 dst_data  dst_linesize  同时指定格式
    av_image_alloc(dst_data,dst_linesize,avCodecContext->width,
            avCodecContext->height,AV_PIX_FMT_RGBA,1);

    double delay_time_per_frame = 1.0 / fps;
    //一帧一帧的把原始数据格式转换成ragb 在一帧一帧渲染到屏幕上
    while (isPlay){

        int ret = frames.pop(avFrame);

        //如果停止播放、跳出循环、出循环、需要释放
        if(!isPlay){
            break;
        }

        if(!ret){
            continue;
        }

        //格式转换(yuv -> rgba)  frame->data ==yuv原始数据   dst_data rgba格式
        //垂直刷新 只有高度没有宽度
        sws_scale(swsContext,avFrame->data,
                avFrame->linesize,0,avCodecContext->height,dst_data,dst_linesize);

        //控制视频播放速率
        //在视频渲染前，根据 FPS 来控制视频帧

        //获取当前帧的额外延时时间
        double extra_delay = avFrame->repeat_pict / (2 * fps);
        //根据FPS 得到延时时间
        double real_delay = delay_time_per_frame + extra_delay;


         //等音频
         //单位微秒
         //使视频控制视频速度
        //还没同步
        //av_usleep(result_delay * 1000 * 1000);

        //拿到视频
        this->videoTime = avFrame->best_effort_timestamp * av_q2d(this->time_base) ;

        //拿到音频 播放时间基 audioChannel.audioTime
        double autoTime = this->audioChannel->audioTime;

        //计算差值
        double time_diff = videoTime - autoTime;
        if(time_diff >0){
            //视频快一些 音频慢一些
            //等待音频
//            LOGD("视频快，音频慢");
            //细节处理
            if(time_diff > 1){
                //*2是比较合适的 经过测试
                //有一点差距
                av_usleep((real_delay * 2) * 1000000 );
            }else{
                //0~1相差不大
                av_usleep((time_diff + real_delay)  * 1000000) ;
            }


        }else if(time_diff <0){
            //视频慢 音频快
            //视频加快 追音频
            //丢帧 丢冗余的帧 （冗余帧还需要解码所以丢弃掉会快）
            //packtes  frames
            //同步丢包操作
            //releaseAVFrame(&avFrame); 不能这么操作
            if(fabs(time_diff) >= 0.05){
                this->frames.syncAction();
//                LOGD("视频慢 音频块 需要丢帧");
                //继续 循环
                continue;
            }

        }else {
            // 同步
//            LOGD("音视频同步");
        }


        //渲染 显示在屏幕上
        //两种方式
        //渲染一帧图像(宽、高、数据)
        this->renderCallback(dst_data[0],avCodecContext->width,avCodecContext->height,dst_linesize[0]);
        releaseAVFrame(&avFrame);//释放

    }

    releaseAVFrame(&avFrame);//释放
    isPlay = 0;
    av_freep(&dst_data[0]);
    sws_freeContext(swsContext);
}

void VideoChannel::setAudioChannel(AudioChannel * audioChannel) {
    this->audioChannel = audioChannel;
}

void BaseChannel::setRenderCallback(RenderCallback renderCallback) {
    this->renderCallback = renderCallback;
}

