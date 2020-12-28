package com.shibalnu.ffmpegrtmp

//打不开视频源
const val FFMPEG_CAN_NOT_OPEN_URL = -1

//找不到媒体信息
const val FFMPEG_CAN_NOT_FIND_STREAMS = -2

//找不到解码器
const val FFMPEG_FIND_DECODER_FAIL = -3

//无法根据解码器创建上下文
const val FFMPEG_ALLOC_CODEC_CONTEXT_FAIL = -4

//根据流量信息 配置上下文参数失败
const val FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL = -5

//打开解码器失败
const val FFMPEG_OPEN_DECOOER_FAIL = -6

//没有音频
const val FFMPEG_NO_MEDIA = -7

//读取媒体数据包失败
const val FFMPEG_READ_PACKETS_FAIL = -8
