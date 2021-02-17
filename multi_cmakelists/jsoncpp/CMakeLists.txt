cmake_minimum_required(VERSION 3.17)
project(jsoncpp)
add_library(${PROJECT_NAME} json_reader.cpp json_value.cpp json_writer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)