//
// Created by Trust on 12/27/20.
//


#include "AudioChannel.h"

void * task_audio_decode(void * pVoid){
    AudioChannel * audioChannel = static_cast<AudioChannel *>(pVoid);
    audioChannel->audio_decode();
    return 0;
}

void * task_audio_player(void * pVoid){
    AudioChannel * audioChannel = static_cast<AudioChannel *>(pVoid);
    audioChannel->audio_player();
    return 0;
}


AudioChannel::AudioChannel(int stream_index, AVCodecContext *avCodecContext) : BaseChannel(
        stream_index, avCodecContext) {

    //初始化缓冲区 out_buffers
    out_channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
    out_sample_size = av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
    out_sample_rate = 44100;
    out_buffers_size = out_sample_rate * out_sample_size * out_channels;

    out_buffers = static_cast<uint8_t *>(malloc(out_buffers_size));
    memset(out_buffers,0,out_buffers_size);

    swr_ctx = swr_alloc_set_opts(0,AV_CH_LAYOUT_STEREO,AV_SAMPLE_FMT_S16,out_sample_rate,
            avCodecContext->channel_layout,avCodecContext->sample_fmt,avCodecContext->sample_rate,0,0);

    //初始化  转换 上下文 防止 有电流声
    swr_init(swr_ctx);
}

AudioChannel::~AudioChannel() {}

void AudioChannel::start() {
    isPlay = 1;
    //存放未解码的队列开始工作
    packets.setFlag(1);

    //存放解码后的队列开始工作
    frames.setFlag(1);

    //解码线程
    pthread_create(&pid_decode,0,task_audio_decode,this);
    //播放线程
    pthread_create(&pid_play,0,task_audio_player,this);
}

void AudioChannel::stop() {

}

void AudioChannel::audio_decode() {
    AVPacket * avPacket = 0; //保存压缩 数据包  音频 AAC
    while (isPlay){
        if(isPlay && frames.queueSize() > 100){
            //休眠
            av_usleep(10 * 1000);
            continue;
        }

        int ret = packets.pop(avPacket);
        if(!isPlay){
            break;
        }

        if(!ret){
            continue;
        }

        //获取待解码的音频数据包
        ret = avcodec_send_packet(avCodecContext,avPacket);
        if(ret){
            //失败
            break;
        }

        releaseAVPacket(&avPacket);

        //获取解码后的原始数据包
        AVFrame * frame = av_frame_alloc();
        ret = avcodec_receive_frame(avCodecContext,frame);
        if(ret == AVERROR(EAGAIN)){
            //重新获取
            continue;
        }else if(ret != 0){
            releaseAVFrame(&frame);
            break;
        }
        //frame PCM
        frames.push(frame);

    }

    releaseAVPacket(&avPacket);
}

//创建声卡回调函数
void bqPlayerCallBack(SLAndroidSimpleBufferQueueItf bq,void *context){
    AudioChannel * audioChannel = static_cast<AudioChannel *>(context);
    int pcmSize = audioChannel->getPcm();
    (*bq)->Enqueue(bq,audioChannel->out_buffers,pcmSize);
}


int AudioChannel::getPcm() {
    int pcm_data_size = 0;
    //PCM 在 frames 队列里
    AVFrame * frame = 0;
    while (isPlay){
        int ret = frames.pop(frame);
        //如果停止播放 跳出循环释放
        if(!isPlay){
            break;
        }
        if(!ret){
            continue;
        }

        //PCM 的处理逻辑
        frame->data;
        //音频播放器的数据格式是在下面定义的(16位 双声道)
        //原始数据是 待播放的音频PCM数据
        //无法统一，一个是自定义16 双声道 一个是原始数据 需要重采样
        //开始重采样
        int dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx,frame->sample_rate)
                +frame->nb_samples,out_sample_rate,frame->sample_rate,AV_ROUND_UP);
        ret = swr_convert(swr_ctx, &out_buffers, dst_nb_samples, (const uint8_t **) frame->data, frame->nb_samples);
        if(ret < 0){
            //为什么无法重采样 没有返回 不影响分析整个声波
        }

        pcm_data_size = ret * out_sample_size * out_channels;
        break;

    }
    releaseAVFrame(&frame);

    return pcm_data_size;
}

