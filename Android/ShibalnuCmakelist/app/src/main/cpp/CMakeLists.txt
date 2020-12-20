cmake_minimum_required(VERSION 3.4.1)

file(GLOB allCpp*.cpp)

add_library(
             native-lib   # 最终生成的名字  lib + native-lib.so
             SHARED      # 动态库
             native-lib.cpp # 源文件 可以批量导入
             ${allCpp}
)

#可以省略
#find_library(
#              log-lib
#
#              #ndk 路径下面liblog.so == log
#              log
#)

#引入FFmpeg的头文件

include_directories(${CMAKE_SOURCE_DIR}/include)
#引入FFmpeg的库文件，设置内部方式引入 指定库的目录是 -L 具体的库-l
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}")
add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libavformat.so)

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libavcodec.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libavfilter.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libavutil.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libswresample.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/${CMAKE_ANDROID_ARCH_ABI}/libswscale.so)

target_link_libraries(
                       native-lib
#                       ${log-lib} 可以用下面的 log代替
                        log   #可以直接使用log
                        #引入libz.so
                        z
                        #具体库文件 链接到总库
                        #这样写有坑 会报错  有顺序依赖关系
                        #avcodec avfilter avformat avutil swresample swscale
                        #先把有依赖的库，先依赖进来
                        avformat avcodec avfilter avutil swresample swscale
)