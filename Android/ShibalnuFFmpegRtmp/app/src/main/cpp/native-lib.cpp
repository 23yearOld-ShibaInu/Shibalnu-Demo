
#include <jni.h>
#include <string>
#include "TrustPlayer.h"
#include "JNICallBack.h"
#include <android/native_window_jni.h> //专门为了渲染到屏幕支持的
extern "C"{
#include <libavutil/avutil.h>
}

JavaVM * javaVm = 0;
TrustPlayer * trustPlayer = 0;
ANativeWindow  * nativeWindow = 0;
pthread_mutex_t p_mutex = PTHREAD_MUTEX_INITIALIZER;//静态初始化 互斥锁

int JNI_OnLoad(JavaVM * javaVm , void * pvoid){
    ::javaVm = javaVm;
    return JNI_VERSION_1_6;
}

/**
 * 专门渲染函数
 * @param src_data 解码后的视频 rgba 数据
 * @param width
 * @param height
 * @param src_linesize 行数
 */
void renderFrame(uint8_t * src_data,int width,int height,int src_linesize){
    pthread_mutex_lock(&p_mutex);

    if(!nativeWindow){
        pthread_mutex_unlock(&p_mutex);
    }

    ANativeWindow_setBuffersGeometry(nativeWindow,width,height,WINDOW_FORMAT_RGBA_8888);
    ANativeWindow_Buffer windowBuffer;
    if( ANativeWindow_lock(nativeWindow,&windowBuffer,0)){
        ANativeWindow_release(nativeWindow);
        nativeWindow = 0;
        pthread_mutex_unlock(&p_mutex);
        return;
    }


    //填充数据到buffer == 修改数据
    uint8_t  * dst_data = static_cast<uint8_t *>(windowBuffer.bits);
    int lineSize = windowBuffer.stride * 4; //RGBA  像素点 * 4 （rgba）
    //逐行cv
    for (int i = 0; i < windowBuffer.height; ++i) {
        //一行一行cv 到android 屏幕上
        memcpy(dst_data + i * lineSize,src_data + i * src_linesize,lineSize);
    }
    ANativeWindow_unlockAndPost(nativeWindow);
    pthread_mutex_unlock(&p_mutex);
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
    if(trustPlayer){
        trustPlayer->stop();
    }
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
                                                       jstring data_stource_) {
    JNICallBack * jniCallBack = new JNICallBack(javaVm,env,thiz);

    //TODO 准备

    const  char *dataSource = env->GetStringUTFChars(data_stource_,NULL);
    trustPlayer = new TrustPlayer(dataSource,jniCallBack);
    trustPlayer->setRenderCallback(renderFrame);
    trustPlayer->prepare();

    env->ReleaseStringUTFChars(data_stource_,dataSource);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_setSurfaceNative(JNIEnv *env, jobject thiz,
                                                          jobject surface) {
    pthread_mutex_lock(&p_mutex);
    if(nativeWindow){
        ANativeWindow_release(nativeWindow);
        nativeWindow = 0;
    }

    //创建新的窗口用于视频显示
    nativeWindow = ANativeWindow_fromSurface(env,surface);
    pthread_mutex_unlock(&p_mutex);
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_getDuration(JNIEnv *env, jobject thiz) {
    if(trustPlayer){
        return trustPlayer->getDuration();
    }
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shibalnu_ffmpegrtmp_PlayerUtils_seekToNative(JNIEnv *env, jobject thiz,
                                                      jint play_progress) {
    if(trustPlayer){
        trustPlayer->seekTo(play_progress);
    }else{
        LOGD("trustPlayer == null");
    }
}