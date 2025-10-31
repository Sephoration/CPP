cmake_minimum_required(VERSION 3.15)
project( Project_1 ) 

# 将当前目录（.）的所有源码文件保存在SRC_LIST变量中
aux_source_directory(. SRC_LIST)

add_executable( Project_1 ${SRC_LIST} )





