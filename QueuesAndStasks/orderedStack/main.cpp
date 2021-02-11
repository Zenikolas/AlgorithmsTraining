#include <string>
#include <stack>

#include <gtest/gtest.h>
// Write a program to sort a stack in ascending order. You may use additional stack to
// hold items, but you may not copy the elements into any other data structure such as
// array. The stack supports the following operations push, pop, front, empty.

class Stack {
    std::stack<int> m_buffer;
public:
    void push(int data) {
        std::stack<int> tmp;

        while (!m_buffer.empty() && data < m_buffer.top()) {
            tmp.push(m_buffer.top());
            m_buffer.pop();
        }

        m_buffer.push(data);
        while (!tmp.empty()) {
            m_buffer.push(tmp.top());
            tmp.pop();
        }
    }

    int top() const {
        return m_buffer.top();
    }

    void pop() {
        m_buffer.pop();
    }

    bool empty() const { return m_buffer.empty(); }
};


TEST(OrderedStackTest, NullTest) {
    Stack st;

    ASSERT_TRUE(st.empty());
}

TEST(OrderedStackTest, PushPopTest) {
    Stack st;

    st.push(1);
    ASSERT_FALSE(st.empty());
    ASSERT_EQ(1, st.top());

    st.pop();
    ASSERT_TRUE(st.empty());
}

TEST(OrderedStackTest, AscendingTest) {
    Stack st;

    st.push(1);
    st.push(2);
    st.push(10);
    st.push(5);
    st.push(8);
    st.push(4);

    ASSERT_EQ(10, st.top());
    st.pop();

    ASSERT_EQ(8, st.top());
    st.pop();

    ASSERT_EQ(5, st.top());
    st.pop();

    ASSERT_EQ(4, st.top());
    st.pop();

    ASSERT_EQ(2, st.top());
    st.pop();

    ASSERT_EQ(1, st.top());
    st.pop();
}
