#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(Test LANGUAGES C CXX)

#为Test目录中的每个cpp文件创建可执行文件
file(GLOB TEST_SOURCES "*.cpp")
foreach(SOURCE ${TEST_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
endforeach()

#为Test目录中的每个c文件创建可执行文件
file(GLOB TEST_SOURCES_C "*.c")
foreach(SOURCE ${TEST_SOURCES_C})
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
endforeach()
