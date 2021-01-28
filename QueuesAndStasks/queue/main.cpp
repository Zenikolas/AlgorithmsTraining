#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Reverse forward tree

struct Node {
    int data;
    Node* next;
};

class Queue {
    Node* m_front = nullptr;
    Node* m_back = nullptr;
    size_t m_size = 0;
public:
    void push_back(int data) {
        ++m_size;
        if (!m_front) {
            assert(!m_back);
            m_front = m_back = new Node{.data = data, .next = nullptr};
            return;
        }

        assert(!m_back->next);
        m_back->next = new Node{.data = data, .next = nullptr};
        m_back = m_back->next;
    }

    int front() const {
        return m_front->data;
    }

    void pop() {
        assert(m_front);
        --m_size;
        Node* toRemove = m_front;
        m_front = m_front->next;
        delete toRemove;
    }

    size_t size() const {return m_size; }

    ~Queue() {
        while (m_front) {
            Node* toRemove = m_front;
            m_front = m_front->next;
            delete toRemove;
        }
    }

};


TEST(queueTest, SmokeTest) {
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
