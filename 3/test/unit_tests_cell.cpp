#include <gtest/gtest.h>
#include "map/cell/builders/cell_director.hpp"
#include "utilities/position.hpp"

class CellTest : public ::testing::Test {
  protected:
    Position pos{1, 2};
};

TEST_F(CellTest, BasicCellCreation) {
    Cell cell = CellDirector::createBasicCell(Position(2, 1)); // Explicit constructor call
    auto cell_pos = cell.get_position();
    EXPECT_EQ(cell_pos.get_x(), 1);
    EXPECT_EQ(cell_pos.get_y(), 2);
    EXPECT_TRUE(cell.get_passability());
    EXPECT_FALSE(cell.get_busy());
    EXPECT_EQ(cell.get_id_entity(), 0);
}

TEST_F(CellTest, WallCreation) {
    Cell wall = CellDirector::createWall(pos);
    EXPECT_FALSE(wall.get_passability());
    EXPECT_TRUE(wall.get_busy());
}

TEST_F(CellTest, CellModification) {
    Cell cell = CellDirector::createBasicCell(pos);
    cell.set_busy(true);
    EXPECT_TRUE(cell.get_busy());
    EXPECT_FALSE(cell.is_empty());

    cell.set_id_entity(42);
    EXPECT_EQ(cell.get_id_entity(), 42);

    cell.set_passability(false);
    EXPECT_FALSE(cell.get_passability());
}

TEST_F(CellTest, CellCopyAndMove) {
    Cell original = CellDirector::createBasicCell(pos);
    Cell copied(original);
    EXPECT_EQ(copied.get_position().get_x(), original.get_position().get_x());
    EXPECT_EQ(copied.get_position().get_y(), original.get_position().get_y());

    Cell moved = std::move(copied);
    EXPECT_EQ(moved.get_position().get_x(), original.get_position().get_x());
    EXPECT_EQ(moved.get_position().get_y(), original.get_position().get_y());
}
