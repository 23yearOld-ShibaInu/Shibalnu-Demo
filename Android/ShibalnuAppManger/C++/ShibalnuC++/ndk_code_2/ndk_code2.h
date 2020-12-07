//
// Created by Trust on 2020/7/25.
//

#ifndef SHIBALNUC___NDK_CODE2_H
#define SHIBALNUC___NDK_CODE2_H

#endif //SHIBALNUC___NDK_CODE2_H


void ndk2Init();

void doMethod(int *numbrt1,int *number2);

void add(char * flag, ...);

void say(void(*tt)(char*),char *msg);

void * myPrintln(char *msg);

void loginEngine(void(*resultSuccess)(int64_t code,char *msg),void(resultError)(int64_t code,char *msg));

void * loginSuccess(int64_t code,char *msg);
void * loginError(int64_t code,char *msg);