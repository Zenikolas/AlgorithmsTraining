#include <gtest/gtest.h>
#include <gmock/gmock.h>
// generate list of first prime numbers which are less than specified maximum

std::vector<size_t> genPrimeList(const size_t size)
{
    if (size < 2) {
        return {};
    }

    std::vector<size_t> ret;
    ret.reserve(size);
    bool primes[size];
    for (size_t i = 0; i < size; ++i) {
        primes[i] = true;
    }
    size_t prime = 2;
    while (prime < size) {
        for (size_t i = prime * prime; i  < size; i += prime) {
            primes[i] = false;
        }

        ++prime;
        while (!primes[prime]) { ++prime; }
    }

    for (size_t i = 2; i < size; ++i) {
        if (primes[i]) ret.emplace_back(i);
    }

    return ret;
}

TEST(PrimeListTest, SmokeTest)
{
    ASSERT_THAT(genPrimeList(5), ::testing::ElementsAre(2, 3));
    ASSERT_THAT(genPrimeList(10), ::testing::ElementsAre(2, 3, 5, 7));
}
