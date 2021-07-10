cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(fmt-sample)
include(FetchContent)
#FetchContent_Declare(fmt
#        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#        GIT_TAG 8.0.1)
# 建议使用压缩包的方式依赖，下载速度更快
FetchContent_Declare(fmt
        URL https://github.com/fmtlib/fmt/archive/refs/tags/8.0.1.tar.gz)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(gtest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz)
FetchContent_MakeAvailable(gtest)


add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} fmt gtest)