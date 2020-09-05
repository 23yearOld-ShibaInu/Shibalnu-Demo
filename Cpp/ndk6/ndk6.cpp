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
    priority_queue<int,vector<int>,less<int>> priorityQueue2;
    priorityQueue2.push(2);
    priorityQueue2.push(3);
    priorityQueue2.push(1);
    showLog(priorityQueue2.top());

    // TODO 自定义排序
    // ndk 6 第02节

    showLog("关联容器");
    //关联式容器 根据标示  决定添加或 获取 java map set

}



