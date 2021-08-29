#include <cmath>
#include <iostream>
#include <vector>

#include "list/ListNode.h"
#include "list/ListNodeStream.h"

struct Apple {
    int weight;

    Apple() : Apple(0) {}
    Apple(int weight) : weight(weight) {}
};

int main(void) {
    ListNode n1;
    std::cout << n1.val << std::endl;

    ListNode n2(1);
    std::cout << n2.val << std::endl;

    ListNode n3(2, &n1);
    std::cout << n2.val << std::endl;

    std::cout << n1 << std::endl;
    std::cout << n2 << std::endl;
    std::cout << n3 << std::endl;

    std::cout << &n3 << std::endl;

    LinkList l1{1, 2, 3};
    std::cout << l1.GetRoot() << std::endl;
    std::cout << l1 << std::endl;

    std::vector<int> v{1, 2, 3, 4, 5};
    LinkList l2(v);

    std::cout << l2 << std::endl;

    std::vector<float> fv{1.0, 2.34, 3.67, 9.66};

    struct Fun {
        int operator()(float& val) { return std::round(val); }
    };

    Fun f;
    auto fun = [](float& val) { return std::round(val); };
    Transformer<int, float> funtor = fun;
    BaseLinkList<int> l3(fv, funtor);
    std::cout << l3 << std::endl;
}