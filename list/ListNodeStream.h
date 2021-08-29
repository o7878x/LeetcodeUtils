#ifndef LIST_NODE_STREAM_H__
#define LIST_NODE_STREAM_H__

#include <cstddef>
#include <iostream>
#include <type_traits>

#include "ListNode.h"

template <typename T, typename = decltype(std::declval<std::ostream>() << std::declval<T>())>
std::ostream& operator<<(std::ostream& os, const BaseListNode<T>& node) {
    return os << "[ val = " << node.val << " next = " << node.next << " ]";
}

template <typename T, typename = decltype(std::declval<std::ostream>() << std::declval<T>())>
std::ostream& operator<<(std::ostream& os, const BaseLinkList<T>& node) {
    typename BaseLinkList<T>::NodePtr root = node.GetRoot();
    if (!root) {
        return os << "[ Empty List ]" << std::endl;
    }

    std::size_t i = 0;
    while (root) {
        os << "Index = " << i << " Node = " << *root << std::endl;

        i++;
        root = root->next;
    }

    return os;
}

#endif