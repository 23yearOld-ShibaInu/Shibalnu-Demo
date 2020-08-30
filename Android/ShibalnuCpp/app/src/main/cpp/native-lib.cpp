#include <jni.h>
#include <string>
#include "studyCpp/TrustLog.h"
#include "studyCpp/mainTrust.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_trust_shibalnucpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ test this is 大sad撒打算的";
    main();
    return env->NewStringUTF(hello.c_str());
}
