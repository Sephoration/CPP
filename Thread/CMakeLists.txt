#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(thread LANGUAGES C CXX)

# 旧的 C 线程池
set(SOURCES main.c thrd_pool.c thrd_pool.h)
add_executable(thread_pool_c ${SOURCES})

# C++ 多线程练习
add_executable(thread_basics thread_basics.cpp)
add_executable(thread_sync_mutex thread_sync_mutex.cpp)
add_executable(thread_producer_consumer thread_producer_consumer.cpp)
add_executable(thread_atomic thread_atomic.cpp)
add_executable(thread_pool thread_pool.cpp)