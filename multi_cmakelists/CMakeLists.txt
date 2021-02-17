cmake_minimum_required(VERSION 3.17)
project(multi_cmakelists)
# 添加子工程
add_subdirectory(jsoncpp)
add_executable(${PROJECT_NAME} main.cpp)
# 链接子工程
target_link_libraries(${PROJECT_NAME} jsoncpp)