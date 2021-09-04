#ifndef TREE_NODE_H__
#define TREE_NODE_H__

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <vector>

template <typename OutputType, typename InputType,
          typename = std::enable_if_t<!std::is_void<OutputType>::value && !std::is_void<InputType>::value>>
using Transformer = std::function<OutputType(InputType&)>;

template <typename InputType, typename = std::enable_if_t<!std::is_void<InputType>::value>>
using Verifier = std::function<bool(InputType&)>;

template <typename T>
struct BaseTreeNode {
    using Type = T;
    using NodePtr = BaseTreeNode<Type>*;

    T val;
    NodePtr left;
    NodePtr right;

    BaseTreeNode() : BaseTreeNode({}, nullptr, nullptr) {}
    BaseTreeNode(T val) : BaseTreeNode(val, nullptr, nullptr) {}
    BaseTreeNode(T val, NodePtr left, NodePtr right) : val{val}, left{left}, right{right} {}

    ~BaseTreeNode() = default;
};

template <typename T>
struct BaseBinaryTree {
public:
    using Type = T;
    using Node = BaseTreeNode<T>;
    using NodePtr = Node*;

    BaseBinaryTree(const std::vector<T>& v, Verifier<T>& fun) {
        const long len = static_cast<long>(v.size());
        if (len <= 0) {
            root = nullptr;
            return;
        }

        std::vector<NodePtr> tempList(len, nullptr);
        for (long i = 0; i < len; i++) {
            auto val = v[i];
            if (!fun(val)) {
                continue;
            }

            auto newNode = new Node(val);
            tempList[i] = newNode;
            auto parentId = ((i - 1) >> 1);
            if (parentId < 0) {
                continue;
            }

            bool isLeftNode = static_cast<bool>(i & 0x1);
            if (isLeftNode) {
                tempList[parentId]->left = newNode;
            } else {
                tempList[parentId]->right = newNode;
            }
        }

        root = tempList[0];
    }

    ~BaseBinaryTree() {
        if (!root) {
            return;
        }

        DeleteTreeNode(root);
    }

    NodePtr GetRoot() const { return root; }

private:
    void DeleteTreeNode(NodePtr curNode) {
        if (!curNode) {
            return;
        }

        if (curNode->left) {
            DeleteTreeNode(curNode->left);
        }

        if (curNode->right) {
            DeleteTreeNode(curNode->right);
        }

        delete curNode;
    }

    NodePtr root;
};

#endif