#include <jni.h>
#include <string>
//直接这么引入有坑 必须混合编译
//#include "include/libavutil/avutil.h"
extern "C" {
    #include "include/libavutil/avutil.h"
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_shibalnu_cmakelist_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = av_version_info();
//    std::string hello = "test ";
    return env->NewStringUTF(hello.c_str());
}
