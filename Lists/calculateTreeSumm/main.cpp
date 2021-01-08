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

Node* calculateTreeSumm(Node* lhs, Node* rhs) {
    Node* rlhead = reverseTree(lhs);
    Node* rrhead = reverseTree(rhs);
    Node* result = nullptr;

    bool isOverflow = false;
    while (rlhead && rrhead) {
        int value = rlhead->data + rrhead->data;
        if (isOverflow) {
            ++value;
        }

        isOverflow = value >= 10;
        if (isOverflow) {
            value %= 10;
        }
        result = new Node{.data = value, .next = result};

        rlhead = rlhead->next;
        rrhead = rrhead->next;
    }

    while (rlhead) {
        int value = rlhead->data;
        if (isOverflow) {
            ++value;
        }

        isOverflow = value >= 10;
        if (isOverflow) {
            value %= 10;
        }
        result = new Node{.data = value, .next = result};
        rlhead = rlhead->next;
    }

    while (rrhead) {
        int value = rrhead->data;
        if (isOverflow) {
            ++value;
        }

        isOverflow = value >= 10;
        if (isOverflow) {
            value %= 10;
        }
        result = new Node{.data = value, .next = result};
        rrhead = rrhead->next;
    }

    if (isOverflow) {
        result = new Node{.data = 1, .next = result};
    }

    return result;
}

TEST(calculateTreeSummTest, SmokeTest) {
    Node* lhs = nullptr;
    lhs = new Node{.data = 5, .next = lhs};
    lhs = new Node{.data = 4, .next = lhs};
    lhs = new Node{.data = 7, .next = lhs};
    lhs = new Node{.data = 5, .next = lhs};
    lhs = new Node{.data = 3, .next = lhs};
    lhs = new Node{.data = 2, .next = lhs};

    Node* rhs = nullptr;
    rhs = new Node{.data = 5, .next = rhs};
    rhs = new Node{.data = 8, .next = rhs};
    rhs = new Node{.data = 7, .next = rhs};

    Node* expectedSumm = nullptr;
    expectedSumm = new Node{.data = 0, .next = expectedSumm};
    expectedSumm = new Node{.data = 3, .next = expectedSumm};
    expectedSumm = new Node{.data = 5, .next = expectedSumm};
    expectedSumm = new Node{.data = 6, .next = expectedSumm};
    expectedSumm = new Node{.data = 3, .next = expectedSumm};
    expectedSumm = new Node{.data = 2, .next = expectedSumm};

    printList(lhs);
    printList(rhs);
    Node* summ = calculateTreeSumm(lhs, rhs);
    printList(summ);


    compareList(expectedSumm, summ);

    deleteList(lhs);
    deleteList(rhs);
    deleteList(summ);
    deleteList(expectedSumm);
}


TEST(calculateTreeSummTest, CarryTest) {
    Node* lhs = nullptr;
    lhs = new Node{.data = 5, .next = lhs};
    lhs = new Node{.data = 4, .next = lhs};

    Node* rhs = nullptr;
    rhs = new Node{.data = 8, .next = rhs};
    rhs = new Node{.data = 7, .next = rhs};

    Node* expectedSumm = nullptr;
    expectedSumm = new Node{.data = 3, .next = expectedSumm};
    expectedSumm = new Node{.data = 2, .next = expectedSumm};
    expectedSumm = new Node{.data = 1, .next = expectedSumm};

    printList(lhs);
    printList(rhs);
    Node* summ = calculateTreeSumm(lhs, rhs);
    printList(summ);


    compareList(expectedSumm, summ);

    deleteList(lhs);
    deleteList(rhs);
    deleteList(summ);
    deleteList(expectedSumm);
}
