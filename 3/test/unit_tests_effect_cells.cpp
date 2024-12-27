#include <gtest/gtest.h>
#include "map/cell/builders/cell_director.hpp"
#include "utilities/exceptions.hpp"

class EffectCellsTest : public ::testing::Test {
  protected:
    Position pos{0, 0};
    const size_t duration = 3;
};

TEST_F(EffectCellsTest, SpeedCell) {
    EffectCellSpeed cell = CellDirector::createSpeedCell(pos, 5, duration);
    EXPECT_TRUE(cell.get_sing());
    EXPECT_EQ(cell.give_effect(), 5);
    EXPECT_EQ(cell.give_effect(), 5);
    EXPECT_EQ(cell.give_effect(), 5);
    EXPECT_THROW(cell.give_effect(), EffectExpiredException);

    // Test negative speed
    cell.set_effect(-3, 1);
    EXPECT_FALSE(cell.get_sing());
}

TEST_F(EffectCellsTest, RangeCell) {
    EffectCellRange cell = CellDirector::createRangeCell(pos, 2, duration);
    EXPECT_TRUE(cell.get_sing());
    EXPECT_EQ(cell.give_effect(), 2);

    cell.set_effect(-1, 1);
    EXPECT_FALSE(cell.get_sing());
}

TEST_F(EffectCellsTest, HPCell) {
    EffectCellHP cell = CellDirector::createHPCell(pos, 10, duration);
    EXPECT_TRUE(cell.get_sing());
    EXPECT_EQ(cell.give_effect(), 10);

    cell.set_effect(-5, 1);
    EXPECT_FALSE(cell.get_sing());
}

TEST_F(EffectCellsTest, DamageCell) {
    EffectCellDamage cell = CellDirector::createDamageCell(pos, 15, duration);
    EXPECT_TRUE(cell.get_sing());
    EXPECT_EQ(cell.give_effect(), 15);

    cell.set_effect(-7, 1);
    EXPECT_FALSE(cell.get_sing());
}

TEST_F(EffectCellsTest, EffectExpiration) {
    auto test_expiration = [](auto cell) { // Remove reference
        cell.give_effect();                // duration 2
        cell.give_effect();                // duration 1
        cell.give_effect();                // duration 0
        EXPECT_THROW(cell.give_effect(), EffectExpiredException);
    };

    auto speed_cell = CellDirector::createSpeedCell(pos, 1, duration);
    auto range_cell = CellDirector::createRangeCell(pos, 1, duration);
    auto hp_cell = CellDirector::createHPCell(pos, 1, duration);
    auto damage_cell = CellDirector::createDamageCell(pos, 1, duration);

    test_expiration(speed_cell);
    test_expiration(range_cell);
    test_expiration(hp_cell);
    test_expiration(damage_cell);
}
