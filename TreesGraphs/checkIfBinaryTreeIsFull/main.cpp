#include <gtest/gtest.h>

#include <memory>

struct Node {
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    const std::vector<Node*>& getChildes() const {
        return std::vector<Node*> {left.get(), right.get()};
    }
};

struct CompareResult {
    size_t min;
    size_t max;
};

CompareResult getDepths(Node* root) {
    if (!root->left && !root->right) {
        return CompareResult{.min= 0, .max = 0};
    }

    CompareResult leftDepths = getDepths(root->left.get());
    CompareResult rightDepths = getDepths(root->right.get());
    size_t min = std::min(leftDepths.min, rightDepths.min) + 1;
    size_t max = std::max(leftDepths.max, rightDepths.max) + 1;

    return CompareResult{.min = min, .max = max};
}

bool checkIfTreeIsFull(Node* root) {
    CompareResult result = getDepths(root);

    return result.max - result.min <= 1;
}

void TreeUtil::print(std::ostream& os, const Node* root) {
    if (!root) {
        throw std::runtime_error("NodeError::INVALID_TREE_ROOT");
    }

    struct TreeNode {
        const Node* node;
        std::string intend;
        bool last;
    };

    std::stack<TreeNode> stack;
    stack.push({.node = root, .intend = "", .last = true});
    while (!stack.empty()) {
        TreeNode top = stack.top();
        stack.pop();

        assert(top.node && "must be not null");

        os << top.intend << "+ " << *top.node << "\n";
        auto& childs = top.node->getChildes();
        if (childs.empty()) {
            continue;
        }

        std::string intend;
        if (top.last) {
            intend = top.intend + "\t";
        } else {
            intend = top.intend + "|\t";
        }

        stack.push({.node = childs.back().get(), .intend = intend, .last = true});
        const size_t lastElemIndex = childs.size() - 1;
        const size_t preLastElemIndex = lastElemIndex - 1;
        for (size_t i = 0; i < lastElemIndex; ++i) {
            const Node* currentChild = childs[preLastElemIndex - i].get();
            stack.push({.node = currentChild, .intend = intend, .last =false});
        }
    }

    return NodeError::SUCCESS;
}

TEST(CheckIfBinaryTreeIsFullTest, GoodCase) {
    auto root = std::make_unique<Node>();
    root->left = std::make_unique<Node>();
    root->right = std::make_unique<Node>();

    auto left = root->left.get();
    auto right = root->right.get();

    left->left = std::make_unique<Node>();
    left->right = std::make_unique<Node>();

    right->left = std::make_unique<Node>();
    right->right = std::make_unique<Node>();

    left->left->left = std::make_unique<Node>();
    left->left->right = std::make_unique<Node>();

    ASSERT_TRUE(checkIfTreeIsFull(root.get()));
}

TEST(CheckIfBinaryTreeIsFullTest, BadCase) {
    auto root = std::make_unique<Node>();
    root->left = std::make_unique<Node>();
    root->right = std::make_unique<Node>();

    auto left = root->left.get();
    auto right = root->right.get();

    left->left = std::make_unique<Node>();
    left->right = std::make_unique<Node>();

    right->left = std::make_unique<Node>();
    right->right = std::make_unique<Node>();

    left->left->left = std::make_unique<Node>();
    left->left->right = std::make_unique<Node>();

    left->left->right->left = std::make_unique<Node>();
    left->left->right->right = std::make_unique<Node>();

    ASSERT_FALSE(checkIfTreeIsFull(root.get()));
}
