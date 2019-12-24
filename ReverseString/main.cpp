#include <cstring>
#include <iostream>

#include <gtest/gtest.h>

// Description:
// Implement a function void reverse(char* str) which reverses a null-terminated
// string.

void reverse(char *str) {
    size_t size = strlen(str);
    if (size < 2) {
        return;
    }

    size_t mid = size / 2;
    for (size_t i = 0; i < mid; ++i) {
        size_t lhs_index = i;
        size_t rhs_index = size - i - 1;
        std::swap(str[lhs_index], str[rhs_index]);
    }
}

TEST(reverseString, simple) {
    char str[] = "abc";
    reverse(str);

    ASSERT_STREQ(str, "cba");
}

TEST(reverseString, oneChar) {
    char str[] = "a";
    reverse(str);

    ASSERT_STREQ(str, "a");
}

TEST(reverseString, oddStr) {
    char str[] = "abcde";
    reverse(str);

    ASSERT_STREQ(str, "edcba");
}

TEST(reverseString, evenStr) {
    char str[] = "abcdef";
    reverse(str);

    ASSERT_STREQ(str, "fedcba");
}