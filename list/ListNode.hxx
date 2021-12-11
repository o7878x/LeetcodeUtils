#ifndef LIST_NODE_HXX__
#define LIST_NODE_HXX__

#include <functional>
#include <initializer_list>
#include <stack>
#include <vector>

template <typename OutputType, typename InputType,
          typename = std::enable_if_t<!std::is_void<OutputType>::value && !std::is_void<InputType>::value>>
using Transformer = std::function<OutputType(InputType&)>;

template <typename T>
struct BaseListNode {
    using Value = T;
    using Ptr = BaseListNode<Value>*;

    Value val;
    Ptr next;

    // normal constructor
    BaseListNode() : BaseListNode({}, nullptr) {}
    BaseListNode(Value value) : BaseListNode(value, nullptr) {}
    BaseListNode(Value value, Ptr next) : val{value}, next{next} {}

    // copy constructor
    BaseListNode(const BaseListNode<T>& otherNode) : val{otherNode.val}, next{otherNode.next} {}
    BaseListNode& operator=(const BaseListNode<T>& otherNode) {
        this->val = otherNode.val;
        this->next = otherNode.val;
    }

    // move constructor
    BaseListNode(BaseListNode<T>&& otherNode) {
        this->val = std::move(otherNode.val);

        this->next = otherNode.next;
        otherNode.next = nullptr;
    }
    BaseListNode& operator=(const BaseListNode<T>&& otherNode) {
        this->val = std::move(otherNode.val);

        this->next = otherNode.next;
        otherNode.next = nullptr;
    }

    // destructor
    ~BaseListNode() = default;

    // comparator
    bool operator==(const BaseListNode<T>& otherNode) const { return val == otherNode.val; }
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

    template <typename U>
    BaseLinkList(std::vector<U>& initList, Transformer<T, U>& fun) {
        Node tempNode;
        NodePtr curPtr = &tempNode;
        for (auto& val : initList) {
            curPtr->next = new Node(fun(val));
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

    BaseLinkList(const BaseLinkList& others) = delete;
    BaseLinkList& operator==(const BaseLinkList& others) = delete;

    BaseLinkList(BaseLinkList&& others) = delete;
    BaseLinkList& operator==(BaseLinkList&& others) = delete;

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

    NodePtr GetRoot() const { return root; }

    void Loop(std::function<bool(T)>) {}

private:
    NodePtr root;
};

using ListNode = BaseListNode<int>;
using LinkList = BaseLinkList<int>;

#endif