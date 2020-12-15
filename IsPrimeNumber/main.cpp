#include <cmath>

#include <gtest/gtest.h>
// check if given number is prime

bool isPrimeNumber(int number)
{
    int square = static_cast<int>(std::sqrt(static_cast<double>(number)));
    for (int i = 2; i <= square; ++i) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

TEST(isPrimeNumberTest, OneTest)
{
    ASSERT_TRUE(isPrimeNumber(1));
    ASSERT_TRUE(isPrimeNumber(2));
    ASSERT_TRUE(isPrimeNumber(3));
    ASSERT_FALSE(isPrimeNumber(4));
    ASSERT_TRUE(isPrimeNumber(5));
    ASSERT_FALSE(isPrimeNumber(6));
    ASSERT_TRUE(isPrimeNumber(7));
    ASSERT_FALSE(isPrimeNumber(8));
    ASSERT_FALSE(isPrimeNumber(9));
    ASSERT_FALSE(isPrimeNumber(10));
    ASSERT_TRUE(isPrimeNumber(11));
}
