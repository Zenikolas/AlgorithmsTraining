#include <assert.h>
#include <iostream>

// Implement a method to perform basic string compression using the counts of
// repeated characters. For example, the string aabcccccaaa would become
// a2blc5a3, If the "compressed" string would not become smaller than the
// original string, your method should return the original string. You can
// assume the string has only uppercase and lowercase letters (a - z).

size_t coundDigitInNumber(size_t number) {
  if (number == 0)
    return 1;
  size_t count = 0;
  while (number > 0) {
    number /= 10;
    ++count;
  }

  return count;
}

std::string compress(const std::string &str) {
  if (str.size() <= 2) {
    return str;
  }

  size_t futureSize = 0;
  char prev = str[0];
  size_t count = 1;
  for (int i = 1; i < str.size(); ++i) {
    if (str[i] != prev) {
      futureSize += coundDigitInNumber(count) + 1;
      prev = str[i];
      count = 1;
    } else {
      ++count;
    }
  }

  futureSize += coundDigitInNumber(count) + 1;

  if (futureSize >= str.size()) {
    return str;
  }

  std::string newStr;
  newStr.reserve(futureSize);
  prev = str[0];
  count = 1;
  for (int i = 1; i < str.size(); ++i) {
    if (str[i] != prev) {
      newStr.append(prev + std::to_string(count));
      count = 1;
      prev = str[i];
    } else {
      ++count;
    }
  }

  newStr.append(prev + std::to_string(count));

  return newStr;
}

int main() {
  assert(1 == coundDigitInNumber(0));
  assert(1 == coundDigitInNumber(1));
  assert(1 == coundDigitInNumber(9));
  assert(2 == coundDigitInNumber(10));
  assert(3 == coundDigitInNumber(100));
  assert(4 == coundDigitInNumber(1000));

  assert("ab" == compress("ab"));
  assert("a" == compress("a"));
  assert("" == compress(""));
  assert("abc" == compress("abc"));
  assert("abbbbc" == compress("abbbbc"));
  assert("a1b4c2" == compress("abbbbcc"));

  return 0;
}