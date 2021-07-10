#include <fmt/core.h>
#include "gtest/gtest.h"
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/os.h>
#include <fmt/ranges.h>

using namespace std;

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SuiteName, TestName1) {
    fmt::print("Hello, world!\n");
}

TEST(SuiteName, TestName2) {
    std::string s = fmt::format("The answer is {}.", 42);
}

TEST(SuiteName, TestName3) {
    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");
}

TEST(SuiteName, TestName4) {
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
}

TEST(SuiteName, TestName5) {
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}\n", v);
}

TEST(SuiteName, TestName6) {
    auto out = fmt::output_file("guide.txt");
    out.print("Don't {}", "Panic");
}

TEST(SuiteName, TestName7) {
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
               fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");
}

TEST(SuiteName, TestName8) {
    fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.",
               fmt::arg("name", "World"), fmt::arg("number", 42));
}

TEST(SuiteName, TestName9) {
    std::string s = fmt::format("The answer is {:.2f}", 1.12345678);
    ASSERT_EQ("The answer is 1.12", s);
}

