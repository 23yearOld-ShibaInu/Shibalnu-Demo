//
// Created by Trust on 2020-08-28.
//
#include "Student.h"
#include "TrustLog.h"

using namespace std;

Student::Student() {
    //cl 上可以这样写
    //但是 as上这样写会崩溃
//    cout << "Student" << endl;
    LOGD("默认构造函数");
}

Student::Student(int age, int age2, int age3) {
    this->age = age;
    this->age2 = age2;
    this->age3 = age3;
    LOGD("有参数构造函数");
}

Student::~Student() {//当对象被释放的时候 会回调析构函数
    LOGD("析构构造函数");
}


//常量函数 :不允许修改class中的成员
void Student::setAge1(int age) const {
//    this->age = age;
}

void Student::setAge2(int age) {
    this->age2 = age;
}

void Student::updateField(Student *) {
    this->age = 11;
}
