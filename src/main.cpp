// Copyright 2022 NNTU-CS
#include "tree.h"

#include <ctime>
#include <iostream>
#include <vector>

int main() {
    std::srand(std::time(nullptr));

    std::vector<char> input = {'A', 'B', 'C'};
    PMTree tree(input);

    std::vector<std::vector<char>> all = getAllPerms(tree);
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all[i].size(); ++j) {
            std::cout << all[i][j];
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    std::vector<char> p1 = getPerm1(tree, 2);
    for (size_t i = 0; i < p1.size(); ++i) {
        std::cout << p1[i];
    }
    std::cout << std::endl;

    std::vector<char> p2 = getPerm2(tree, 3);
    for (size_t i = 0; i < p2.size(); ++i) {
        std::cout << p2[i];
    }
    std::cout << std::endl;

    int sizes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int k = 0; k < 10; ++k) {
        int n = sizes[k];
        std::vector<char> chars;
        for (int i = 0; i < n; ++i) {
            chars.push_back('a' + i);
        }
        PMTree bigTree(chars);

        std::clock_t start1 = std::clock();
        std::vector<std::vector<char>> perms = getAllPerms(bigTree);
        std::clock_t end1 = std::clock();
        double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;

        std::clock_t start2 = std::clock();
        std::vector<char> perm2 = getPerm2(bigTree, 1);
        std::clock_t end2 = std::clock();
        double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC;

        std::cout << n << " " << time1 << " " << time2 << std::endl;
    }

    return 0;
}
