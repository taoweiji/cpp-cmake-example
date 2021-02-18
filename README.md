# C++工程：CMake 添加第三方库依赖 find_library、FetchContent、CPM等
CMake 已经成为了C++工程管理的主流方式，功能非常强大，现在大多数的 C++ 库都已经支持CMake，下面以 [jsoncpp](https://github.com/open-source-parsers/jsoncpp) 为例，介绍几种引入第三方库的方式。


## 1. 代码依赖
这种方式是把第三方库的完整代码直接添加到我们的项目中，当做项目代码的一部分进行编译，这种方式会把第三方代码和我们的代码混在一起，并不推荐使用。首先我们需要到 [jsoncpp](https://github.com/open-source-parsers/jsoncpp) 下载需要的头文件和实现代码，放到项目当中。
##### 工程文件目录
```
├── CMakeLists.txt
├── jsoncpp
│   ├── include
│   │   └── json
│   │       ├── autolink.h
│   │       ├── config.h
│   │       ├── features.h
│   │       ├── forwards.h
│   │       ├── json.h
│   │       ├── reader.h
│   │       ├── value.h
│   │       └── writer.h
│   ├── json_batchallocator.h
│   ├── json_internalarray.inl
│   ├── json_internalmap.inl
│   ├── json_reader.cpp
│   ├── json_value.cpp
│   ├── json_valueiterator.inl
│   └── json_writer.cpp
└── main.cpp
```
##### CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.17)
project(includes_full_code)
set(CMAKE_CXX_STANDARD 14)
# 包含头文件
include_directories(./jsoncpp/include)
set(jsoncpp jsoncpp/json_reader.cpp jsoncpp/json_writer.cpp jsoncpp/json_value.cpp)
# 添加可执行代码
add_executable(includes_full_code main.cpp ${jsoncpp})
```
##### main.cpp
后面的示例的main.cpp都是一样
```cpp
#include <iostream>
#include "json/json.h"
int main() {
    Json::Value json;
    json["name"] = "Wiki";
    json["age"] = 18;
    std::cout << json.toStyledString() << std::endl;
    return 0;
}
```
完整代码：[includes_full_code_exmaple](https://github.com/taoweiji/cpp-dependency-management-example/includes_full_code)


## 2. 内部工程依赖
这种方式和上面 `代码依赖` 的方式类似，不同的是内部工程依赖会把第三方库的管理职责交给第三方库工程CMakeLists.txt文件，这种方式的好处是职责分明，是最常用的依赖方式。
##### 工程文件目录
目录结果和上面的案例相似，不同的是jsoncpp文件夹多了一个 `CMakeLists.txt` 文件
```makefile
├── CMakeLists.txt
├── jsoncpp
│   ├── CMakeLists.txt
│   ├── include
│   │   └── json
│   │       ├── autolink.h
│   │       ├── config.h
│   │       ├── features.h
│   │       ├── forwards.h
│   │       ├── json.h
│   │       ├── reader.h
│   │       ├── value.h
│   │       └── writer.h
│   ├── json_batchallocator.h
│   ├── json_internalarray.inl
│   ├── json_internalmap.inl
│   ├── json_reader.cpp
│   ├── json_value.cpp
│   ├── json_valueiterator.inl
│   └── json_writer.cpp
└── main.cpp
```
##### jsoncpp/CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.17)
project(jsoncpp)
add_library(${PROJECT_NAME} json_reader.cpp json_value.cpp json_writer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
```
##### CMakeLists.txt
```makefile
cmake_minimum_required(VERSION 3.17)
project(multi_cmakelists)
# 添加子工程
add_subdirectory(jsoncpp)
add_executable(${PROJECT_NAME} main.cpp)
# 链接子工程
target_link_libraries(${PROJECT_NAME} jsoncpp)
```
完整代码：[multi_cmakelists_example](https://github.com/taoweiji/cpp-dependency-management-example/multi_cmakelists)


> 这种方式除了引入第三方依赖，通常我们也会用这种方式来管理项目中的各个子模块，每个模块都有独立的CMakeLists.txt文件，从而实现子工程的单独引用，源码请看 [subdirectory_example](https://github.com/taoweiji/cpp-dependency-management-example/subdirectory)。



## 3. find_library：编译库方式引入
这种方式是用来依赖已经打包好的二进制文件，这种方式也分为静态库（.a、.lib）和动态库（.so、.dll）方式引入，这种方式也可以查找本机已经安装好的库，比如 Android 的 log 库就是通过这种方式引入。
##### 生成.a文件
运行上面的 `内部工程依赖` 案例后，我们我们可以从项目中找到编译好的 multi_cmakelists/cmake-build-debug/jsoncpp/libjsoncpp.a 文件。
##### 工程文件目录
和上面不同的是，这里只需要导入jsoncpp的头文件和.a文件。
```
├── CMakeLists.txt
├── jsoncpp
│   ├── include
│   │   └── json
│   │       ├── autolink.h
│   │       ├── config.h
│   │       ├── features.h
│   │       ├── forwards.h
│   │       ├── json.h
│   │       ├── reader.h
│   │       ├── value.h
│   │       └── writer.h
│   └── libjsoncpp.a
└── main.cpp
```
##### CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.17)
project(find_library_example)
include_directories(jsoncpp/include)
add_executable(${PROJECT_NAME} main.cpp)
find_library(jsoncpp_lib NAMES jsoncpp PATHS ./jsoncpp)
target_link_libraries(${PROJECT_NAME} ${jsoncpp_lib})
```
完整代码：[find_library_example](https://github.com/taoweiji/cpp-dependency-management-example/find_library)


> 这种方式在 Android 开发很常见，比如我们引入xlog实现日志打印就可以通过这种方式实现，代码参考 [xlog_example](https://github.com/taoweiji/cpp-dependency-management-example/xlog)。


## 4. FetchContent
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) 是 cmake 3.11.0 版本开始提供的功能，可以非常方便用来添加第三方依赖。
##### 工程文件目录
```
├── CMakeLists.txt
└── main.cpp
```
##### CMakeLists.txt
```bash
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
```
建议通过压缩包的方式引入，因为直接引入git仓库可能会很慢。


完整代码：[fetch_content_example](https://github.com/taoweiji/cpp-dependency-management-example/fetch_content)


> Android SDK 的 CMake 的默认版本是3.10.2，并不支持FetchContent，如果想在Android开发中使用需要安装3.11.0以上版本的cmake，为了降低团队的协同成本，并不建议在 Android 工程使用，建议使用内部工程的方式引入。



## 5. CPM
[CPM.cmake](https://github.com/TheLartians/CPM.cmake) 是在 FetchContent 的基础上封装而来，相比 FetchContent 更加简单易用，使用CPM需要到 [CPM.cmake](https://github.com/TheLartians/CPM.cmake) 下载cmake目录的文件CPM.cmake、get_cpm.cmake和testing.cmake，添加到项目当中。
##### 工程文件目录
```
├── CMakeLists.txt
├── cmake
│   ├── CPM.cmake
│   ├── get_cpm.cmake
│   └── testing.cmake
└── main.cpp

```
##### CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.17)
project(cpm_example)
include(cmake/CPM.cmake)
#CPMAddPackage(
#        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
#        GIT_TAG 1.9.4)
# 建议使用压缩包的方式依赖，下载速度更快
CPMAddPackage(
        NAME jsoncpp
        URL https://github.com/open-source-parsers/jsoncpp/archive/1.9.4.tar.gz)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
```
这种方式的细节不需要我们自己处理，都交给了CPM解决，这种方式也同样不建议在 Android 工程使用。


完整代码：[cpm_example](https://github.com/taoweiji/cpp-dependency-management-example/cpm)
## 6. find_package
[find_package](https://cmake.org/cmake/help/latest/command/find_package.html) 是 cmake 3.19.0 版本开始提供的功能，可以非常方便添加，这种方式主要是从本机上查找已经安装好的库，需要提前通过命令安装。
##### 安装jsoncpp
我的Mac OS，通过下面方法安装可以成功，其它系统可能会出错
```bash
# 拉取代码
git clone https://github.com/open-source-parsers/jsoncpp
cd jsoncpp
mkdir -p build/debug
cd build/debug
# 生成Makefile
cmake -DCMAKE_BUILD_TYPE=release -DBUILD_STATIC_LIBS=OFF -DBUILD_SHARED_LIBS=ON -DARCHIVE_INSTALL_DIR=. -DCMAKE_INSTALL_INCLUDEDIR=include -G "Unix Makefiles" ../..
# 安装
make && make install
```
> 如果提示没有安装cmake，需要自行安装cmake



##### 工程文件目录
```
├── CMakeLists.txt
└── main.cpp
```
##### CMakeLists.txt
```bash
cmake_minimum_required(VERSION 3.17)
project(find_package_example)
find_package(jsoncpp REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
```
##### 完整代码：[find_package_example](https://github.com/taoweiji/cpp-dependency-management-example/find_package)


> 使用这种方式是需要有个大前提，电脑必须已经安装好了对应的库，否则无法正常工作，这种方式只有在特定的场景下使用，比如调用电脑的opencv、openssl。

### 总结
C++添加依赖的方式有很多种，没有绝对的好与差，应该根据不同的场景使用不同的依赖方式，例如在Android工程中，我们应该尽量不要改变默认的CMake版本，避免增加环境的依赖。
