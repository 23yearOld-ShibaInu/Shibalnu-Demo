//
// Created by Trust on 2020/7/25.
//
#include <stdio.h>
#include "ndk_code2.h"
#include <stdint.h>
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


    //TODO  视频 ndkcode2  视频时间 01:21:46

}



void doMethod(int *number1,int *number2){
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
//    printf("doMethod number1: %d   number2:  %d\n",number1,number2);

}