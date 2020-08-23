#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ndk_code_2/ndk_code2.h"

#include "ndk_code_3/ndk_code3.h"
//引入头文件  #include <xx.h>

void NdkCode1();
void NdkCode2();

int main() {
//    printf("Hello, World!\n");
    NdkCode1();
    NdkCode2();
    ndk3Init();
    return 0;
}

void NdkCode1(){
    //有符号和无符号的区别在于取值范围的不同
    //有符号 可以默认不写前面的 signed
    printf("有符号声明及打印--------");
    signed int count = 99;
    printf("int count: %d 字节: %d\n",count,sizeof(count));
    signed short age2 = 25;
    printf("short age2:%d 字节: %hd\n",age2,sizeof(age2));
    long testLong = 1000;
    printf("long testLong:%ld 字节：%d\n",testLong,sizeof(testLong));
    char sex = 'w';
    printf("char sex:%c 字节：%d\n",sex,sizeof(sex));


    printf("无符号声明及打印--------");
    unsigned int uncount = 99;
    printf("int count: %u 字节：%d\n",uncount,sizeof(uncount));
    unsigned short unage2 = 25;
    printf("short age2:%hu 字节：%d\n",unage2,sizeof(unage2));
    unsigned long untestLong = 1000;
    printf("long testLong:%lu 字节：%d\n",untestLong,sizeof(untestLong));
    unsigned char unsex = 'w';
    printf("char sex:%c 字节: %d\n",unsex,sizeof(unsex));

    // long long 变量   为8个字节 == java中的long 8个字节
    long long tLongLong = 10000;
    printf("long long tLongLong : %ld  字节： %d\n",tLongLong,sizeof(tLongLong));

    double testDouble = 1.666666;
    printf(" testsssLong : %.2lf  字节： %d\n",testDouble,sizeof(testDouble));



    //字符串
    char *str  = "今天天气好晴朗";
    printf("*str %s \n",str);

    //数组  容器
    //数组是一块连续的内存空间
    char strChar[200];
    sprintf(strChar,"处处好风光 %d \n",999);
    printf("%s \n",strChar);

    printf("----------遍历数组--start------------\n");

    int intArray[] = {1,3,2,5,4};
    //遍历
    //sizeof(test) 获取数组的字节 然后除以 单个类型占用的字节
    for (int i = 0; i < (sizeof(intArray)/ sizeof(int)); ++i) {
        printf("%d \n",intArray[i]);
    }
    printf("----------遍历数组--end------------\n");
    //1个int 占用4个字节

    //打印内存地址
    printf("数组长度:%d\n",sizeof(intArray));
    printf("数组+0:%#x\n",intArray + 0);
    printf("数组+1:%\n",intArray + 1);

    //* 取出内存地址里面对应的值
    // 理解数组是一个连续的内存空间的例子
    printf("*数组+0:%d\n",* (intArray + 0));
    printf("*数组+1:%d\n",* (intArray + 1));
    printf("*数组+2:%d\n",* (intArray + 2));

    //%x   加一个# 代表16进制显示
    //数组+0:0XE3FB79F0
    //数组+1:0XE3FB79F4
    //数组+2:0XE3FB79F8
    //可以证明是连续的内存
    //数组内存地址 和 数组首位内存地址 一样
    printf("数组+0:%#X\n",(intArray + 0));
    printf("数组+1:%#X\n",(intArray + 1));
    printf("数组+2:%#X\n",(intArray + 2));


    //c 面向过程， 没有面向对象 没有class
    //c++ 面向对象  和java一摸一样 有class



    // TODO 动态内存申请 （堆区）
    //例子  声明都是在 栈区
    int *p1; //悬空指针
    long *p2; //悬空指针

    //动态申请时 内部回去检测 是否有可以用的内存，里面可能会存在垃圾数据
    int *p3 = calloc(10,sizeof(int));
    //初始化 清空
    memset(p3,NULL,10 * sizeof(int));

    //释放
    free(p3);

    //释放之后 指针就成了野指针
    p3 = 0; //p3 = NULL; 效果一样
}



void NdkCode2(){ ndk2Init(); }



