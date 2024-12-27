#include <gtest/gtest.h>
#include "../src/utilities/position.hpp"

TEST(PositionTest, Constructor) {
    Position p1;
    EXPECT_EQ(p1.get_x(), 0);
    EXPECT_EQ(p1.get_y(), 0);

    Position p2(3, 4);
    EXPECT_EQ(p2.get_x(), 4);
    EXPECT_EQ(p2.get_y(), 3);
}

TEST(PositionTest, SettersAndGetters) {
    Position p;
    p.set_x(5);
    p.set_y(7);

    EXPECT_EQ(p.get_x(), 5);
    EXPECT_EQ(p.get_y(), 7);
}

TEST(PositionTest, Addition) {
    Position p1(1, 2);
    Position p2(3, 4);
    Position result = p1 + p2;

    EXPECT_EQ(result.get_x(), 6);
    EXPECT_EQ(result.get_y(), 4);
}

TEST(PositionTest, Equality) {
    Position p1(1, 2);
    Position p2(1, 2);
    Position p3(2, 1);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PositionTest, ManhattanDistance) {
    Position p1(1, 1);
    Position p2(4, 5);

    EXPECT_EQ(p1.manhattan_distance(p2), 7);
    EXPECT_EQ(p2.manhattan_distance(p1), 7);
}
