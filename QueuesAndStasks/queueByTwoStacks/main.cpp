#include <stack>

#include <gtest/gtest.h>
// Implement a queue using two stacks

class Queue {
    std::stack<int> m_front;
    std::stack<int> m_back;
public:
    void push_back(int data) {
        m_back.push(data);
    }

    int front() {
        if (m_front.empty()) {
            if (m_back.empty()) {
                throw std::runtime_error("Trying to get value from empty queue");
            }

            while (!m_back.empty()) {
                m_front.emplace(m_back.top());
                m_back.pop();
            }
        }

        return m_front.top();
    }

    void pop() {
        if (m_front.empty()) {
            if (m_back.empty()) {
                throw std::runtime_error("Trying to pop value from empty queue");
            }

            while (!m_back.empty()) {
                m_front.emplace(m_back.top());
                m_back.pop();
            }
        }

        m_front.pop();
    }

    size_t size() const {return m_front.size() + m_back.size(); }
};


TEST(queueTwoStacksTest, SmokeTest) {
    Queue qq;
    ASSERT_EQ(0, qq.size());
    qq.push_back(10);
    ASSERT_EQ(1, qq.size());
    qq.push_back(20);
    qq.push_back(30);
    qq.push_back(40);
    qq.push_back(50);
    ASSERT_EQ(5, qq.size());
    ASSERT_EQ(10, qq.front());
    qq.pop();
    ASSERT_EQ(4, qq.size());
    ASSERT_EQ(20, qq.front());
    qq.pop();
    ASSERT_EQ(30, qq.front());
    qq.pop();
    ASSERT_EQ(40, qq.front());
    qq.pop();
    ASSERT_EQ(50, qq.front());
    qq.pop();
    ASSERT_EQ(0, qq.size());
}
