//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_MACRO_H
#define SHIBALNUFFMPEGRTMP_MACRO_H

#define THREAD_MAIN  1
#define THREAD_CHILD  2


//定义释放宏函数
#define  DELETE(object) if(object){delete object;object = 0;};

//打不开视频源
#define FFMPEG_CAN_NOT_OPEN_URL  -1

//找不到媒体信息
#define FFMPEG_CAN_NOT_FIND_STREAMS  -2

//找不到解码器
#define FFMPEG_FIND_DECODER_FAIL  -3

//无法根据解码器创建上下文
#define FFMPEG_ALLOC_CODEC_CONTEXT_FAIL  -4

//根据流量信息 配置上下文参数失败
#define  FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL  -5

//打开解码器失败
#define FFMPEG_OPEN_DECOOER_FAIL  -6

//没有音频
#define FFMPEG_NO_MEDIA  -7

//读取媒体数据包失败
#define FFMPEG_READ_PACKETS_FAIL  -8


#endif //SHIBALNUFFMPEGRTMP_MACRO_H
