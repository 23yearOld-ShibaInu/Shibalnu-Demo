#include <jni.h>
#include <string>
#include <android/log.h>

//extern int get(); 当前是cpp 不是c 所以会报错 需要混合编译

extern "C" {
    int get();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_shibalnu_androidcmakelist_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    __android_log_print(ANDROID_LOG_DEBUG,"Trust","get : %d",get());
    return env->NewStringUTF(hello.c_str());
}
