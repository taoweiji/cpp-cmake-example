# C++：CMake 项目集成 GTest 单元测试教程

单元测试是对软件基本组成单元进行的测试，可以用于对某个功能或者某个类或某个函数进行测试。善用单元测试可以有效提高开发效率，使用单元测试的编写代码也更加可靠性。GTest 全程 Google Test，是 Google 推出的 C++ 测试框架，可以提供编写单元测试用例的效率。本文示例是基于[ clion ](https://www.jetbrains.com/clion/) 编写的程序，这是至今最好用的 C++ IDE，极力推荐使用。
### 下载GTest到项目
首先到 [googletest](https://github.com/google/googletest/) 下载源码，由于项目中已经包含了  `CMakeLists.txt` 文件，只需要把代码复制到项目中，如果 cmake 的版本低于 3.11.0，推荐通过 git submodule 方式引入到项目，cmake 3.11.0  以上通过 [FetchContent](https://github.com/taoweiji/cpp-cmake-example/tree/master/fetch_content) 添加依赖，不需要把源码拷贝进来正式项目。

### 目录结构
这里推荐把 gtest 源码拷贝到 third_party 目录下。
```
├── CMakeLists.txt
├── src
│   ├── CMakeLists.txt
│   ├── add.cpp
│   └── add.h
├── test
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── test.cpp
└── third_party
    └── gtest
        ├── googletest
        ├── CMakeLists.txt
        └── ...
```
### 编写代码
src/add.h
```
#ifndef ADD_HPP
#define ADD_HPP
int add(int a, int b);
#endif // ADD_HPP
```
src/add.cpp
```
#include "add.h"

int add(int a, int b) {
    return a + b;
}
```
src/CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10.2)
project(src)
# 定义需要参与编译的源文件
aux_source_directory(. source)
# 把源码添加进来参与编译
add_library(${PROJECT_NAME} ${source})
# 定义需要暴露的头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
```


### 编写单元测试用例
test/CMakeLists.txt
```
cmake_minimum_required(VERSION 3.17)
project(test)
add_executable(${PROJECT_NAME} main.cpp test.cpp)
target_link_libraries(${PROJECT_NAME} gtest src)
```
test/test.cpp
```
#include "gtest/gtest.h"
#include "add.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SuiteName, TestName1) {
    int expected = 3;
    int actual = add(1, 2);
    ASSERT_EQ(expected, actual);
}

TEST(SuiteName, TestName2) {
    int expected = 3;
    int actual = add(1, 3);
    ASSERT_EQ(expected, actual);
}
```
main.cpp
```
#include "gtest/gtest.h"
#include "add.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### 根目录 CMakeLists.txt
```
cmake_minimum_required(VERSION 3.17)
project(gtest_example)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/gtest)
```

### 运行用例
##### 运行所有用例
可以通过运行 main 函数，会运行所有的测试用例。
##### 对单个文件所有用例测试
右击页面的空白处，可以对整个文件的用例进行测试。
![](https://upload-images.jianshu.io/upload_images/2431302-b13c0eb4868e55c9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
##### 测试单个用例
也可以点击测试用例的前面的运行按钮对用例进行单独测试。
![](https://upload-images.jianshu.io/upload_images/2431302-fe642a15be7ce3fc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 示例源码
https://github.com/taoweiji/cpp-cmake-example/tree/master/gtest-sample






