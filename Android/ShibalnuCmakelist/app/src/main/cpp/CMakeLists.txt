cmake_minimum_required(VERSION 3.4.1)

add_library(
             native-lib   # 最终生成的名字  lib + native-lib.so
             SHARED      # 动态库
             native-lib.cpp # 源文件 可以批量导入
)

#可以省略
#find_library(
#              log-lib
#
#              #ndk 路径下面liblog.so == log
#              log
#)

target_link_libraries(
                       native-lib
#                       ${log-lib} 可以用下面的 log代替
                        log   #可以直接使用log
                        #引入libz.so
                        z
)