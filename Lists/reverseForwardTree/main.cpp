#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Reverse forward tree

struct Node {
    int data;
    Node* next;
};

void deleteList(Node* head) {
    while (head) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
}


Node* initLists() {
    Node* head = nullptr;
    for (int i = 0; i < 10; ++i) {
        head = new Node{.data = i + 1, .next = head};
    }

    return head;
}

void compareList(Node* lhs, Node* rhs) {
    while (lhs && rhs) {
        ASSERT_EQ(lhs->data, rhs->data);
        lhs = lhs->next;
        rhs = rhs->next;
    }

    ASSERT_FALSE(lhs);
    ASSERT_FALSE(rhs);
}

void printList(Node* head) {
    if (head) {
        std::cout << head->data;
        head = head->next;
    }

    while (head) {
        std::cout << " " << head->data;
        head = head->next;
    }

    std::cout << std::endl;
}

Node* reverseTree(Node* head) {
    Node* rhead = head;
    if (!rhead) {
        return rhead;
    }

    Node* node = rhead->next;
    rhead->next = nullptr;
    while (node) {
        Node* next = node->next;
        node->next = rhead;
        rhead = node;
        node = next;
    }

    return rhead;
}

TEST(reverseForwardTreeTest, SmokeTest) {
    Node* head = nullptr;
    head = new Node{.data = 5, .next = head};
    head = new Node{.data = 4, .next = head};
    head = new Node{.data = 7, .next = head};
    head = new Node{.data = 5, .next = head};
    head = new Node{.data = 3, .next = head};
    head = new Node{.data = 11, .next = head};

    Node* expectedHead = nullptr;
    expectedHead = new Node{.data = 11, .next = expectedHead};
    expectedHead = new Node{.data = 3, .next = expectedHead};
    expectedHead = new Node{.data = 5, .next = expectedHead};
    expectedHead = new Node{.data = 7, .next = expectedHead};
    expectedHead = new Node{.data = 4, .next = expectedHead};
    expectedHead = new Node{.data = 5, .next = expectedHead};

    printList(head);
    head = reverseTree(head);
    printList(head);

    compareList(expectedHead, head);

    deleteList(head);
    deleteList(expectedHead);
}
