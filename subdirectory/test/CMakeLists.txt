cmake_minimum_required(VERSION 3.17)
project(test)
# 创建可执行程序
add_executable(${PROJECT_NAME} main.cpp)
# 链接别的库
target_link_libraries(${PROJECT_NAME} project3)