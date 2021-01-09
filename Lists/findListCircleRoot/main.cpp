#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Write code to partition a linked list around value x, such that all nodes less than
// x come before all nodes greater than or equal to x

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

void printList(Node* head, Node* root)
{
    Node* printNode = head;

    bool rootPassed = false;
    while (printNode) {
        std::cout << " " << printNode->data;
        if (printNode == root) {
            if (rootPassed) {
                break;
            } else {
                rootPassed = true;
            }
        }
        printNode = printNode->next;
    }

    std::cout << std::endl;
}

Node* findListCircleRoot(Node* head)
{
    Node* slow = head;
    Node* fast = head;
    while (fast) {
        if (fast && fast->next) {
            fast = fast->next->next;
        } else {
            return nullptr;
        }

        slow = slow->next;

        if (slow == fast) {
            break;
        }
    }

    if (!fast) {
        return nullptr;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

void deleteCirrucularList(Node* head, Node* root) {
    bool rootpassed = false;
    while (head) {
        if (head == root) {
            if (!rootpassed) {
                rootpassed = true;
                head = head->next;
                continue;
            } else {
                delete head;
                break;
            }
        }
        Node* next  = head->next;
        delete head;
        head = next;
    }
}



TEST(findListCircleRootTest, SmokeTest)
{
    Node* head = nullptr;
    head = new Node{.data = 5, .next = head};
    Node* tail = head;
    head = new Node{.data = 4, .next = head};
    head = new Node{.data = 7, .next = head};
    head = new Node{.data = 87, .next = head};
    Node* expectedRootNode = head;
    head = new Node{.data = 3, .next = head};
    head = new Node{.data = 90, .next = head};
    head = new Node{.data = 11, .next = head};
    tail->next = expectedRootNode;

    printList(head, expectedRootNode);
    Node* root = findListCircleRoot(head);

    ASSERT_EQ(expectedRootNode, root);
    deleteCirrucularList(head, root);
}
