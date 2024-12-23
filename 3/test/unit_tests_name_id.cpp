#include <gtest/gtest.h>
#include "utilities/name_id.hpp"

class NameIDTest : public ::testing::Test {
  protected:
    NameID* test_obj;

    void
    SetUp() override {
        test_obj = new NameID(1, "Test");
    }

    void
    TearDown() override {
        delete test_obj;
    }
};

TEST_F(NameIDTest, ConstructorTest) {
    NameID obj(42, "TestName");
    EXPECT_EQ(obj.get_id(), 42);
    EXPECT_EQ(obj.get_name(), "TestName");
}

TEST_F(NameIDTest, GetIdTest) { EXPECT_EQ(test_obj->get_id(), 1); }

TEST_F(NameIDTest, GetNameTest) { EXPECT_EQ(test_obj->get_name(), "Test"); }

TEST_F(NameIDTest, SetNameTest) {
    test_obj->set_name("NewName");
    EXPECT_EQ(test_obj->get_name(), "NewName");
}

TEST_F(NameIDTest, EmptyNameTest) {
    test_obj->set_name("");
    EXPECT_EQ(test_obj->get_name(), "");
}
