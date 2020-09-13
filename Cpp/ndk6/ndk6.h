//
// Created by Trust on 2020/9/5.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include "Log.h"

#include <ostream> //输出
#include <istream> //输入

#include <fstream>

#include <istream>
#include <stdlib.h>

#include <pthread.h>

#ifndef CPP_LOG_H
#define CPP_LOG_H
#endif //CPP_NDK6_H

using namespace std;



#include "safe_queue_tool.h"

class ndk6 {
public:
    void test(){MainTest();};

private:
    void MainTest();
    void filec();
    void filecpp();
    void trustPthread();
    static void trustPthreadSync();
    void trustPthreadCont();
};


