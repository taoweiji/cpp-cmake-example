#include "gtest/gtest.h"
#include "add.h"


TEST(SuiteName, TestName1) {
    int expected = 3;
    int actual = add(1, 2);
    ASSERT_EQ(expected, actual);
}

TEST(SuiteName, TestName2) {
    int expected = 4;
    int actual = add(1, 4);
    ASSERT_EQ(expected, actual);
}