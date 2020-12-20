cmake_minimum_required(VERSION 3.4.1)
#打印log 1
message(im cmakelist)
message("当前 CMake的路径是${CMAKE_SOURCE_DIR}")
file(GLOB allCpp *.cpp)
add_library(
        native-lib
        SHARED
        #native-lib.cpp
        ${allCpp}
)

#导入静态库 get 是名字
add_library(get STATIC IMPORTED)
#导入静态库 路径  get 是名字
set_target_properties(get PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libTest_te.a)

##导入动态库 Test 是名字
#add_library(Test SHARED IMPORTED)
##导入动态库 路径 Test 名字
#set_target_properties(Test PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibsssss/${CMAKE_ANDROID_ARCH_ABI}/libTest.so)

find_library(
        log-lib
        log )

message("当前loglib 路径 ${log-lib}")

target_link_libraries(
        native-lib
        ${log-lib}
#        Test
        get
)