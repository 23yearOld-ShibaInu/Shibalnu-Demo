

#include "mainTrust.h"

//操作符重载
class Operator{
public:
    int count;

public:
    Operator operator + (const Operator& par1){
        Operator temp;
        temp.count = this->count + par1.count;
        return temp;
    }
};


//模拟入口
int main(){
    test02();

    //单例模式
    TrustInstance * instance = TrustInstance::getInstance();
    instance->show();
    instance->show2();
    instance->unInstance();


    //操作符重载
    Operator anOperator1;
    anOperator1.count = 22;

    Operator anOperator2;
    anOperator2.count = 22;

    Operator anOperator3;
    anOperator3 = anOperator1 + anOperator2;
    LOGD("anOperator3:%d",anOperator3.count);
}

void test01() {
    Student student;
}

void test02(){
    Student *student = new Student;
    delete(student);
}


void test03(){
    Student student(24,25,26);
}

//void updateField(Student * student) {
//    student->old = 11;
//}
//友元函数调用
void updateFieldfriend(Student * student){
    student->old = 11;
}