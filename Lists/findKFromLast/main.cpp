#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// find the kth to last element of singly linked list

struct Node {
    int data;
    Node* next;
};

Node* findKFromLast(Node* head, size_t k)
{
    if (k == 0) {
        return nullptr; // considering elements starting from 1
    }

    Node* ptr = head;
    size_t i = 1;
    while (i++ < k && ptr) {
        ptr = ptr->next;
    }

    if (!ptr) {
        return nullptr; // list has less than k elements
    }

    Node* res = head;
    ptr = ptr->next;
    while (ptr) {
        ptr = ptr->next;
        res = res->next;
    }

    return res;
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
TEST(FindKFromLastTest, SecondElem)
{
    Node* head = initLists();

    Node* kth = findKFromLast(head, 2);
    ASSERT_EQ(2, kth->data);
    deleteList(head);
}

TEST(FindKFromLastTest, TenElem)
{
    Node* head = initLists();

    Node* kth = findKFromLast(head, 10);
    ASSERT_EQ(10, kth->data);
    deleteList(head);
}

TEST(FindKFromLastTest, invalidInput)
{
    Node* head = initLists();

    ASSERT_EQ(nullptr, findKFromLast(head, 11));
    ASSERT_EQ(nullptr, findKFromLast(head, 0));
    deleteList(head);
}