void AudioChannel::audio_player() {
    //音频播放 需要 OpenLSES
    //1 创建引擎对象
    SLresult sLresult = slCreateEngine(&engineObject,0,NULL,0,NULL,NULL);
    if(SL_RESULT_SUCCESS != sLresult){
        return;
    }

    //1.2 初始化引擎
    sLresult = (*engineObject)->Realize(engineObject,SL_BOOLEAN_FALSE);
    if (SL_BOOLEAN_FALSE != sLresult) {
        return;
    }
    //1.3 获取引擎接口
    sLresult = (*engineObject)->GetInterface(engineObject,SL_IID_ENGINE,&engineInterface);
    if (SL_BOOLEAN_FALSE != sLresult) {
        return;
    }
    //2 创建混音器
    sLresult = (*engineInterface)->CreateOutputMix(engineInterface,&outputMixObject,0,0,0);

    if(SL_RESULT_SUCCESS != sLresult){
        return;
    }

    //2.2 初始化 混音器
    sLresult = (*outputMixObject)->Realize(outputMixObject,SL_BOOLEAN_FALSE);
    if(SL_BOOLEAN_FALSE != sLresult){
        return;
    }


    //不使用 混响可以不用获取混音器接口
    //获取混音器接口
//    sLresult = (*outputMixObject)->GetInterface(outputMixObject,SL_IID_ENVIRONMENTALREVERB,
//            &outputmixe)


    //3 创建播放器
    //创建 buffer缓冲队列2个
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,2};
    SLDataFormat_PCM format_pcm =  {
            //数据格式 pcm
            SL_DATAFORMAT_PCM,
            //声道  双声道
            2,
            //采样率 44100 44.1赫兹 应用最广 兼容最好
            SL_SAMPLINGRATE_44_1,
            //采样格式 16bit 16位 2个字节
            SL_PCMSAMPLEFORMAT_FIXED_16,
            //数据大小 16bit 16位 2个字节
            SL_PCMSAMPLEFORMAT_FIXED_16,
            //左右声道 双声道 立体声的效果
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            //小端模式
            SL_BYTEORDER_LITTLEENDIAN
    };

    //设置 数据源
    SLDataSource audioSrc = {&loc_bufq,&format_pcm};


    //3.2 配置音轨(输出)
    //设置混音器
    SLDataLocator_OutputMix locator_outmix = {SL_DATALOCATOR_OUTPUTMIX,outputMixObject};
    SLDataSink audioSnk = {&locator_outmix,NULL};

    //队列接口
    const SLInterfaceID  ids[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean  req[1] = {SL_BOOLEAN_TRUE};


    //3.3创建播放器
    sLresult = (*engineInterface)->CreateAudioPlayer(engineInterface,&bqPlayerObject,&audioSrc,&audioSnk,1,ids,req);
    if(SL_RESULT_SUCCESS != sLresult){
        return;
    }

    //3.4初始化播放器
    sLresult = (*bqPlayerObject)->Realize(bqPlayerObject,SL_BOOLEAN_FALSE);
    if(SL_RESULT_SUCCESS != sLresult){
        return;
    }

    //3.5获取播放器接口
    sLresult = (*bqPlayerObject)->GetInterface(bqPlayerObject,SL_IID_PLAY,&bqPlayerPlay);
    if(SL_RESULT_SUCCESS != sLresult){
        return;
    }


    //设置播放回调函数
    //4 获取播放器队列接口
    (*bqPlayerObject)->GetInterface(bqPlayerObject,SL_IID_BUFFERQUEUE,&bqPlayerBufferQueue);
    //4.2设置回调
    (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue,bqPlayerCallBack,this);


    //设置播放器状态为播放状态
    (*bqPlayerPlay)->SetPlayState(bqPlayerPlay,SL_PLAYSTATE_PLAYING);

    //手动激活回调函数
    bqPlayerCallBack(bqPlayerBufferQueue,this);


}



