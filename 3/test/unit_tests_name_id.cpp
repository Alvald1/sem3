#include <gtest/gtest.h>
#include "../src/utilities/name_id.hpp"

TEST(NameIDTest, Constructor) {
    NameID id(1, "test");
    EXPECT_EQ(id.get_id(), 1);
    EXPECT_EQ(id.get_name(), "test");
}

TEST(NameIDTest, CopyConstructor) {
    NameID original(1, "test");
    NameID copy(original);

    EXPECT_EQ(copy.get_id(), original.get_id());
    EXPECT_EQ(copy.get_name(), original.get_name());
}

TEST(NameIDTest, AssignmentOperator) {
    NameID id1(1, "test1");
    NameID id2(2, "test2");

    id2 = id1;
    EXPECT_EQ(id2.get_id(), 1);
    EXPECT_EQ(id2.get_name(), "test1");
}

TEST(NameIDTest, SetName) {
    NameID id(1, "test");
    id.set_name("new_test");
    EXPECT_EQ(id.get_name(), "new_test");
}

TEST(NameIDTest, SelfAssignment) {
    NameID id(1, "test");
    id = id; // Should handle self-assignment gracefully

    EXPECT_EQ(id.get_id(), 1);
    EXPECT_EQ(id.get_name(), "test");
}
