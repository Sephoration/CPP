#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(TinySTL LANGUAGES CXX)

#设置TinySTL的源文件
file(GLOB_RECURSE TINYSTL_SOURCES "TinySTL/*.cpp")
file(GLOB_RECURSE TINYSTL_HEADERS "TinySTL/*.h")

#创建TinySTL库
add_library(TinySTL STATIC ${TINYSTL_SOURCES} ${TINYSTL_HEADERS})

#为TinySTL的测试文件创建可执行文件
file(GLOB TEST_SOURCES "TinySTL/Test/*Test.cpp")
foreach(SOURCE ${TEST_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
    target_link_libraries(${EXECUTABLE_NAME} TinySTL)
endforeach()
