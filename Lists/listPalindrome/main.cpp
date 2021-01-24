#include <string>
#include <unordered_set>

#include <gtest/gtest.h>
// Check of list elements make a palindrome

struct Node {
    char data;
    Node* next;
};


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

void deleteList(Node* head) {
    while (head) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
}

bool isPalindrome(Node* head) {
    bool isEven = false;
    Node* first = head;
    Node* second = head;
    Node* reversed = nullptr;

    while(second->next) {
        second = second->next;
        if (!second->next) {
            isEven = true;
        } else {
            second = second->next;
        }

        reversed = new Node{first->data, reversed};
        first = first->next;
    }

    if (!reversed) {
        return true;
    }

    if (!isEven) {
        first = first->next;
    }

    while (first) {
        if (first->data != reversed->data) {
            return false;
        }

        first = first->next;
        reversed = reversed->next;
    }

    return !reversed;
}

TEST(listPalindromeTest, AbbaTest)
{
    Node* head = nullptr;
    head = new Node{.data = 'A', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'A', .next = head};

    printList(head);
    ASSERT_TRUE(isPalindrome(head));

    deleteList(head);
}

TEST(listPalindromeTest, AbcbaTest)
{
    Node* head = nullptr;
    head = new Node{.data = 'A', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'A', .next = head};

    printList(head);
    ASSERT_TRUE(isPalindrome(head));

    deleteList(head);
}

TEST(listPalindromeTest, MoreComplexTest)
{
    Node* head = nullptr;
    head = new Node{.data = 'A', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'A', .next = head};

    printList(head);
    ASSERT_TRUE(isPalindrome(head));

    deleteList(head);
}

TEST(listPalindromeTest, FailedTest)
{
    Node* head = nullptr;
    head = new Node{.data = 'A', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'D', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'C', .next = head};
    head = new Node{.data = 'B', .next = head};
    head = new Node{.data = 'A', .next = head};

    printList(head);
    ASSERT_FALSE(isPalindrome(head));

    deleteList(head);
}
