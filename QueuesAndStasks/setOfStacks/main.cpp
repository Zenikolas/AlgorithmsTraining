#include <string>
#include <unordered_set>
#include <memory>

#include <gtest/gtest.h>

// Implement set of stacks

struct Node {
    int data;
    std::shared_ptr<Node> above = nullptr;
    std::shared_ptr<Node> below = nullptr;
};

class Stack {
    std::shared_ptr<Node> m_top = nullptr;
    std::shared_ptr<Node> m_bottom = nullptr;
    size_t m_size = 0;

    void join(std::shared_ptr<Node>& above, std::shared_ptr<Node>& below) {
        if (above) above->below = below;
        if (below) below->above = above;
    }
public:
    void push(int data) {
        ++m_size;
        auto newNode = std::make_shared<Node>();
        newNode->data = data;
        if (m_size == 1) {
            m_top = m_bottom = newNode;
            return;
        }

        join(newNode, m_top);
        m_top = newNode;
    }

    int top() const {
        return m_size > 0 ? m_top->data : 0;
    }

    int pop() {
        if (m_size == 0) {
            return 0;
        }
        --m_size;
        int ret = m_top->data;
        m_top = m_top->below;
        if (m_top) {
            m_top->above = nullptr;
        }

        return ret;
    }

    int popBottom() {
        if (m_size == 0) {
            return 0;
        }

        --m_size;
        int ret = m_bottom->data;
        m_bottom = m_bottom->above;
        if (m_bottom) {
            m_bottom->below = nullptr;
        }

        return ret;
    }

    size_t size() const {return m_size; }

};

class SetOfStacks {
    std::vector<Stack> m_stacks;
    size_t m_threshold;

    int shift(size_t idx) {
        if (idx >= m_stacks.size()) {
            std::runtime_error("Invalid stack index");
        }

        int ret = m_stacks[idx].popBottom();
        for (size_t i = idx + 1; i < m_stacks.size(); ++i) {
            m_stacks[i - 1].push(m_stacks[i].popBottom());
        }

        if (m_stacks.back().size() == 0) {
            m_stacks.pop_back();
        }

        return ret;
    }
public:
    SetOfStacks(size_t threshold) : m_threshold(threshold) {}

    void push(int data) {
        if (m_stacks.empty() || m_stacks.back().size() == m_threshold) {
            m_stacks.emplace_back();
        }

        m_stacks.back().push(data);
    }

    int top() const {
        return m_stacks.empty() ? 0 : m_stacks.back().top();
    }
    size_t size () const {
        size_t finalSize = 0;

        for (auto& stack: m_stacks) {
            finalSize += stack.size();
        }

        return finalSize;
    }

    int pop() {
        if (m_stacks.empty()) {
            throw std::runtime_error("Trying to pop from an empty stack");
        }

        int ret = m_stacks.back().pop();
        if (m_stacks.back().size() == 0) {
            m_stacks.pop_back();
        }

        return ret;
    }

    int popAt(size_t idx) {
        if (idx >= m_stacks.size()) {
            throw std::runtime_error("Trying to pop from an invalid stack index");
        }

        int ret = m_stacks[idx].pop();
        if (idx == m_stacks.size() - 1) {
            if (m_stacks[idx].size() == 0) {
                m_stacks.pop_back();
            }

            return ret;
        }

        m_stacks[idx].push(shift(idx + 1));

        return ret;
    }
};


TEST(setOfStacksTest, SmokeTest) {
    SetOfStacks ss(3);
    ASSERT_EQ(0, ss.size());
    ss.push(10);
    ASSERT_EQ(1, ss.size());
    ss.push(20);
    ss.push(30);
    ss.push(40);
    ss.push(50);
    ASSERT_EQ(5, ss.size());
    ASSERT_EQ(50, ss.top());
    ss.pop();
    ASSERT_EQ(4, ss.size());
    ASSERT_EQ(40, ss.top());
    ss.pop();
    ASSERT_EQ(30, ss.top());
    ss.pop();
    ASSERT_EQ(20, ss.top());
    ss.pop();
    ASSERT_EQ(10, ss.top());
    ss.pop();
    ASSERT_EQ(0, ss.size());
}

TEST(setOfStacksTest, PopAtTest) {
    SetOfStacks ss(3);
    ss.push(10);
    ss.push(20);
    ss.push(30);
    ss.push(40);
    ss.push(50);

    ASSERT_EQ(30, ss.popAt(0));
    ASSERT_EQ(40, ss.popAt(0));
    ASSERT_EQ(50, ss.popAt(0));
    ASSERT_EQ(20, ss.pop());
    ASSERT_EQ(10, ss.pop());
    ASSERT_EQ(0, ss.size());
}
