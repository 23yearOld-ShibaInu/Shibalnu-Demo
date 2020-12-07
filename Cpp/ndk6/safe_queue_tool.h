//
// Created by Trust on 2020/9/10.
//

#ifndef CPP_SAFE_QUEUE_TOOL_H
#define CPP_SAFE_QUEUE_TOOL_H

#endif //CPP_SAFE_QUEUE_TOOL_H
#pragma once
//TODO 生产者 和消费者
#include <iostream>
#include <string>
#include <pthread.h>
#include <queue>
using namespace std;

//定义模版
template<typename  T>

class SafeQueueClass{
private:
    queue<T> queue; //定义队列

    pthread_mutex_t mutex1; //不允许有野指针

    pthread_cond_t  cond;//定义条件变量 不允许有野指针

public:
    SafeQueueClass(){
        //初始化互斥锁
        pthread_mutex_init(&mutex1,NULL);

        //初始化 条件变量
        pthread_cond_init(&cond,NULL);
    }

    ~SafeQueueClass(){
        //释放互斥锁
        pthread_mutex_destroy(&mutex1);
        pthread_cond_destroy(&cond);
    }

    //TODO 生产 加入队列
    void add(T t){
        //上锁
        pthread_mutex_lock(&mutex1);
        queue.push(t);

        //唤醒
        //让系统唤醒一个线程  java notify
        //pthread_cond_signal(&cond);
        //推荐使用下面的方式
        //以广播的形式通知所有线程   java notifyall
        pthread_cond_broadcast(&cond);


        //解锁
        pthread_mutex_unlock(&mutex1);
    }

    // TODO 消费 获取
    void get(T& t){
        //上锁
        pthread_mutex_lock(&mutex1);
        //用if可能有问题  可能会被系统唤醒 使用while
        while (queue.empty()){
            //开始等待
            //条件
            pthread_cond_wait(&cond,&mutex1);
        }

        //被唤醒
        //取出首元素  传到外面  使用引用类型的方式把值 返回出去
        t = queue.front();
        //删掉传出去的值
        queue.pop();
        //解锁
        pthread_mutex_unlock(&mutex1);
    }
};
