//
// Created by Trust on 2020-08-28.
//
//预处理器执行的时候 保证只引入一次头文件
#pragma once

#include <iostream>

#ifndef SHIBALNUCPP_STUDENT_H
#define SHIBALNUCPP_STUDENT_H

#endif //SHIBALNUCPP_STUDENT_H

class Student {
    //结构体默认都是public
    //默认全是private

//构造函数
public:
    Student();

    Student(int age,int age2,int age3);

    //析构函数
    ~Student();
//成员变量
private:
    int age;
protected:
    int age2;
public:
    int age3;

//函数
public:
    //常量函数
    void setAge1(int age) const ;

    void setAge2(int age);

    //友元函数  破坏了 c++的封闭性
    friend void updateFieldfriend(Student *);

    void updateField(Student *);

    //友元类
    friend class Person;

private:
    int old;
};

//友元类  可以访问 Student 类的私有变量
class Person{
    void updateField(Student * student){
        student->old = 22;
    }
};