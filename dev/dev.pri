####################################################################################################
# DEVHOME 是开发主目录，放置与运行相关的文件，运行程序放在此目录的 bin 子目录下(必须定义)
####################################################################################################

# 需要要环境变量 DEVHOME ，指向开发目录
DEVHOME = ../../../

# 设置系统执行文件路径、库文件路径、头文件包含路径变量
BIN_PATH = $$DEVHOME/bin
BUILD_PATH = $$DEVHOME/dev/build
LIB_PATH = $$DEVHOME/dev/lib
INCLUDE_PATH = $$DEVHOME/dev/include
SOURCE_PATH = $$DEVHOME/dev/source
DEBUG_PATH = $$BUILD_PATH/debug
RELEASE_PATH = $$BUILD_PATH/release

QMAKE_LIBDIR *= $$LIB_PATH
DEPENDPATH *= . $$INCLUDE_PATH
INCLUDEPATH *= . $$INCLUDE_PATH
