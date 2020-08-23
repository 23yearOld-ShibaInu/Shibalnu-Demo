//
// Created by Trust on 2020/7/27.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "ndk_code3.h"

//别名
typedef long long l ;


//结构体
struct Student{
    //结构体 ：里面所有的成员，默认都是public
    char *name;
    int age;
    char sex;
};


//共用体
union MyCount{
    int countValueInfo1;
    int countValueInfo2;
    int countValueInfo3;
    int countValueInfo4;
    int countValueInfo5;
    int countValueInfo6;
    int countValueInfo7;
    int countValueInfo8;
};

struct Worker{
    char *name;
    int age;
    char sex;
}s1,s2;

typedef struct {
    char * name;
} dog;

#pragma pack(2)//内部使用对其算法  唯一的目的 是对齐  通常情况下 不会指定
//目的是节约内存。内部算法方便位移
struct User{
    int num1;
    char num2;
    int num3;
};

//还原

//#pragma pack() //对齐的还原


void ndk3Init(){
    //别名
    l number1 = 1231231;
    printf("别名: %lld\n",number1);


    /**
     * TODO 结构体
     */

    struct  Student student; //栈中定义

    student.name = "耐看的李先生";
    student.age = 25;
    student.sex = 'm';

    printf("结构体: %s , %d , %c \n",student.name,student.age,student.sex);

    s1.name = "李先生1";
    s1.age = 52;
    s1.sex = 'w';

    s2.name = "李先生2";
    s2.age = 522;
    s2.sex = 's';

    printf("结构体: s1:%s ,s1: %d , s1:%c \n",s1.name,s1.age,s1.sex);
    printf("结构体: s2:%s ,s2: %d , s2:%c \n",s2.name,s2.age,s2.sex);

    dog d;
    d.name = "i'm dog!";

    printf("dog 结构体 :%s\n",d.name);


    struct User u;
    printf("user 占用的字节:%lu\n",sizeof(u));


    //TODO ndk3   24：29

    //TODO 共用体
    printf("---------共用体---------\n");

    union MyCount myCount;
    myCount.countValueInfo1 = 10;
    printf("countValueInfo1:%d\n",myCount.countValueInfo1);
    myCount.countValueInfo2 = 200;
    printf("countValueInfo1:%d\n",myCount.countValueInfo1);

    printf("共用体占用字节书:%lu\n",sizeof(myCount));

    //场景
    //保证最新值  同类型 会共用最新的额

    //#include  并不是倒入包
    //直接文本替换 就是把倒入的内容全部替换到 #include xx 行
    //弊端 体积会变大
}
