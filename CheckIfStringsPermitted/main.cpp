#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>

// Description
// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.

bool checkIfPermutted(const std::string &lhs, const std::string &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  std::string lhs_copy(lhs);
  std::string rhs_copy(rhs);

  std::sort(lhs_copy.begin(), lhs_copy.end());
  std::sort(rhs_copy.begin(), rhs_copy.end());

  return lhs_copy == rhs_copy;
}

TEST(CheckIfPermuttedTest, oneLetterSizeGood) {
  ASSERT_TRUE(checkIfPermutted("a", "a"));
}

TEST(CheckIfPermuttedTest, oneLetterSizebad) {
  ASSERT_FALSE(checkIfPermutted("a", "b"));
}

TEST(CheckIfPermuttedTest, Simple) {
  ASSERT_TRUE(checkIfPermutted("abc", "bac"));
}

TEST(CheckIfPermuttedTest, SimpleRepeatted) {
  ASSERT_TRUE(checkIfPermutted("aabbbc", "bababc"));
}

TEST(CheckIfPermuttedTest, BadSimple) {
  ASSERT_FALSE(checkIfPermutted("abc", "dab"));
}

TEST(CheckIfPermuttedTest, DifferentSizes) {
  ASSERT_FALSE(checkIfPermutted("abc", "abc "));
}