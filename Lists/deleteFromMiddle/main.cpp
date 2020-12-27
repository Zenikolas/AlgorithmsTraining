#include <string>

#include <gtest/gtest.h>
// Implement an algorithm to delete a node in the middle of singly linked list, given
// only access to that node

struct Node {
    int data;
    Node* next;
};

void deleteFromMiddle(Node* node)
{
    if (!node || !node->next) {
        return;
    }

    Node* next = node->next;
    node->data = next->data;
    node->next = next->next;
    delete next;
}

void deleteList(Node* head) {
    while (head) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
}


Node* initLists(size_t N = 10)
{
    Node* head = nullptr;
    for (int i = 0; i < N; ++i) {
        head = new Node{.data = i + 1, .next = head};
    }

    return head;
}

bool compareList(Node* lhs, Node* rhs) {
    while (lhs && rhs) {
        if (lhs->data != rhs->data) {
            return false;
        }
        lhs = lhs->next;
        rhs = rhs->next;
    }

    if (lhs || rhs) {
        return false;
    }

    return true;
}

void printList(Node* head)
{
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

TEST(deleteFromMiddle, SmokeTest)
{
    Node* head = initLists();
    Node* node = head;
    for (int i = 0; i < 3; ++i) { node = node->next; }

    printList(head);
    ASSERT_EQ(7, node->data);
    deleteFromMiddle(node);
    printList(head);

    ASSERT_EQ(6, node->data);

    deleteList(head);
}

