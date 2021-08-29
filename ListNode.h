#ifndef LIST_NODE_H__
#define LIST_NODE_H__

#include <initializer_list>
#include <vector>
#include <stack>

template <typename T>
struct BaseListNode {
    using Value = T;
    using Ptr = BaseListNode<Value>*;

    Value val;
    Ptr next;

    BaseListNode() : BaseListNode({}, nullptr) {}
    BaseListNode(Value value) : BaseListNode(value, nullptr) {}
    BaseListNode(Value value, Ptr next) : val{value}, next{next} {}

    ~BaseListNode() = default;

    BaseListNode(const BaseListNode<T>& otherNode) {
        val = otherNode.val;
        next = otherNode.next;
    }

    BaseListNode(BaseListNode<T>&& otherNode) {
        val = std::move(otherNode.val);

        next = otherNode.next;
        otherNode.next = nullptr;
    }
};

template <typename T>
class BaseLinkList {
    public:
        using Node = BaseListNode<T>;
        using NodePtr = Node*;

        BaseLinkList(std::initializer_list<T> initList) {
            Node tempNode;
            NodePtr curPtr = &tempNode;
            for (const auto& val : initList) {
                curPtr->next = new Node(val);
                curPtr = curPtr->next;
            }

            root = tempNode.next;
        }

        BaseLinkList(std::vector<T>& v) {
            Node tempNode;
            NodePtr curPtr = &tempNode;
            for (const auto& val : v) {
                curPtr->next = new Node(val);
                curPtr = curPtr->next;
            }

            root = tempNode.next;
        }

        ~BaseLinkList() {
            std::stack<NodePtr> ptrStack;
            NodePtr curPtr = root;
            while (curPtr) {
                ptrStack.push(curPtr);
                curPtr = curPtr->next;
            }

            while (!ptrStack.empty()) {
                curPtr = ptrStack.top();
                ptrStack.pop();
                delete curPtr;
            }
        }

        NodePtr GetRoot() const {
            return root;
        }

    private:
        NodePtr root;
};


using ListNode = BaseListNode<int>;
using LinkList = BaseLinkList<int>;

#endif