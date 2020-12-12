#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// check of candidate string is rotated from original one

struct Node {
    int data;
    Node* next;
};

void deleteDuplicationsWithExtraMemory(Node* head)
{
    std::unordered_set<decltype(head->data)> elements{head->data};
    Node* current = head;
    while (current->next) {
        if (elements.find(current->next->data) != elements.end()) {
            Node* tmp = current->next;
            current->next = current->next->next;
            delete tmp;
        } else {
            elements.insert(current->next->data);
            current = current->next;
        }
    }
}

void deleteDuplications(Node* head)
{
    Node* current = head;
    while (current) {
        Node* runner = current;
        while (runner->next) {
            if (current->data == runner->next->data) {
                Node* tmp = runner->next;
                runner->next = runner->next->next;
                delete tmp;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
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

void deleteList(Node* head) {
    while (head) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
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


std::tuple<Node*, Node*> initLists()
{
    Node* head = nullptr;
    for (int i = 0; i < 10; ++i) {
        int value = i % 2 == 0 ? 2 : i;
        head = new Node{.data = value, .next = head};
    }

    Node* expectedHead = nullptr;
    expectedHead = new Node{.data = 1, .next = expectedHead};
    expectedHead = new Node{.data = 3, .next = expectedHead};
    expectedHead = new Node{.data = 5, .next = expectedHead};
    expectedHead = new Node{.data = 7, .next = expectedHead};
    expectedHead = new Node{.data = 2, .next = expectedHead};
    expectedHead = new Node{.data = 9, .next = expectedHead};

    return {head, expectedHead};
}
TEST(DeleteDuplicationsTest, SmokeTestWithBuffer)
{
    auto[head, expectedHead] = initLists();

    printList(head);
    deleteDuplicationsWithExtraMemory(head);
    printList(head);
    printList(expectedHead);
    ASSERT_TRUE(compareList(head, expectedHead));
    deleteList(head);
    deleteList(expectedHead);
}

TEST(DeleteDuplicationsTest, SmokeTest)
{
    auto[head, expectedHead] = initLists();

    printList(head);
    deleteDuplications(head);
    printList(head);
    printList(expectedHead);
    ASSERT_TRUE(compareList(head, expectedHead));
    deleteList(head);
    deleteList(expectedHead);
}

