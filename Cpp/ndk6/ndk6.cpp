//
// Created by Trust on 2020/9/5.
//

#include "ndk6.h"
using namespace std;
void testMain(){

}

void showLog(char * msg){
    cout << msg << endl;
}

void showLog(string  msg){
    cout << msg << endl;
}

void showLog(int  msg){
    cout << msg << endl;
}

vector<string> allVec;


class TrustType{
public:
    int count;
public:
    TrustType(int count){
        this->count = count;
    }
};

//模拟源码的less
struct TrustTypeLess
{
    bool operator()(const TrustType& __x, const TrustType& __y) const
    {return __x.count > __y.count;}
};


void ndk6::MainTest() {
    //序列式容器
    //元素的顺序和元素本身没有任何关系。只有在添加时 添加顺序影响
    //vector priority_queue
    vector<int> vec1(1);//声明一个元素大小的容器
    vector<string> vec2(99,"肚子疼");//声明99个 "肚子疼"元素大小的容器
    vector<string> vec3;

    //添加元素
    vec3.emplace_back("头疼1");
    vec3.push_back("头疼2");
    vec3.push_back("头疼3");
    //删除元素
    //删除最后一个add元素
    vec3.pop_back();
    //获取元素
    string va = vec3.at(0);
    showLog(va);
    va = vec3[0];
    showLog(va);

    showLog("遍历 vector--------");

    vector<string>::iterator it =  vec3.begin();
    for (; it < vec3.end(); it++) {
        showLog(*it);
    }


    //清空元素
    vec3.clear();
    //vec3.erase(vec3.begin(),vec3.end()); 相等


    if(vec3.empty()){
        showLog("vec3 被清空");
    }else{
        showLog("vec3 没有被清空");
    }


    //容器问题还会占用内存空间 在栈区使用会自动释放不需要特殊操作
    showLog(vec3.capacity());

    //定义为全局的要释放
    allVec.push_back("1111");
    allVec.push_back("2222");

    allVec.clear();

    //替换方式 解决此问题
    vector<string> tem;//临时容器 解决全局容器不能释放的问题 把全局容器占用的内存空间释放掉
    tem.swap(allVec);
    showLog("全局问题: 全局容器占用空间");
    showLog(allVec.capacity());

    showLog("优先级队列");


    //优先级队列 priority_queue 是基于vector来实现的
    priority_queue<int> priorityQueue;
    priorityQueue.push(2);
    priorityQueue.push(3);
    priorityQueue.push(1);
    //默认返回最大的数
    showLog(priorityQueue.top());
    //TODO 传统用法
    //greater代表优先返回最小值
    //less 优先返回最大值
    priority_queue<int,vector<int>,greater<int>> priorityQueue2;
    priorityQueue2.push(2);
    priorityQueue2.push(3);
    priorityQueue2.push(1);
    showLog(priorityQueue2.top());



    // TODO 自定义排序
    // ndk 6 第02节
    showLog("自定义排序");
    priority_queue<TrustType,vector<TrustType>,TrustTypeLess> priorityQueue3;
    priorityQueue3.push(TrustType(1));
    priorityQueue3.push(TrustType(100));
    priorityQueue3.push(TrustType(50));
    showLog(priorityQueue3.top().count);



    showLog("关联容器------------------");
    //关联式容器 根据标示  决定添加或 获取 java map set


    set<int> set1 = {1,22,3,4,5};

    set1.insert(6);
    set1.insert(7);
    set1.insert(8);

    //重复的元素添加不进去
    set1.insert(1);
    set1.insert(22);
    set1.insert(3);
    set1.insert(4);
    set1.insert(5);


    showLog(set1.size());

    //删除元素 参数是下标识
//    set1.erase(1);

    //遍历
    set<int>::iterator beginResult = set1.begin(); //指向容器里第0个元素
    set<int>::iterator endResult = set1.end(); //指向容器里末尾元素的下一个元素
    showLog("指针遍历");
//    showLog(*(beginResult++));

    for (; beginResult != endResult; beginResult++) {
        showLog("for 遍历");
        showLog(*beginResult);
    }


    set<string> set2 = {"11","22","33"};
    set2.insert("44");
    set2.insert("55");
    set2.insert("66");

    set2.erase("11");

    //6 32:28

    //TODO
    //文件操作

    filec();
    filecpp();
    trustPthread();
}


