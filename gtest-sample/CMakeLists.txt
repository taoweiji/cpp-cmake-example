cmake_minimum_required(VERSION 3.17)
project(gtest_example)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/gtest)

