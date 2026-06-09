#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(STL LANGUAGES CXX)

#为STL目录中的每个test_*.cpp文件创建可执行文件
file(GLOB TEST_SOURCES "test_*.cpp")
foreach(SOURCE ${TEST_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
endforeach()
