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


    //给student 对象赋值
    sig = "(Ljava/lang/String;)V";
    jmethodID setNameId = env->GetMethodID(student_class,"setName",sig);
    jstring setNamestr = env->NewStringUTF("Trust");
    env->CallVoidMethod(student,setNameId,setNamestr);

    sig =  "(I)V";
    jmethodID setAgeId = env->GetMethodID(student_class,"setAge",sig);
    env->CallVoidMethod(student,setAgeId,25);

    env->CallVoidMethod(person,setStudentId,student);

    //TODO ndk9 01  24：51


    //回收方式 转门回收class 和jobject  内部会回收 可以不用写但是建议写上
    env->DeleteLocalRef(person_class);
    env->DeleteLocalRef(person);

    env->DeleteLocalRef(student_class);
    env->DeleteLocalRef(student);
}



//TODO 引用类型 +Java构造方法实例化

//c++中 还是属于局部引用
jclass dogClass;

extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_testDog(JNIEnv *env, jobject thiz) {
    //局部引用 自动回收 函数执行完就释放 建议代码写回收



    //制造bug
    if(dogClass == NULL){
        //局部引用  与java 不同
//TODO 1
//        const char * dog_class_str = "com/trust/shibalnucpp/Dog";
//        dogClass = env->FindClass(dog_class_str);
//TODO 2
        //解决局部引用的问题 全局引用（通过代码提升）
        const char * dog_class_str = "com/trust/shibalnucpp/Dog";
        jclass temp = env->FindClass(dog_class_str);
        //提升全局引用
        dogClass = static_cast<jclass>(env->NewGlobalRef(temp));
    }

    //出现一个问题  第一次ok  第二次崩溃
    //第一次调用成功后  隐式释放 dogClass
    //第二次调用的时候 dogClass 判断不为null
    //调用NewObject的时候 dogClass 已经释放了 导致崩溃
    //隐式释放 dogClass 不为NULL  处于悬空状态
    //释放的式dogClass 的内存  但是dogClass本身没有释放
    //这是局部引用的困扰


    //Java 构造方法实例化
    //与普通函数不一样
    const char * method = "<init>";
    const char * sig = "()V";
    jmethodID dog1ID = env->GetMethodID(dogClass,method,sig);
    env->NewObject(dogClass,dog1ID);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_testUnBindDog(JNIEnv *env, jobject thiz) {
    //TODO 手动释放全局引用
    //与全局引用对应
    if(dogClass != NULL){
        LOGD("释放dogClass 的引用");
        env->DeleteGlobalRef(dogClass);
        //不使用 dogClass = null  会跟隐式释放一样的后果
        dogClass = NULL;
    }
    //TODO ndk9 2 动态注册
}

//TODO 静态注册
//extern "C"
//JNIEXPORT void JNICALL
//包名Java_com_x_x_x_函数名


//TODO 动态注册
//源码里面都是动态注册

//代码
//typedef struct {
//    const char* name;
//    const char* signature;
//    void*       fnPtr;
//} JNINativeMethod;

void register01(JNIEnv *env, jobject thiz,jstring text){
    const char * textValue = env->GetStringUTFChars(text,NULL);
    LOGD("register01 动态注册 success %s",textValue);
    //回收
    env->ReleaseStringUTFChars(text,textValue);
}

int register02(JNIEnv *env, jobject thiz,jstring text){
    const char * textValue = env->GetStringUTFChars(text,NULL);
    LOGD("register02 动态注册 success %s",textValue);
    //回收
    env->ReleaseStringUTFChars(text,textValue);
    return 25;
}

//一次性注册很多
//批量注册
//灵活性高 安全
//缺点 麻烦
static const JNINativeMethod jniNativeMethod[]={
        {"registerJava01","(Ljava/lang/String;)V",(void *)(register01)},
        {"registerJava02","(Ljava/lang/String;)I",(int *)(register02)}
};


JavaVM * jvm;
//自动调用  当System.loadLibrary"xxx.lib"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm ,void *pVoid){
    ::jvm = javaVm;

    //获取 JNIEnv
    //通过虚拟机创建 JNIEnv

    JNIEnv * jniEnv = nullptr;
    //参数2 是jni的版本  NDK 1.6是最高的  java jni有1.8
    jint  result = jvm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);
    if(result != JNI_OK){
        return -1;//主动报错
    }


    const  char * mainActivityClassStr = "com/trust/shibalnucpp/MainActivity";
    jclass mainActivityClass = jniEnv->FindClass(mainActivityClassStr);
    jniEnv->RegisterNatives(mainActivityClass,jniNativeMethod, sizeof(jniNativeMethod) / sizeof(JNINativeMethod));

    return JNI_VERSION_1_6;
}

//TODO jni 线程
//
void * coustomThread(void *pVoid){
//    for (int i = 0; i <30; ++i) {
//        LOGD("线程 :%d ",i);
//    }
    //必须使用env  无法跨线程
    //动态注册获取全局的 jv java虚拟机 只有虚拟机javaVm才能跨越线程

    JNIEnv * pEnv = nullptr;//新的env
    //把native的线程 附加到JVM里
    //可以理解为初始化env
    int result = jvm->AttachCurrentThread(&pEnv,0);
    if(result !=0){
        //失败
        return 0;
    }

    //自己的实例化的对象是不行的

    //需要外部传进来
    jobject thiz = static_cast<jobject >(pVoid);

//    const char * thiz_class_str = "com/trust/shibalnucpp/JniTest";
//    jclass this_class = pEnv->FindClass(thiz_class_str);
    jclass this_class = pEnv->GetObjectClass(thiz);

    const char * sig = "()V";
    jmethodID updateUI = pEnv->GetMethodID(this_class,"updateUI",sig);

    pEnv->CallVoidMethod(thiz,updateUI);

    //解除附加到jvm上的native线程
    jvm->DetachCurrentThread();

    return 0;
}

jobject mInstance;

extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_testThread(JNIEnv *env, jobject thiz) {

    mInstance = env->NewGlobalRef(thiz);
    pthread_t pthreadID;
    //这样传的话应该是悬空指针
    //pthread_create(&pthreadID,0,coustomThread,thiz);
    pthread_create(&pthreadID,0,coustomThread,mInstance);
    pthread_join(pthreadID,0);
}

//释放全局
extern "C"
JNIEXPORT void JNICALL
Java_com_trust_shibalnucpp_JniTest_unThread(JNIEnv *env, jobject thiz) {
    if(NULL != mInstance){
        env->DeleteGlobalRef(mInstance);
        mInstance = NULL;
    }
}

