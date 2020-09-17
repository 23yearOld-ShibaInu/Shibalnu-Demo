#include <jni.h>
#include <string>
//#include "studyCpp/TrustLog.h"
#include "studyCpp/mainTrust.h"

//TODO
//日志打印
#include <android/log.h>
#define TAG "LiHao"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_trust_shibalnucpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++ test this is 大sad撒打算的";
    main();
    return env->NewStringUTF(hello.c_str());
}

//支持c语言的代码
extern "C"
//Linux 和Win 不一样  jni.h 内部定义全部不一样  这个宏代表对外暴露的标准形式定义
//例如 windows中 对外暴露的标准 规定了  所有函数以window系统规则定义的
//JNIEXPORT linux上不写这个也可以 因为不严格 但win上严格会报错
JNIEXPORT
//返回值
void
//宏  linux上 占位 win上 这个宏会特殊处理
//代表当前对应的函数 压栈的规则(行参规则)
//例如 windows 上  代表函数压栈 从右 到左
// linux 可以不用写 但win上必须要有
JNICALL
Java_com_trust_shibalnucpp_JniTest_Test1(JNIEnv *env, jobject thiz) {
    // TODO: implement Test1()

    //jni1  7:35
    LOGD("我是log");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_addTest01(
        JNIEnv *env, //JAVA 虚拟机自动携带过来的 就是为了让我们可以使用jni的api
        jobject thiz, //java中的 调用该函数的实例
        jint number,
        jstring text,
        jintArray int_array,
        jobjectArray string_array) {

    //C                 JNI          JAVA
    //int               jint         int    JAVA 可以直接自动转成c

    //const char *      jstring      String


    //


    int c_number = number;
    LOGD("c_number %d \n",c_number);

    //参数二 是否在内部完成copy操作
    //NULL == 不在内部完成
    //随意值 就可以运行
    const char * c_str = env->GetStringUTFChars(text,NULL);
    LOGD("c_str %s \n",c_str);
    //回收
    env->ReleaseStringUTFChars(text,c_str);

    //数组
    jint * c_int_array = env->GetIntArrayElements(int_array,NULL);

    jsize int_size = env->GetArrayLength(int_array);
    for (int i = 0; i <int_size ; ++i) {
        int result = *(c_int_array+i);

        //使用这个操作来修改数组的值  java层的数组也会修改
        *(c_int_array+i)+=1000;
        LOGD("c_int_array %d \n",result);
    }
    //回收
    //jni model  0代表要刷新更改的值 也就是修改java层的值  基本类型可以这么做
    env->ReleaseIntArrayElements(int_array,c_int_array,0);

    //TODO 41:16

    //打印string数组
    jsize  str_size = env->GetArrayLength(string_array);

    for (int i = 0; i < str_size ; ++i) {
        jobject obj = env->GetObjectArrayElement(string_array,i);
        jstring  jstr = static_cast<jstring >(obj);
        const  char * str = env->GetStringUTFChars(jstr,NULL);
        LOGD("str_array: %s \n",str);
        //回收
        env->ReleaseStringUTFChars(jstr,str);
    }


    //c 操作java
}

//TODO
//c 操作java
extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_putStudent(
        JNIEnv *env,
        jobject thiz,
        jobject student) {

    //C                 JNI                 JAVA
    //                  jclass              class
    //                  jmethodID           Method

    //反射
    //1:获取字节码
    const char  * student_class_str = "com/trust/shibalnucpp/Student" ;
    jclass student_class = env->FindClass(student_class_str);
    //2:获取函数  第三个参数方法签名
    //在app/build/intermediates/javac/debug/classes  命令目录下 执行javap -s (路径+类名)
    const char * sig = "(Ljava/lang/String;)V";
    jmethodID setName = env->GetMethodID(student_class,"setName",sig);
    //3:调用对象
    const char  * str = "cpp";
    jstring jstr = env->NewStringUTF(str);
    env->CallVoidMethod(student,setName,jstr);

    //调用有参无返回值
    sig = "(I)V";
    jmethodID setAge = env->GetMethodID(student_class,"setAge",sig);

    env->CallVoidMethod(student,setAge,100);

    //调用静态无返回值
    sig = "()V";
    jmethodID statcMethodID = env->GetStaticMethodID(student_class,"startMethod",sig);
    env->CallStaticVoidMethod(student_class,statcMethodID);

    //回收
    env->DeleteLocalRef(student);
    env->DeleteLocalRef(student_class);
}

//TODO NDK第9节
//深入对象
extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_ndk9(JNIEnv *env, jobject thiz) {
    const char * person_class_str = "com/trust/shibalnucpp/Person";
    jclass person_class = env->FindClass(person_class_str);
    //c 实例化java class  反射
    jobject person = env->AllocObject(person_class);
    //调用person 函数
    const char * sig = "(Lcom/trust/shibalnucpp/Student;)V";
    jmethodID setStudentId = env->GetMethodID(person_class,"setStudent",sig);

    //实例化 student
    const char * student_class_str = "com/trust/shibalnucpp/Student";
    jclass student_class = env->FindClass(student_class_str);
    jobject student = env->AllocObject(student_class);


    sig = "(Ljava/lang/String;)V";
    jmethodID setNameId = env->GetMethodID(student_class,"setName",sig);
    jstring setNamestr = env->NewStringUTF("Trust");
    env->CallVoidMethod(student,setNameId,setNamestr);

    sig =  "(I)V";
    jmethodID setAgeId = env->GetMethodID(student_class,"setAge",sig);
    env->CallVoidMethod(student,setAgeId,25);

    env->CallVoidMethod(person,setStudentId,student);

    //TODO ndk9 01  24：51
}