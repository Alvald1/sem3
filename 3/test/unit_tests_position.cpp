#include <gtest/gtest.h>
#include "../src/utilities/position.hpp"

TEST(PositionTest, DefaultConstructor) {
    Position pos;
    EXPECT_EQ(pos.get_x(), 0);
    EXPECT_EQ(pos.get_y(), 0);
}

TEST(PositionTest, ParameterizedConstructor) {
    Position pos(2, 3);
    EXPECT_EQ(pos.get_x(), 3);
    EXPECT_EQ(pos.get_y(), 2);
}

TEST(PositionTest, SettersAndGetters) {
    Position pos;
    pos.set_x(5);
    pos.set_y(7);
    EXPECT_EQ(pos.get_x(), 5);
    EXPECT_EQ(pos.get_y(), 7);
}

TEST(PositionTest, Addition) {
    Position pos1(1, 2);
    Position pos2(3, 4);
    Position result = pos1 + pos2;
    EXPECT_EQ(result.get_x(), 6);
    EXPECT_EQ(result.get_y(), 4);
}

TEST(PositionTest, Equality) {
    Position pos1(1, 2);
    Position pos2(1, 2);
    Position pos3(2, 1);
    EXPECT_TRUE(pos1 == pos2);
    EXPECT_FALSE(pos1 == pos3);
}

TEST(PositionTest, ManhattanDistance) {
    Position pos1(1, 1);
    Position pos2(4, 5);
    EXPECT_EQ(pos1.manhattan_distance(pos2), 7);
    EXPECT_EQ(pos2.manhattan_distance(pos1), 7);
}
