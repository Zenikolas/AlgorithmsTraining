#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Implement a queue

struct Node {
    int data;
    int min;
    Node* next;
};

class MinStack {
    Node* m_head = nullptr;
public:
    void push(int data) {
        int min = data;
        if (m_head) {
            min = std::min(min, m_head->min);
        }
        m_head = new Node{.data = data, .min = min, .next = m_head};
    }

    int top() const {
        return m_head ? m_head->data : 0;
    }

    int min() const {
        return m_head ? m_head->min: 0;
    }

    void pop() {
        if (!m_head) {
            return;
        }

        Node* tmp = m_head;
        m_head = m_head->next;
        delete tmp;
    }

    bool empty() const {return !m_head; }

    ~MinStack() {
        while (m_head) {
            Node* toRemove = m_head;
            m_head = m_head->next;
            delete toRemove;
        }
    }

};


TEST(MinStackTest, EmptyTest) {
    MinStack stack;

    ASSERT_TRUE(stack.empty());

    stack.push(40);

    ASSERT_FALSE(stack.empty());

    ASSERT_EQ(40, stack.top());

    stack.pop();

    ASSERT_TRUE(stack.empty());
}

TEST(MinStackTest, SmokeTest) {
    MinStack stack;

    stack.push(40);
    ASSERT_EQ(40, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.push(5);
    ASSERT_EQ(5, stack.top());
    ASSERT_EQ(5, stack.min());

    stack.pop();
    ASSERT_EQ(40, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.push(60);
    ASSERT_EQ(60, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.push(80);
    ASSERT_EQ(80, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.push(30);
    ASSERT_EQ(30, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.push(100);
    ASSERT_EQ(100, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.push(120);
    ASSERT_EQ(120, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.push(40);
    ASSERT_EQ(40, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.pop();
    ASSERT_EQ(120, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.pop();
    ASSERT_EQ(100, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.pop();
    ASSERT_EQ(30, stack.top());
    ASSERT_EQ(30, stack.min());

    stack.pop();
    ASSERT_EQ(80, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.pop();
    ASSERT_EQ(60, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.pop();
    ASSERT_EQ(40, stack.top());
    ASSERT_EQ(40, stack.min());

    stack.pop();
    ASSERT_TRUE(stack.empty());
}
