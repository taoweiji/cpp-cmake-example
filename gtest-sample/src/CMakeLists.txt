cmake_minimum_required(VERSION 3.10.2)
project(src)
# 定义需要参与编译的源文件
aux_source_directory(. source)
# 把源码添加进来参与编译
add_library(${PROJECT_NAME} ${source})
# 定义需要暴露的头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})