#include <gtest/gtest.h>
#include "map/cell/time.hpp"

TEST(TimeTest, Constructor) {
    Time time(5);
    EXPECT_EQ(time.get_time(), 5);
}

TEST(TimeTest, DecreaseTime) {
    Time time(3);
    time.decrease_time();
    EXPECT_EQ(time.get_time(), 2);
    time.decrease_time();
    EXPECT_EQ(time.get_time(), 1);
    time.decrease_time();
    EXPECT_EQ(time.get_time(), 0);
    time.decrease_time(); // Should not go below 0
    EXPECT_EQ(time.get_time(), 0);
}

TEST(TimeTest, IsNotZero) {
    Time time(1);
    EXPECT_TRUE(time.is_not_zero());
    time.decrease_time();
    EXPECT_FALSE(time.is_not_zero());
}

TEST(TimeTest, SetTime) {
    Time time(0);
    time.set_time(10);
    EXPECT_EQ(time.get_time(), 10);
}
