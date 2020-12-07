
cmake_minimum_required(VERSION 3.4.1)


file(GLOB sourceFile studyCpp/*.h studyCpp/*.cpp)


add_library(
        native-lib #最终生成的lib + native-lib.so
        SHARED #指定动态库
        native-lib.cpp

        # studyCpp/Student.h

        ${sourceFile}
        )



find_library(
        log-lib
        log # liblog.so == log
)



target_link_libraries(
        native-lib
        ${log-lib}
        # libz.so
        z

)