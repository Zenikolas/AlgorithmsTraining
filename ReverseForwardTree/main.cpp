#include <iostream>
#include <stack>

struct Node {
    Node *next;
};

Node *contructList(size_t size) {
    Node *head = new Node();
    Node *root = head;
    while (size > 0) {
        head->next = new Node();
        head = head->next;
        --size;
    }

    return root;
}

void visitList(Node *node) {
    size_t size = 0;
    while (node) {
        std::cout << "Node[" << size++ << "]: " << node << std::endl;
        node = node->next;
    }
    std::cout << "====================" << std::endl;
}

void destroyList(Node *root) {
    std::stack<Node *> nodeList;
    Node *head = root;
    while (head) {
        nodeList.push(head);
        head = head->next;
    }

    while (!nodeList.empty()) {
        Node *node = nodeList.top();
        nodeList.pop();
        if (node) {
            delete node;
        }
    }
}

void swap(Node *&lhs, Node *&rhs) {
    lhs = (Node *)((uintptr_t)lhs ^ (uintptr_t)rhs);
    rhs = (Node *)((uintptr_t)lhs ^ (uintptr_t)rhs);
    lhs = (Node *)((uintptr_t)lhs ^ (uintptr_t)rhs);
}

Node *reverseListSwapVersion(Node *root) {
    if (!root || !root->next) {
        return root;
    }

    Node *prev = nullptr;
    Node *head = root;

    while (head) {
        swap(head->next, prev);
        swap(head, prev);
    }

    return prev;
}

int main() {
    Node *root = contructList(2);

    visitList(root);
    root = reverseListSwapVersion(root);
    visitList(root);

    destroyList(root);
    return 0;
}