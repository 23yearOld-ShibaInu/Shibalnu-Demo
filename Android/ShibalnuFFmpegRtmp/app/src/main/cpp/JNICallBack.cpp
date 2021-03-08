//
// Created by Trust on 12/27/20.
//

#include "JNICallBack.h"

JNICallBack::JNICallBack(JavaVM *javaVm, JNIEnv *env, jobject instance) {
    this->javaVm = javaVm;
    this->env = env;
    //什么情况下 不能使用  instance? 跨线程
    //有可能被其他地方 释放掉
    this->instance = env->NewGlobalRef(instance);//全局引用


    //回调上层函数
    jclass  clasz = env->GetObjectClass(this->instance);
    const char * sig = "(I)V";
    this->jmd_prepared = env->GetMethodID(clasz,"onPrepared",sig);

    const char * errorSig = "(I)V";
    this->jmd_error = env->GetMethodID(clasz,"onError",errorSig);

    const char * progressSig = "(I)V";
    this->jmd_onprogress = env->GetMethodID(clasz,"onProgress",progressSig);

}

JNICallBack::~JNICallBack() {
    this->javaVm = 0;
    env->DeleteGlobalRef(this->instance);
    this->instance = 0;
    env = 0;
}

//线程不确定
void JNICallBack::onPrePared(int thread_mode) {
    if(thread_mode == THREAD_MAIN ){
        //env 可以用
        this->env->CallVoidMethod(this->instance,this->jmd_prepared);
    }else if(thread_mode == THREAD_CHILD){
        //子线程
        //附加线程
        JNIEnv * jniEnv = nullptr;
        jint ret = this->javaVm->AttachCurrentThread(&jniEnv,0);
        if(ret != JNI_OK){
            return;
        }
        jniEnv->CallVoidMethod(this->instance,this->jmd_prepared);

        //结束附加线程
        this->javaVm->DetachCurrentThread();
    }
}

//线程不确定
void JNICallBack::onErrorAction(int thread_mode, int error_code) {
    if(thread_mode == THREAD_MAIN ){
        //env 可以用
        this->env->CallVoidMethod(this->instance,this->jmd_error,error_code);
    }else if(thread_mode == THREAD_CHILD){
        //子线程
        //附加线程
        JNIEnv * jniEnv = nullptr;
        int ret = this->javaVm->AttachCurrentThread(&jniEnv,0);
        if(ret != JNI_OK){
            return;
        }
        jniEnv->CallVoidMethod(this->instance,this->jmd_error,error_code);

        //结束附加线程
        this->javaVm->DetachCurrentThread();
    }
}

void JNICallBack::onResultProgress(int thread_mode,int nativeProgress) {
    if(thread_mode == THREAD_MAIN){
        this->env->CallVoidMethod(this->instance,this->jmd_onprogress,nativeProgress);
    }else if(thread_mode == THREAD_CHILD){
        JNIEnv * jniEnv = nullptr;
        int ret = this->javaVm->AttachCurrentThreadAsDaemon(&jniEnv, nullptr);
        if(ret != JNI_OK){
            return ;
        }
        jniEnv->CallVoidMethod(this->instance,this->jmd_onprogress,nativeProgress);
        this->javaVm->DetachCurrentThread();
    }
}
