#include "set.cpp"
#include <gtest/gtest.h>

using namespace custom_set;

TEST(CustomSetTest, CopyConstructor) {
    CustomSet set1;
    set1.insert(5);

    CustomSet set2(set1);

    ASSERT_TRUE(set2.contains(5));
}

TEST(CustomSetTest, AssignmentOperator) {
    CustomSet set1;
    set1.insert(5);

    CustomSet set2;
    set2 = set1;

    ASSERT_TRUE(set2.contains(5));
}

TEST(CustomSetTest, PrintMethod) {
    CustomSet set;
    set.insert(1);
    set.insert(2);
    set.insert(3);

    // Печать содержимого не может быть протестирована напрямую в Google Test.
    set.print();
}

TEST(CustomSetTest, InsertMethod) {
    CustomSet set;
    set.insert(10);

    ASSERT_TRUE(set.contains(10));
}

TEST(CustomSetTest, ContainsMethod) {
    CustomSet set;
    set.insert(7);

    ASSERT_TRUE(set.contains(7));
    ASSERT_FALSE(set.contains(8));
}

TEST(CustomSetTest, EraseMethod) {
    CustomSet set;
    set.insert(4);
    set.erase(4);

    ASSERT_FALSE(set.contains(4));
}

TEST(CustomSetTest, IteratorTest) {
    CustomSet set;
    set.insert(1);
    set.insert(2);
    set.insert(3);

    std::vector<int> elements = { 1, 2, 3 };
    int index = 0;
    for (const auto& element : set) {
        ASSERT_EQ(element, elements[index]);
        index++;
    }
}

TEST(CustomSetTest, FindIntersectionTest) {
    CustomSet set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);

    CustomSet set2;
    set2.insert(2);
    set2.insert(3);
    set2.insert(4);

    CustomSet result = findIntersection(set1, set2);

    ASSERT_TRUE(result.contains(2));
    ASSERT_TRUE(result.contains(3));
    ASSERT_FALSE(result.contains(1));
    ASSERT_FALSE(result.contains(4));
}

TEST(CustomSetTest, FindDifferenceTest) {
    CustomSet set1;
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);

    CustomSet set2;
    set2.insert(2);
    set2.insert(3);
    set2.insert(4);

    CustomSet result = findDifference(set1, set2);

    ASSERT_TRUE(result.contains(1));
    ASSERT_FALSE(result.contains(2));
    ASSERT_FALSE(result.contains(3));
    ASSERT_FALSE(result.contains(4));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}