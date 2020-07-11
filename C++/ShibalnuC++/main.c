#include <stdio.h>

void NdkCode1();

int main() {
//    printf("Hello, World!\n");
    NdkCode1();
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

}



