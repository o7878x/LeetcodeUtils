#include <gtest/gtest.h>

#include <vector>

#include "ListNode.hxx"

TEST(baseListNodeTest, baseConstruction) {
    ListNode n1;
    EXPECT_EQ(0, n1.val);
    EXPECT_EQ(nullptr, n1.next);

    ListNode n2(1);
    EXPECT_EQ(1, n2.val);
    EXPECT_EQ(nullptr, n2.next);

    ListNode n3(2, &n2);
    EXPECT_EQ(2, n3.val);
    EXPECT_EQ(&n2, n3.next);
}

TEST(baseListNodeTest, copyConstruction) {
    ListNode n1(1);
    ListNode n2(2, &n1);

    ListNode n3(n2);
    EXPECT_EQ(2, n3.val);
    EXPECT_EQ(&n1, n3.next);

    ListNode n4(std::move(n2));
    EXPECT_EQ(2, n4.val);
    EXPECT_EQ(&n1, n4.next);
    EXPECT_EQ(2, n2.val);
    EXPECT_EQ(nullptr, n2.next);
}

TEST(baseListNodeTest, equality) {
    ListNode n1(1);
    ListNode n2(2);

    EXPECT_TRUE(n1 == n1);
    EXPECT_FALSE(n1 == n2);
}

TEST(baseList, baseConstruction) {
    LinkList l1{1, 2, 3};
    EXPECT_EQ(1, l1.GetRoot()->val);
    EXPECT_EQ(2, l1.GetRoot()->next->val);
    EXPECT_EQ(3, l1.GetRoot()->next->next->val);
    EXPECT_EQ(nullptr, l1.GetRoot()->next->next->next);

    std::vector<int> v1 {1, 2, 3};
    LinkList l2(v1);
    EXPECT_EQ(1, l2.GetRoot()->val);
    EXPECT_EQ(2, l2.GetRoot()->next->val);
    EXPECT_EQ(3, l2.GetRoot()->next->next->val);
    EXPECT_EQ(nullptr, l2.GetRoot()->next->next->next);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}