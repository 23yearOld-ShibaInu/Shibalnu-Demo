#include <iostream> //C++标准包
#include <string>
#include "ndk6/ndk6.h"
#include "ndk6/Log.h"
//命名空间  c++才有  类似于java中的导包
using namespace std;
//自定义命名空间
namespace TrustNameSpace{
    void TrustMethend(string msg){
        cout << "我是TrustMethend" << msg << endl;
    }
}

using namespace TrustNameSpace ;

//嵌套命名空间
//规范情况下 两级
namespace User
{
    namespace  Man
    {
        void showMan()
        {
            cout << "showMan" << endl;
        }
    }
}
using namespace User::Man;

//引用类型
void changeMethed(int& change){
    change = 666;
}


//C++中使用C
extern "C"{
    #include "main.h"
}
//如果不添加extern 编译是不通过的
//clang: error: linker command failed with exit code 1 (use -v to see invocation)

int main() {
    std::cout << "Hello, World!" << std::endl;

    //域作用符 ::  类似于java中的this
    std::cout << "今天是:" << 1 << "天气:" << "晴天" << std::endl;

    show();

    //string

    std::string str = "吴彦祖"; //在栈定义的
    std::cout << "namg:" << str <<std::endl;
    //new 一定要用指针接收  申请内存 要释放
    string *str1 = new string ;
    str1->append("我是append");
    delete str1;

    /**
     * malloc --> free(v);  v == NULL;  向堆中申请内存
     * new --> delete   申请内存 拿到的是引用
     * new [] --> delete[]
     */
    //数组申请与 释放
    char *ddd = new char [1];
    delete [] ddd;


    char buffer[20];
    char * charvalue = "trust";
    strcpy(buffer,charvalue);
    cout << "Value:" << buffer << endl;



    //自定义命名空间
    TrustNameSpace::TrustMethend("正常使用");
    TrustMethend("直接使用");


    //嵌套 命名空间

    User::Man::showMan();
    showMan();


    //大数
    long long i = 124235134513512;
    printf("我是大数:i: %lld \n",i);

    long double ld01 = 16.123456;
    printf("ld01:%Lf\n",ld01);

    //引用类型 c++独有

    int age = 99;
    int& ageYin = age;
    changeMethed(ageYin);
    cout << "引用类型:"<< age <<endl;


    ndk6 *n;
    n->test();
    return 0;
}
