#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Write code to partition a linked list around value x, such that all nodes less than
// x come before all nodes greater than or equal to x

struct Node {
    int data;
    Node* next;
};

Node* partitionList(Node* head, int x)
{
    Node* greater = nullptr;
    while (head && head->data >= x) {
        Node* next = head->next;
        head->next = greater;
        greater = head;

        head = next;
    }

    if (!head) {
        return greater;
    }

    Node* node = head;
    while (node->next) {
        Node* next = node->next;
        if (next->data >= x) {
            Node* next_next = next->next;
            next->next = greater;
            greater = next;
            node->next = next_next;
            continue;
        }

        node = node->next;
    }


    node->next = greater;

    return head;
}

void deleteList(Node* head) {
    while (head) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
}


Node* initLists()
{
    Node* head = nullptr;
    for (int i = 0; i < 10; ++i) {
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

TEST(partitionList, SmokeTest)
{
    Node* head = nullptr;
    head = new Node{.data = 5, .next = head};
    head = new Node{.data = 4, .next = head};
    head = new Node{.data = 7, .next = head};
    head = new Node{.data = 5, .next = head};
    head = new Node{.data = 3, .next = head};
    head = new Node{.data = 11, .next = head};

    Node* expectedHead = nullptr;
    expectedHead = new Node{.data = 11, .next = expectedHead};
    expectedHead = new Node{.data = 5, .next = expectedHead};
    expectedHead = new Node{.data = 7, .next = expectedHead};
    expectedHead = new Node{.data = 5, .next = expectedHead};
    expectedHead = new Node{.data = 4, .next = expectedHead};
    expectedHead = new Node{.data = 3, .next = expectedHead};

    printList(head);
    head = partitionList(head, 5);
    printList(head);

    ASSERT_TRUE(compareList(expectedHead, head));

    deleteList(head);
    deleteList(expectedHead);
}
