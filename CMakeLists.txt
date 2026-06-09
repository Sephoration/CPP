#最低限CMake版本要求
cmake_minimum_required(VERSION 3.14)  

#项目名称和使用的语言
project(CPP_Projects LANGUAGES C CXX)

#添加子目录
add_subdirectory(Thread)
add_subdirectory(EduMan)
add_subdirectory(Test)
add_subdirectory(STL)
#暂时跳过TinySTL的构建，因为它有较多的错误需要修复
#add_subdirectory(TinySTL)