void ndk6::filec() {

    //c语言

    //1： 路径
    //2： 模式（权限  读写）r 读  w写

    //写文件
    FILE * file1 = fopen("/Users/trust/Desktop/Work/Demo/Shibalnu-Demo/Shibalnu-Demo/Cpp/file.txt","w");
    fprintf(file1,"今天是%d号鸭?",6);
    fclose(file1);//必须关闭资源

    //读取文件
    FILE * file2 = fopen("/Users/trust/Desktop/Work/Demo/Shibalnu-Demo/Shibalnu-Demo/Cpp/file.txt","r");
    //定义接收缓冲区
    char buffer[1024]; //1023+/n
    fscanf(file2,"%s",buffer);
    fclose(file2);
    showLog("读取文件 ");
    showLog(buffer);



    //循环读取

    //缺点遇到空格就直接返回了
    showLog("循环读取");

    FILE * file3 = fopen("/Users/trust/Desktop/Work/Demo/Shibalnu-Demo/Shibalnu-Demo/Cpp/CMakeLists.txt","r");
    char buff2[1024];
    while (!feof(file3)){
        fscanf(file3,"%s",buff2);
        showLog(buff2);
    }
    fclose(file3);


    //解决循环读取 碰到空格返回  遇到换行 或 \0返回
    showLog("解决循环读取 空格返回问题");
    FILE * file4 = fopen("/Users/trust/Desktop/Work/Demo/Shibalnu-Demo/Shibalnu-Demo/Cpp/CMakeLists.txt","r");
    char buff3[1025];
    while (!feof(file4)){
        fgets(buff3,1024,file4);
        showLog(buff3);
    }
    fclose(file4);
}



void ndk6::filecpp() {
    char * filevar = "/Users/trust/Desktop/Work/Demo/Shibalnu-Demo/Shibalnu-Demo/Cpp/cppfile.txt";
    //写
    char data[200];

    //打开文件
    ofstream outFile;
    outFile.open(filevar);

    //获取用户在控制台输入的信息
    showLog("请输入保存的信息:");
    //控制台输入的信息 输入data
    cin >> data;
    //把data数据 输出给outFile
    outFile << data << endl;

    outFile.close();

    //读取操作
    char readData[200];
    showLog("读取cppfile 文件的内容");
    ifstream  ifstreamVar;
    ifstreamVar.open(filevar);

    ifstreamVar >> readData;

    showLog("cppfile 内容:");
    showLog(readData);
    ifstreamVar.close();
}

void * customPthreadMethed (void * pVoid){


    //必须返回0 不返回 会出现莫名其妙的问题
    return 0;
}


void ndk6::trustPthread() {
    //mac 不需要特殊操作
    //win 是需要下载pthread包 已经去cmakelist中配置
    //cmakelist 中
    //方法1 win 上编译可能会报错 会提示缺少一个宏 要在源码里面自己定义出来就ok
    //方法2 cmakelist中解决宏没有定义的问题



    //TODO 线程
    //定义线程ID

    /*int pthread_create(pthread_t _Nullable * _Nonnull __restrict,  线程id
                       const pthread_attr_t * _Nullable __restrict,  线程属性
                       void * _Nullable (* _Nonnull)(void * _Nullable), 函数指针  执行异步任务
                       void * _Nullable __restrict);          函数指针的参数传递*/
    pthread_t  pthreadID;
    int value01 = 9988;
    pthread_create(&pthreadID,0,customPthreadMethed,&value01);
    //ndk07  第二节
}