#include <iostream>

#include <gtest/gtest.h>


bool checkIfAllUniqueCharacters(const std::string &str) {
    uint64_t counter = 0;
    for (auto &letter : str) {
        uint64_t index = 1 << (letter - 'a');
        if (index & counter) {
            return false;
        }
        counter += index;
    }

    return true;
}

TEST(UniqueCharacterTest, Simple) {
    ASSERT_TRUE(checkIfAllUniqueCharacters("abc"));
}

TEST(UniqueCharacterTest, OneChar) {
    ASSERT_TRUE(checkIfAllUniqueCharacters("a"));
}

TEST(UniqueCharacterTest, Empty) {
    ASSERT_TRUE(checkIfAllUniqueCharacters(""));
}

TEST(UniqueCharacterTest, Repeated) {
    ASSERT_FALSE(checkIfAllUniqueCharacters("abcdefc"));
}