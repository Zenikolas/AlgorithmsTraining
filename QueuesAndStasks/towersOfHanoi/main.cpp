#include <gtest/gtest.h>

#include <stack>

class Tower {
    std::stack<int> m_buffer;
public:
    bool add(int value) {
        if (!m_buffer.empty() && m_buffer.top() <= value) {
            std::cerr << "Trying to add disk with bigger size: " << value << " on disk with smaller size: "
                      << m_buffer.top() << std::endl;
            return false;
        }

        m_buffer.push(value);
    }

    void pop() {
        m_buffer.pop();
    }

    int top() const {
        return m_buffer.top();
    }

    size_t size() const {
        return m_buffer.size();
    }
};

void move(Tower& src, Tower& dst, Tower& buffer, size_t SIZE) {
    assert(SIZE > 0);
    assert(src.size() >= SIZE);

    if (SIZE == 1) {
        dst.add(src.top());
        src.pop();
        return;
    } else if (SIZE == 2) {
        move(src, buffer, dst, 1);
        move(src, dst, buffer, 1);
        move(buffer, dst, src, 1);
        return;
    }

    move(src, buffer, dst, SIZE - 1);
    dst.add(src.top());
    src.pop();
    move(buffer, dst, src, SIZE - 1);
}

struct HanoiTowers {
    Tower src;
    Tower buffer;
    Tower dest;

    HanoiTowers(const std::vector<int>& disks) {
        for (auto rit = disks.rbegin(); rit != disks.rend(); ++rit) {
            src.add(*rit);
        }
    }

    HanoiTowers(size_t N) {
        for (size_t i = N; i > 0; --i) {
            src.add(i);
        }
    }

    void moveDisks() {
        move(src, dest, buffer, src.size());
    }
};


TEST(TowersOfHanoiTest, NTest) {
    size_t N = 20;
    HanoiTowers ht(N);

    ht.moveDisks();

    ASSERT_EQ(0, ht.src.size());
    ASSERT_EQ(0, ht.buffer.size());
    ASSERT_EQ(N, ht.dest.size());

    for (size_t i = 1; i <= N; ++i) {
        ASSERT_EQ(i, ht.dest.top());
        ht.dest.pop();
    }
}

TEST(TowersOfHanoiTest, SmokeTest) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    HanoiTowers ht(input);

    ht.moveDisks();

    ASSERT_EQ(0, ht.src.size());
    ASSERT_EQ(0,ht.buffer.size());
    ASSERT_EQ(input.size(), ht.dest.size());

    for (size_t i = 0 ; i < input.size(); ++i) {
        ASSERT_EQ(input[i], ht.dest.top());
        ht.dest.pop();
    }
}
