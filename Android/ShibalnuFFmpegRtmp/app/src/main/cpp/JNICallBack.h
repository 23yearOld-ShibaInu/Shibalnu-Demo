//
// Created by Trust on 12/27/20.
//

#ifndef SHIBALNUFFMPEGRTMP_JNICALLBACK_H
#define SHIBALNUFFMPEGRTMP_JNICALLBACK_H

#include <jni.h>
#include "macro.h"
class JNICallBack {
public:
    //线程中 不能使用 env  env无法跨线程
    JNICallBack(JavaVM * javaVm, JNIEnv * env, jobject instance);
    virtual ~JNICallBack();

    //回调
    //thread_mode 可以区分 主线程或子线程
    void onPrePared(int thread_mode);
    //失败回调
    void onErrorAction(int thread_mode,int error_code);

    void onResultProgress(int thread_mode,int nativeProgress);
private:
    JavaVM * javaVm = 0;
    JNIEnv * env = 0;
    jobject  instance;

    const char  * class_path = 0;
    jmethodID jmd_prepared;
    jmethodID jmd_error;
    jmethodID jmd_onprogress;
};


#endif //SHIBALNUFFMPEGRTMP_JNICALLBACK_H
