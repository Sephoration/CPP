#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(thread LANGUAGES C CXX)

#变量定义
set(SOURCES main.c thrd_pool.c thrd_pool.h)

#添加可执行文件
add_executable(thread ${SOURCES})
