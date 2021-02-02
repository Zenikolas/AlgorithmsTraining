#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
#include <langinfo.h>
// Describe how to use single array to implement three stasks

template <class T>
class MultipleStacksFixed {
    struct StackInfo {
        size_t start;
        size_t size;
        size_t capacity;

        StackInfo(size_t _start, size_t capacity) : start(_start), size(0), capacity(capacity) {}

        bool isFull() const {
            return size == capacity;
        }

        bool isEmpty() const {
            return size == 0;
        }
    };

    std::vector<StackInfo> m_stacks;
    std::vector<T> m_buffer;

    bool shift(size_t idx) {
        idx %= m_stacks.size();
        StackInfo& stack = m_stacks[idx];
        if (stack.isFull()) {
            bool ret = shift(idx + 1);
            if (!ret) {
                return ret;
            }

            ++stack.capacity;
        }

        for (size_t i = 0; i < stack.size; ++i) {
            size_t current = (stack.start + stack.size - 1 - i) % m_buffer.size();
            size_t next = (current + 1) % m_buffer.size();
            m_buffer[next] = m_buffer[current];
        }

        m_buffer[stack.start] = T{};
        stack.start = (stack.start + 1) % m_buffer.size();
        --stack.capacity;
        return true;
    }
public:
    MultipleStacksFixed(long long int numberOfStacks, size_t bufferSize = 1000)
    : m_buffer(bufferSize) {
        m_stacks.reserve(numberOfStacks);
        size_t portion = m_buffer.size() / numberOfStacks;
        for (size_t i = 0; i < numberOfStacks; ++i) {
            size_t start = i * portion;
            size_t capacity = portion;
            if (i == numberOfStacks - 1) {
                capacity += m_buffer.size() % numberOfStacks;
            }
            m_stacks.emplace_back(start, capacity);
        }
    }

    void push (size_t stackIdx, const T& value) {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        StackInfo& stack = m_stacks[stackIdx];
        if (stack.isFull()) {
            bool ret = shift(stackIdx + 1);
            if (!ret) {
                throw std::runtime_error("No more capacity!");
            }

            ++stack.capacity;
        }

        size_t pos = (stack.start + stack.size) % m_buffer.size();
        ++stack.size;
        m_buffer[pos] = value;
    }

    T top(size_t stackIdx) const {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        const StackInfo& stack = m_stacks[stackIdx];
        size_t pos = (stack.start + stack.size - 1) % m_buffer.size();
        return m_buffer[pos];
    }

    void pop(size_t stackIdx) {
        if (stackIdx >= m_stacks.size()) {
            throw std::runtime_error("Wrong stack idx");
        }

        StackInfo& stack = m_stacks[stackIdx];
        size_t pos = (stack.start + stack.size - 1) % m_buffer.size();
        m_buffer[pos] = T{};
        --stack.size;
    }

    bool isFull() const {
        for (auto& stack: m_stacks) {
            if (!stack.isFull()) {
                return false;
            }
        }

        return true;
    }

    bool isEmpty() const {
        for (auto& stack: m_stacks) {
            if (!stack.isEmpty()) {
                return false;
            }
        }

        return true;
    }
};


TEST(MultipleStacksFixedTest, SmokeTest) {
    MultipleStacksFixed<int> multiStacks(3, 6);

    ASSERT_TRUE(multiStacks.isEmpty());

    multiStacks.push(0, 100);
    multiStacks.push(1, 200);
    multiStacks.push(2, 300);

    multiStacks.push(2, 301);
    multiStacks.push(1, 201);
    multiStacks.push(0, 101);

    ASSERT_TRUE(multiStacks.isFull());

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

    ASSERT_TRUE(multiStacks.isEmpty());
}

TEST(MultipleStacksFixedTest, ShiftTest) {
    MultipleStacksFixed<int> multiStacks(3, 8);

    ASSERT_TRUE(multiStacks.isEmpty());

    multiStacks.push(0, 100);
    multiStacks.push(1, 200);
    multiStacks.push(2, 300);

    multiStacks.push(2, 301);
    multiStacks.push(1, 201);
    multiStacks.push(0, 101);

    ASSERT_FALSE(multiStacks.isFull());

    multiStacks.push(0, 102);
    multiStacks.push(1, 202);

    ASSERT_TRUE(multiStacks.isFull());

    ASSERT_EQ(102, multiStacks.top(0));
    ASSERT_EQ(202, multiStacks.top(1));
    ASSERT_EQ(301, multiStacks.top(2));

    multiStacks.pop(0);
    multiStacks.pop(1);
    multiStacks.pop(2);

    ASSERT_EQ(101, multiStacks.top(0));
    ASSERT_EQ(201, multiStacks.top(1));
    ASSERT_EQ(300, multiStacks.top(2));

    multiStacks.pop(0);
    multiStacks.pop(1);
    multiStacks.pop(2);

    ASSERT_EQ(100, multiStacks.top(0));
    ASSERT_EQ(200, multiStacks.top(1));

    multiStacks.pop(0);
    multiStacks.pop(1);

    ASSERT_TRUE(multiStacks.isEmpty());
}
