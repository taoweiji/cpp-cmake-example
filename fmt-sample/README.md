
[fmt](https://github.com/fmtlib/fmt) 是一个先进的文本格式库，具有现代语言的特征，用来代替 C 的 stdio 和 C++ iostreams。实现了 C++20 的 [std::format](https://en.cppreference.com/w/cpp/utility/format/format) 标准。fmt 基于 CMakeLists.txt 开发，引入到项目中非常简单。
#### 通过 FetchContent 引入项目
```
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(fmt-sample)
include(FetchContent)

FetchContent_Declare(fmt
        URL https://github.com/fmtlib/fmt/archive/refs/tags/8.0.1.tar.gz)
FetchContent_MakeAvailable(fmt)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} fmt)
```

#### 格式化输出
```
#include <fmt/core.h>

int main() {
  fmt::print("Hello, world!\n");
}
```
#### 格式字符串
```
std::string s = fmt::format("The answer is {}.", 42);
// s == "The answer is 42."
```
#### 使用位置顺数参数
```
std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
// s == "I'd rather be happy than right."
```
#### 时间格式化
```
#include <fmt/chrono.h>

int main() {
  using namespace std::literals::chrono_literals;
  fmt::print("Default format: {} {}\n", 42s, 100ms);
  fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
}
```
#### 输出列表
```
#include <vector>
#include <fmt/ranges.h>

int main() {
  std::vector<int> v = {1, 2, 3};
  fmt::print("{}\n", v);
}
```
#### 输出到文件
```
#include <fmt/os.h>

int main() {
  auto out = fmt::output_file("guide.txt");
  out.print("Don't {}", "Panic");
}
```
#### 输出带颜色到控制台
```
#include <fmt/color.h>

int main() {
  fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
             "Hello, {}!\n", "world");
  fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
             fmt::emphasis::underline, "Hello, {}!\n", "мир");
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
             "Hello, {}!\n", "世界");
}
```
#### 测试示例


#### 来源
https://github.com/fmtlib/fmt




