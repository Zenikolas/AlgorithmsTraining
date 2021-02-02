#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Implement a stack

struct Node {
    int data;
    Node* next;
};

class Stack {
    Node* m_head = nullptr;
    size_t m_size = 0;
public:
    void push(int data) {
        ++m_size;
        m_head = new Node{.data = data, .next = m_head};
    }

    int top() const {
        return m_head->data;
    }

    void pop() {
        --m_size;
        Node* toRemove = m_head;
        m_head = m_head->next;
        delete toRemove;
    }

    size_t size() const {return m_size; }

    ~Stack() {
        while (m_head) {
            Node* toRemove = m_head;
            m_head = m_head->next;
            delete toRemove;
        }
    }

};


TEST(queueTest, SmokeTest) {
    Stack stack;
    ASSERT_EQ(0, stack.size());
    stack.push(10);
    ASSERT_EQ(1, stack.size());
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    ASSERT_EQ(5, stack.size());
    ASSERT_EQ(50, stack.top());
    stack.pop();
    ASSERT_EQ(4, stack.size());
    ASSERT_EQ(40, stack.top());
    stack.pop();
    ASSERT_EQ(30, stack.top());
    stack.pop();
    ASSERT_EQ(20, stack.top());
    stack.pop();
    ASSERT_EQ(10, stack.top());
    stack.pop();
    ASSERT_EQ(0, stack.size());
}
