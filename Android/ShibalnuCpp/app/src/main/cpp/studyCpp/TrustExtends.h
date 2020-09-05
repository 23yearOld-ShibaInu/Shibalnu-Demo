//
// Created by Trust on 2020-09-05.
//

#ifndef SHIBALNUCPP_TRUSTEXTENDS_H
#define SHIBALNUCPP_TRUSTEXTENDS_H

#include "TrustLog.h"

class TrustExtendsLh {
private:
    int age;
    char sex;
public:
    char *name;
    void show(){ LOGD("我是 TrustExtends show()"); }
    void show1(){ LOGD("我是 TrustExtends show1()"); }
    void show2(){ LOGD("我是 TrustExtends show2()"); }
    //虚函数
    virtual void show3(){ LOGD("我是 TrustExtends show3()"); }
    //纯虚函数 类似java中的抽象方法 0 == NULL
    virtual void show4() = 0;
};


//子类    :public 共有继承 能访问父类中public变量和函数
class Workder : public TrustExtendsLh{
public:
    void show(){ LOGD("我是 Workder show()"); }
    void show1(){ LOGD("我是 Workder show1()"); }
    void show2(){ LOGD("我是 Workder show2()"); }
    void show3(){ LOGD("我是 Workder show3()"); }
    void show4(){ LOGD("我是 Workder show4()"); }

};


#endif //SHIBALNUCPP_TRUSTEXTENDS_H
