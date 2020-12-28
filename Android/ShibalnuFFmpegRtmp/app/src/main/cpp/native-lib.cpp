
#include <jni.h>
#include <string>
#include "TrustPlayer.h"
#include "JNICallBack.h"
extern "C"{
#include <libavutil/avutil.h>
}

JavaVM * javaVm = 0;
TrustPlayer * trustPlayer = 0;


int JNI_OnLoad(JavaVM * javaVm , void * pvoid){
    ::javaVm = javaVm;
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_shibalnu_ffmpegrtmp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hello.append(av_version_info());
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_startNative(JNIEnv *env, jobject thiz) {

    //播放音视频

    if(trustPlayer){
        trustPlayer->start();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_stopNative(JNIEnv *env, jobject thiz) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_releaseNative(JNIEnv *env, jobject thiz) {

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_getFFmpegVersion(JNIEnv *env, jobject thiz) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_prepareNative(JNIEnv *env, jobject thiz,
                                                       jstring data_stource) {
    JNICallBack * jniCallBack = new JNICallBack(javaVm,env,thiz);

    //TODO 准备

    const  char *dataSource = env->GetStringUTFChars(data_stource,NULL);
    trustPlayer = new TrustPlayer(dataSource,jniCallBack);
    trustPlayer->prepare();

    env->ReleaseStringUTFChars(data_stource,dataSource);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_setSurfaceNative(JNIEnv *env, jobject thiz,
                                                          jobject surface) {

}