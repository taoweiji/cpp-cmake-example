cmake_minimum_required(VERSION 3.17)
project(project1)
# 创建可执行程序
add_library(${PROJECT_NAME} project1.cpp)
include_directories(./)
# 链接别的库
#target_link_libraries(${PROJECT_NAME} project2 project3)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
