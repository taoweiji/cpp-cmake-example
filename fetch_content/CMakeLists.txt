cmake_minimum_required(VERSION 3.17)
project(fetch_content_example)
include(FetchContent)
#FetchContent_Declare(jsoncpp
#        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
#        GIT_TAG 1.9.4)
# 建议使用压缩包的方式依赖，下载速度更快
FetchContent_Declare(jsoncpp
        URL https://github.com/open-source-parsers/jsoncpp/archive/1.9.4.tar.gz)
FetchContent_MakeAvailable(jsoncpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)