cmake_minimum_required(VERSION 3.16)
project(Cpp) #目标库
#TODO win才需要配置 mac 不需要配置
# TODO 引入线程库所有头文件
#include_directories("路径/Pre-built.2/include")
# TODO 引入线程库库文件 链接库
#link_directories("路径/Pre-built.2/lib/x86或其他")
#TODO 解决pthread源码缺少宏的问题
#CXX c++  c = c
#"${CMAKE_CXX_FLAGS}"  不破坏源码配置 在源码配置基础上增加 "${CMAKE_CXX_FLAGS} -D你需要配置的宏" 必须要跟-D连接
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D你需要配置的宏")

set(CMAKE_CXX_STANDARD 20)

add_executable(Cpp main.cpp main.c main.h ndk6/ndk6.cpp ndk6/ndk6.h ndk6/Log.h )

# TODO
#target_link_libraries(Cpp pthreadVC2)


