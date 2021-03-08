//
// Created by Trust on 12/25/20.
//


#include <pthread.h>
#include "TrustPlayer.h"

//函数指着
//void* (*__start_routine)(void*)
void * customTashPrepareThread(void * pVoid){
    TrustPlayer *trustPlayer = static_cast<TrustPlayer *>(pVoid);
    trustPlayer->prepare_();
    return 0;//必须返回
}

void * customTashStartThread(void * pVoid){
    TrustPlayer * trustPlayer = static_cast<TrustPlayer *>(pVoid);
    trustPlayer->start_();
    return 0;
}


TrustPlayer::~TrustPlayer(){
    if(this->data_source){
        delete this->data_source;
        this->data_source = 0;
    }
}

TrustPlayer::TrustPlayer(const char * data_source,JNICallBack * jniCallBack){
    //直接会崩溃 悬空指针
//    this->data_source = data_source;

    //有错 长度不对  c++跟C环境不一样  c:aaa c++: aaa+\n
    //this->data_source = new char [strlen(data_source)];

    this->data_source = new char [strlen(data_source)+1];
    strcpy(this->data_source,data_source);

    this->jniCallBack = jniCallBack;
}

//准备工作 "解码"  拆包裹（音频流、视频流、字节流....）
//av_register_all（）已经淘汰了 ffmpeg 2.几的版本会使用
//开线程
void TrustPlayer::prepare(){
    //创建异步线程
    pthread_create(&this->pid_prepare,0,customTashPrepareThread,this);
}

void TrustPlayer::prepare_() {
    //拆包裹 解码
    this->avFormatContext = avformat_alloc_context();

    //筛选是否符合预定包裹 (损坏的数据格式)
    //第4个参数
    AVDictionary * dictionary = 0;
    av_dict_set(&dictionary,"timeout","5000000",0);//单位是微秒,模拟器卡的话就设置大一点 超时时间

    //回收字典
    av_dict_free(&dictionary);

    int status = avformat_open_input(&this->avFormatContext,this->data_source,0,&dictionary);
    if(status){
        if(this->jniCallBack){
            //JNI回调 通知上层通知用户 播放流已经损坏
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_CAN_NOT_OPEN_URL);
        }
        return;
    }

    //寻找 媒体格式中的 音、视频、字幕（字母多半跟视频在一起 基本不需要）
    //不给字典 是因为不需要设置额外配置
    status = avformat_find_stream_info(this->avFormatContext,0);
    if(status < 0){
        if(this->jniCallBack){
            //JNI回调 通知上层通知用户 失败
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_CAN_NOT_FIND_STREAMS);
        }
        return;
    }

    //媒体上下文，有了需要的值了
    this->duration = avFormatContext->duration / AV_TIME_BASE;//最终需要拿到秒

    //遍历媒体格式里面的流n  流0视频 流1音频 流2字幕

    for (int i = 0; i < this->avFormatContext->nb_streams; ++i) {
        //获取媒体流
        AVStream * stream = this->avFormatContext->streams[i];
        //获取解码器id
        AVCodecParameters * avCodecParameters = stream->codecpar;
        enum AVCodecID  codecId = avCodecParameters->codec_id;

        //解码器
        AVCodec * avCodec = avcodec_find_decoder(codecId);
        if(!avCodec){
            //获取解码器失败
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_FIND_DECODER_FAIL);
            return;
        }

        //为了后续方便解码 需要解码器上下文
        AVCodecContext * avCodecContext = avcodec_alloc_context3(avCodec);
        if(!avCodecContext){
            //获取解码器上下文 失败
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            return;
        }

        //给解码器上下文设置参数
        status = avcodec_parameters_to_context(avCodecContext,avCodecParameters);
        if(status < 0){
            //给解码器上下文设置参数失败
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }

        //打开解码器
        status = avcodec_open2(avCodecContext,avCodec,0);
        if(status){
            //打开解码器 失败
            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_OPEN_DECOOER_FAIL);
            return;
        }

        //获取时间基 完成音视频同步
        AVRational time_base = stream->time_base;

        //解码器打开成功
        //区分媒体流格式 音频、视频
        //音频流
        if(avCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO){
            this->audioChannel = new AudioChannel(i, avCodecContext, time_base,jniCallBack);
        }
        //视频流 目前很多字幕流都放在视频轨道中
        else if(avCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
            //获取视频的 FPS
            //平均帧率 == 时间基
            AVRational frame_rate = stream->avg_frame_rate;
            int fpsValue = av_q2d(frame_rate);

            this->videoChannel = new VideoChannel(i, avCodecContext, time_base, fpsValue,jniCallBack);
            this->videoChannel->setRenderCallback(renderCallback);
        }
    }
    if(!audioChannel && !videoChannel){
        this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_NO_MEDIA);
        return;
    }

    //通知上层 ready
    if(jniCallBack){
        this->jniCallBack->onPrePared(THREAD_CHILD);
    }


}

void TrustPlayer::start() {
    isPlayer = 1;
    if(this->videoChannel){
        this->videoChannel->setAudioChannel(this->audioChannel);
        this->videoChannel->start();
    }
    if(this->audioChannel){
        this->audioChannel->start();
    }
    //开始线程 放入队列
    pthread_create(&this->pid_start,0,customTashStartThread,this);
}

//异步函数
void TrustPlayer:: start_() {
    //循环读取 视频包
    while (this->isPlayer){

        //生产的 太多了  处理不过来 容易泄漏  目的 队列不被爆掉
        // 内存泄漏点1，解决方案：控制队列大小
        if (videoChannel && videoChannel->packets.queueSize() > 100) {
            // 休眠 等待队列中的数据被消费
            av_usleep(10 * 1000);
            continue;
        }
        // 内存泄漏点1，解决方案：控制队列大小
        if (audioChannel && audioChannel->packets.queueSize() > 100) {
            // 休眠 等待队列中的数据被消费
            av_usleep(10 * 1000);
            continue;
        }


        //未解码格式保存在avPacket
        AVPacket * avPacket = av_packet_alloc();
        int ret = av_read_frame(this->avFormatContext,avPacket);
//        if(ret != 0){
//            //
//            this->jniCallBack->onErrorAction(THREAD_CHILD,FFMPEG_READ_PACKETS_FAIL);
//            return;
//        }
        if(!ret){
            //AVPacket 放入队列中
            //判断 音视频
            //是视频包
            if(videoChannel && videoChannel->stram_index == avPacket->stream_index){
                this->videoChannel->packets.push(avPacket);
            }
            else if(audioChannel && audioChannel->stram_index == avPacket->stream_index){
                this->audioChannel->packets.push(avPacket);
            }
        }else if(ret == AVERROR_EOF){//文件末尾 读完了

        }else{
            //失败
            break;
        }
    }
    //释放
    this->isPlayer = 0;
    this->videoChannel->stop();
    this->audioChannel->stop();
}

void TrustPlayer::setRenderCallback(RenderCallback renderCallback) {
    this->renderCallback = renderCallback;
}

int TrustPlayer::getDuration() {
    return this->duration;
}
