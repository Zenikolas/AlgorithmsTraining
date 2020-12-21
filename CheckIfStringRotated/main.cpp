#include <string>

#include <gtest/gtest.h>
// check of candidate string is rotated from original one

bool checkIfStringRotated(const std::string& original, const std::string& candidate)
{
    // assume original = xy; then rotated string is yx. If we compound yxyx then in the
    // middle will be original string
    std::string yxyx = candidate + candidate;
    size_t pos = yxyx.find(original);
    if (pos == std::string::npos) {
        return false;
    }
    return  yxyx.substr(pos, original.size()) ==  original;
}

TEST(CheckIfStringRotated, SmokeTest)
{
    ASSERT_TRUE(checkIfStringRotated("bottleneck", "neckbottle"));
}

TEST(CheckIfStringRotated, SameTest)
{
    ASSERT_TRUE(checkIfStringRotated("bottleneck", "bottleneck"));
}

TEST(CheckIfStringRotated, SameSymbolsTest)
{
    ASSERT_TRUE(checkIfStringRotated("aaaaaaa", "aaaaaaa"));
}
