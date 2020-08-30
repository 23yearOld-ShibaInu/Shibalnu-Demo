 //
// Created by Trust on 2020-08-30.
//

#include "TrustInstance.h"
#include "TrustLog.h"

/**
 * nullptr == NULL == 0
 * TrustInstance *  返回值
 */
TrustInstance * TrustInstance::instance = nullptr;

TrustInstance::TrustInstance() {
    LOGD("TrustInstance 创建了");
}

TrustInstance* TrustInstance::getInstance() {
    //C++11后 内部会自动保证 所有static成员变量 线程安全的问题
    if(!instance){// ==null
        instance = new TrustInstance;
    }

    return instance;
}


void TrustInstance::show() { LOGD("show1"); }
void TrustInstance::show2() { LOGD("show2"); }

void TrustInstance::unInstance() {
    if (instance){
        delete instance;
        instance = nullptr;
    }
}

TrustInstance::~TrustInstance() {
    LOGD("TrustInstance 释放了");
}