//
// Created by Trust on 2020/7/25.
//
#include <stdio.h>
#include "ndk_code2.h"
#include <stdint.h>

#include <stdarg.h> //可变参数

#include <stdbool.h> //boolean
void ndk2Init(){
    printf("------------ndkcode2------------\n");

    int32_t  count32 = 10;//4字节
    int64_t  count64 = 20;//8字节
    int8_t   count8 = 30;//1字节
    int16_t  count16 = 40;//2字节

    //指针
    //概念 指针变量和指针的区别
    //指针变量就是定义指针的标记
    //指针就是指向的内存地址

    //TODO int *p = 内存地址;  p == 指针变量   指针 == 内存地址


    int *p;

    //指针的使用
    int value = 1000;

    //1级指针
    int *z = &value;//获取value的内存地址.&取地址符号

    //*指针  == 输出指针内存地址的值

    //输出指针 对应的内存地址
    printf("指针z值 : %#x\n", z);

    //输出指针 对应的值
    printf("指针z值 : %d\n", *z);


    //多级指针
    int trust1 = 999;
    int *z01 = &trust1;
    int **z02 = &z01;//取出1级指针的地址
    int ***z03 = &z02;//取出2级指针地址
    int ****z04 = &z03;//取出3级指针地址

    //取出trust1 的值

    printf("取值：%d\n",****z04);

    //使用场景
    int number1 = 10000;
    int number2 = 20000;
    doMethod(&number1,&number2);


//    int temp = number1;
//    number1 = number2;
//    number2 = temp;
//
    printf("main number1: %#x   number2:  %#x\n",&number1,&number2);
    printf("number1: %d   number2:  %d\n",number1,number2);

    //函数 压栈 有自己所属的内存分配


    //TODO  函数  顺序结构
    add(NULL,1,2,3,4,5,6,'w');

    //TODO 函数指针  指向函数的指针
    void(*test)(char*) = myPrintln;
    say(test,"我是函数指针");

    //TODO 指针函数 使用场景
    loginEngine(loginSuccess,loginError);


    //TODO 预处理器  执行时间在编译之前
#if 0
    printf("写法1\n");
#else if 9
    printf("写法2\n");
#endif
    printf("肯定会执行\n");

    //第二种写法 配合宏

    //定义宏  类似于java中的常量

#define NAME "Trust"

char *name = NAME;

#define DEBUG_MODE

//第二种写法
//ifdef 如果就
//ifndef 如果不是就
//上面两个同时只能使用1个

//#ifndef DEBUG_MODE
#ifdef DEBUG_MODE //如果定义 DEBUG_MODE 这个宏
    printf("配合宏 debug");
#else if
    printf("配合宏 relase");
#endif










}



void doMethod(int *number1,int *number2){
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
//    printf("doMethod number1: %d   number2:  %d\n",number1,number2);

}

//可变参数
void add(char * flag, ...){

    va_list changeList;
    va_start(changeList,flag); //必须穿参数

    //for 循环
    for (int i = 0; i < 6; ++i) {
        int item  = va_arg(changeList,int );
        printf("可变参数: %d\n",item);
    }


    char  msg = va_arg(changeList,char );
    printf("可变函数char : %c\n",msg);  

    va_end(changeList);
}

//函数指针
//say 函数 接收 *tt名字的函数 参数是 char *msg 返回值是void
//类似java 接口回调
void say(void(*tt)(char*),char *msg){
        tt(msg);
}


void * myPrintln(char *msg){
    printf("myPrintln:%s\n",msg);
}





void loginEngine(void(*resultSuccess)(int64_t code,char *msg),void(resultError)(int64_t code,char *msg)){
    bool isSuccess = 0;
    if(isSuccess){
        resultSuccess(isSuccess,"登录成功");
    }else{
        resultError(isSuccess,"登录失败");
    }
}

void * loginSuccess(int64_t code,char *msg){
    printf("loginSuccess :%d , %s\n",code,msg);
}
void * loginError(int64_t code,char *msg){
    printf("loginError :%d , %s\n",code,msg);
}