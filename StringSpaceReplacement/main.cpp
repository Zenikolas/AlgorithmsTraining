// Description:
// Write a method to replace all the spaces in a string with ‘%20’.
// You may assume that the string has sufficient space at the end to hold the additional
// characters and that you are given the “true” length of the string.

#include <cstring>

#include <gtest/gtest.h>

void strSpaceReplace(char* str) {
    const size_t N = strlen(str);
    size_t spaceCount = 0;
    const char* spaceRepl = "%20";
    const size_t spaceReplSize = strlen(spaceRepl);
    for (size_t i = 0; i < N; ++i) {
        if (str[i] == ' ') ++spaceCount;
    }

    const size_t NR = N + 2 * spaceCount;
    size_t resultIdx = NR - 1;
    str[NR] = '\0';
    for (size_t i =0; i < N; ++i) {
        size_t curretnIdx = N - i - 1;
        if (str[curretnIdx] != ' ') {
            str[resultIdx] = str[curretnIdx];
        } else {
            resultIdx -= spaceReplSize - 1;
            memcpy(str + resultIdx, spaceRepl, spaceReplSize);
        }
        --resultIdx;
    }
}


TEST(StrSpaceReplace, Simple) {
    char buffer[] = "Mr John Smith\0    ";
    const char* expected = "Mr%20John%20Smith";
    strSpaceReplace(buffer);
    ASSERT_STREQ(expected, buffer);
}