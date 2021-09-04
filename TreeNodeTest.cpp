#include <iostream>
#include <vector>

#include "tree/TreeNode.h"

int main(void) {
    std::vector<int> v{1, 2, 3, 4, 5};

    Verifier<int> verifier = [](int& value) { return value > 0; };

    BaseBinaryTree<int> tree(v, verifier);

    std::cout << tree.GetRoot() << std::endl;

    return 0;
}