// Copyright 2022 NNTU-CS
#include "alg.h"

#include <algorithm>
#include <cstdint>
#include <vector>

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (char c : remaining) {
        Node* child = new Node(c);
        node->children.push_back(child);
        std::vector<char> newRemaining;
        for (char rc : remaining) {
            if (rc != c) newRemaining.push_back(rc);
        }
        buildTree(child, newRemaining);
    }
}

void PMTree::deleteTree(Node* node) {
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

PMTree::PMTree(const std::vector<char>& chars) {
    root = new Node('\0');
    std::vector<char> sorted = chars;
    std::sort(sorted.begin(), sorted.end());
    buildTree(root, sorted);
}

PMTree::~PMTree() {
    deleteTree(root);
}

Node* PMTree::getRoot() const {
    return root;
}

static void dfs(Node* node, std::vector<char>& current,
                std::vector<std::vector<char>>& result) {
    if (node->value != '\0') current.push_back(node->value);
    if (node->children.empty()) {
        if (!current.empty()) result.push_back(current);
    } else {
        for (Node* child : node->children) {
            dfs(child, current, result);
        }
    }
    if (node->value != '\0') current.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    dfs(tree.getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(all.size())) return {};
    return all[num - 1];
}

static int64_t factorial(int n) {
    int64_t result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> available;
    for (Node* child : tree.getRoot()->children) {
        available.push_back(child->value);
    }
    std::sort(available.begin(), available.end());
    int n = static_cast<int>(available.size());
    int64_t total = factorial(n);
    if (num < 1 || num > static_cast<int>(total)) return {};

    std::vector<char> result;
    int idx = num - 1;
    int remaining = n;
    while (remaining > 0) {
        int64_t block = factorial(remaining - 1);
        int choice = static_cast<int>(idx / block);
        result.push_back(available[choice]);
        available.erase(available.begin() + choice);
        idx = idx % static_cast<int>(block);
        --remaining;
    }
    return result;
}
