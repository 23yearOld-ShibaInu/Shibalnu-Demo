

#include "mainTrust.h"

//第1中写法操作符重载
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


//第2种写法 操作符重载
class Operator2{
public:
    int count;
};

Operator2 operator + (Operator2 o1,Operator2 o2){
    Operator2 o;
    o.count = o1.count + o2.count;
    return o;
}

//特殊 操作符重载
void * operator new (size_t size){
    LOGD("操作符重载 new 被执行了 大小是： %d ",size);
    return malloc(size);
}

void  operator delete (void *p){
    LOGD("操作符重载 delete 内存地址是:%#x",p);
}


//todo  模版编程

template <class T>
//普通模版  函数上
T getMax(T num1,T num2){
    return num1 > num2 ? num1 : num2;
}

//类模版 12:51
template <class Class1 , class Class2 , class Class3>
class Test{
public:
    Class1 getType(Class1 class1){ return class1; }
    Class2 getType(Class2 class1){ return class1; }
    Class3 getType(Class3 class1){ return class1; }
};

//类型转换
class Parent{
public:
    void show(){ LOGD("Parent show");}
    virtual void show1(){ LOGD("Parent show1");}
};

class Soon : public Parent{
public:
    void show(){ LOGD("Soon show"); }
    void show1(){ LOGD("Soon show1"); }
};

//异常
void error(){
    //"i'm error!"  == const char *
    throw  "i'm error!";
}

void  error1(){
    //xcode vs clion 中可以传递参数

    //throw std::exception("this is error");

    //as中不能传递参数 编译不通过
    throw std::exception();

}



//自定义异常
//class TrustException :public std::exception{
//public:
//    char const * what() const {
//        return "我是自定义异常";
//    }
//};

//void error2(){
//    throw new TrustException;
//}

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

    Operator2 anOperator21;
    anOperator21.count = 22;

    Operator2 anOperator22;
    anOperator22.count = 22;

    Operator2 anOperator23;
    anOperator23 = anOperator21 + anOperator22;

    LOGD("anOperator23: %d ",anOperator23.count);



    //Todo 继承  可以多继承
    Workder *trustExtends;
    trustExtends->show();
    trustExtends->name = "";
    delete(trustExtends);

    //静态多态 ，编译期  看左边声明是谁 就调用谁的函数
    TrustExtendsLh *t = new Workder;
    t->show();

    //动态多态  父类的该函数是否是 虚函数
    t->show3();

    //纯虚函数
    t->show4();
    delete(t);

    //todo c++模版编程 == Java 中泛型
    LOGD("%d",getMax(1,2));
    LOGD("%s",getMax("lhsss","lhddd"));
    //类模版
    Test<int ,double ,std::string> test;
    test.getType(1);
    test.getType(1.0);
    test.getType("");


    //todo 类型转换 新式转换
    //普通类型转换  普通类型转换
    const char * c1 = "11111";
    char * c2 = const_cast<char  *>(c1);

    //const_cast<>  <>里面必须是最后得到的数据类型
    char * c3 = "22222";
    const char * c4 = const_cast<const char  *>(c3);

    //静态类型转换 指针类型转换  谁new 回收谁
    Parent *paren = new Parent;
    Soon *soon  = static_cast<Soon *>(paren);
    soon->show();
    delete(paren);


    //动态类型转换
//    Parent *parent1 = new Parent; 失败
    Parent *parent1 = new Soon;
    parent1->show1();
    Soon *soon1 = dynamic_cast<Soon *>(parent1);
    if(soon1){
        LOGD("转换成功");
        soon1->show1();
    }else{
        LOGD("转换失败");
    }

    delete(parent1);

    //ndk 5  40:50

    //todo 异常  c 字符串方式 char *a  = "";
    try {
        error();
    }catch(const char * msg) {
        LOGD("捕获异常 %s",msg);
    }

    try {
        error1();
    }catch (std::exception &msg){
        LOGD("error : %s",msg.what());
    }
    //as 不能运行
    /*try {
        error2();
    }catch (std::exception &msg){
        LOGD("error : %s",msg.what());
    }*/

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