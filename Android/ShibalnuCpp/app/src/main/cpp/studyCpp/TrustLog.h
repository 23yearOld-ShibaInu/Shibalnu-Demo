//
// Created by Trust on 2020-08-28.
//

#ifndef SHIBALNUCPP_TRUSTLOG_H
#define SHIBALNUCPP_TRUSTLOG_H

#endif //SHIBALNUCPP_TRUSTLOG_H

#include <iostream>

//使用ndk里面的日志库打印
#include <android/log.h>


#define TAG "Trust"

#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)