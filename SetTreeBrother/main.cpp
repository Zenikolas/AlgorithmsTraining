#include <iostream>

struct Node {
    Node* parent;
    Node* left;
    Node* right;
    Node* brother;
    int a;
};



void visitTree(Node*& root)
{
    if (!root) {
        return;
    }

    std::cout << "Brother: " << root->brother << std::endl;
    if(root->left) {
        visitTree(root->left);
    }


    if(root->right) {
        visitTree(root->right);
    }
}

void ToBrotherTree(Node*& parent)
{
    if (!parent) {
        return;
    }

    if(parent->left) {
        parent->left->brother = parent->right;
        ToBrotherTree(parent->left);
    }


    if(parent->right) {
        if (parent->brother) {
            parent->right->brother = parent->brother->left;
        }
        ToBrotherTree(parent->right);
    }
}

void createTree(Node*& root, int left)
{
    root = new Node();
    std::cout << "Node: " << root << std::endl;
    root->brother = nullptr;
    if (left <= 0) {
        return;
    }

    createTree(root->left, left - 1);
    createTree(root->right, left - 1);
}

int main()
{
    Node* root = nullptr;

    createTree(root, 2);

    std::cout << "==============================" << std::endl;

    ToBrotherTree(root);

    visitTree(root);
    return 0;
}