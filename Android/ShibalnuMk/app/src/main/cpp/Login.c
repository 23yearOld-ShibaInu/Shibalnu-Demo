#include <jni.h>
#include <android/log.h>

//#include "../libs/libTest.a"

extern int get();

JNIEXPORT jint JNICALL Java_com_shibalnu_shibalnumk_test_getNum
        (JNIEnv * env, jobject inst){
    jint num = get();
    __android_log_print(ANDROID_LOG_DEBUG,"Trust","Test %d",num);
    return num;
}

