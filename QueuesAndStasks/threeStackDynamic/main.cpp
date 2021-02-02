#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
#include <langinfo.h>
// Describe how to use single array to implement three stasks

template <class T>
class MultipleStacks {
    std::vector<long long int> m_stacks;
    std::vector<T> m_buffer;
public:
    MultipleStacks(long long int numberOfStacks) : m_stacks(numberOfStacks) {
        for (long long int i = 0; i < numberOfStacks; ++i) {
            m_stacks[i] = i - numberOfStacks;
        }
    }

    void push (size_t stackIdx, const T& value) {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        m_stacks[stackIdx] += m_stacks.size();
        if (m_stacks[stackIdx] >= m_buffer.size()) {
            m_buffer.resize(m_stacks[stackIdx] + 1);
        }
        m_buffer[m_stacks[stackIdx]] = value;
    }

    T top(size_t stackIdx) const {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        if (m_stacks[stackIdx] < 0) {
            throw std::runtime_error("Stack for specified id is empty");
        }

        assert(m_stacks[stackIdx] < m_buffer.size());

        return m_buffer[m_stacks[stackIdx]];
    }

    void pop(size_t stackIdx) {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        m_buffer[m_stacks[stackIdx]] = T{};
        m_stacks[stackIdx] -= m_stacks.size();
    }
};


TEST(MultipleStacksTest, SmokeTest) {
    MultipleStacks<int> multiStacks(3);

    multiStacks.push(0, 100);
    multiStacks.push(1, 200);
    multiStacks.push(2, 300);

    multiStacks.push(2, 301);
    multiStacks.push(1, 201);
    multiStacks.push(0, 101);

    ASSERT_EQ(101, multiStacks.top(0));
    ASSERT_EQ(201, multiStacks.top(1));
    ASSERT_EQ(301, multiStacks.top(2));

    multiStacks.pop(0);
    multiStacks.pop(1);
    multiStacks.pop(2);

    ASSERT_EQ(100, multiStacks.top(0));
    ASSERT_EQ(200, multiStacks.top(1));
    ASSERT_EQ(300, multiStacks.top(2));

    multiStacks.pop(0);
    multiStacks.pop(1);
    multiStacks.pop(2);
}
