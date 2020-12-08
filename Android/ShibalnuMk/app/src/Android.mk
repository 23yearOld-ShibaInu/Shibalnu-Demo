# 这里面能够决定编译 Login.c

#源文件在的位置。宏函数 my-dir 返回当前目录（包含 Android.mk 文件本身的目录）的路径。
# LOCAL_PATH 其实就是Android.mk文件本身的目录的路径
# 1：指定构建脚本位置
LOCAL_PATH := $(call my-dir)

$(info "LOCAL_PATH:======== ${LOCAL_PATH}")

#引入其他makefile文件。CLEAR_VARS 变量指向特殊 GNU Makefile，可为您清除许多 LOCAL_XXX 变量
#不会清理 LOCAL_PATH 变量
# 2:清理
include $(CLEAR_VARS)

# 预编译库 提前编译好的库


LOCAL_MODULE := libTest
LOCAL_SRC_FILES := ../libs/libTest.a
#LOCAL_SRC_FILES := ../libs/libTest.so

#告诉构建工具 是静态库
include ${PREBUILT_STATIC_LIBRARY}
#告诉构建工具 是动态库
#include ${PREBUILT_SHARED_LIBRARY}
#开始清理
include $(CLEAR_VARS)
#结尾

# 3:指定库名字
#存储您要构建的模块的名称 每个模块名称必须唯一，且不含任何空格
#如果模块名称的开头已是 lib，则构建系统不会附加额外的前缀 lib；而是按原样采用模块名称，并添加 .so 扩展名。
LOCAL_MODULE := MyLoginJar

#包含要构建到模块中的 C 和/或 C++ 源文件列表 以空格分开
LOCAL_SRC_FILES := main/cpp/Login.c \
main/cpp/Reigster.c



#链接
#LOCAL_SHARED_LIBRARIES :=  libTest
LOCAL_STATIC_LIBRARIES :=  libTest


# 导入
#LOCAL_LDLIBS := -llog  (没有成功过)
LOCAL_LDLIBS := -lm -llog


#构建静态库
#include $(BUILD_STATIC_LIBRARY)

#构建动态库
include $(BUILD_SHARED_LIBRARY)