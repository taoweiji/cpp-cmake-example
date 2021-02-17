cmake_minimum_required(VERSION 3.17)
project(project3)
add_library(${PROJECT_NAME} project3.cpp)
# 链接别的库
target_link_libraries(${PROJECT_NAME} project1 project2)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
