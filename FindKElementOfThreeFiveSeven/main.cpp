// Description:
// Design an algorithm to find the kth number such that the only prime factors are 3, 5
// and 7
#include <gtest/gtest.h>

#include <queue>
#include <algorithm>

using ull = unsigned long long;

size_t getMinIdx(const std::queue<ull>& q3,
                 const std::queue<ull>& q5,
                 const std::queue<ull>& q7) {
    ull min = std::min(q3.front(), q5.front());
    min = std::min(min, q7.front());

    if (min == q3.front()) {
        return 3;
    } else if (min == q5.front()) {
        return 5;
    }

    return 7;
}

ull findKthELem(int k) {
    if (k < 0) {
        return 0;
    }

    if (k == 0) {
        return 1;
    }

    std::queue<ull> q3;
    q3.push(3);
    std::queue<ull> q5;
    q5.push(5);
    std::queue<ull> q7;
    q7.push(7);
    ull min{};
    for (int i = 0; i < k; ++i) {
        size_t idx = getMinIdx(q3, q5, q7);
        switch (idx) {
            case 3:
                min = q3.front();
                q3.push(3 * min);
                q5.push(5 * min);
                q7.push(7 * min);
                q3.pop();
                break;
            case 5:
                min = q5.front();
                q5.push(5 * min);
                q7.push(7 * min);
                q5.pop();
                break;
            case 7:
                min = q7.front();
                q7.push(7 * min);
                q7.pop();
                break;
            default:
                assert(false);
        }
    }

    return min;
}

TEST(FindKElementOfThreeFiveSevenTest, SmokeTest) {
    ASSERT_EQ(27, findKthELem(8));
    ASSERT_EQ(15, findKthELem(5));
    ASSERT_EQ(1, findKthELem(0));
    ASSERT_EQ(0, findKthELem(-1));
}
