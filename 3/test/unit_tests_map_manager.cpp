#include <gtest/gtest.h>

#include "managers/map_manager.hpp"
#include "queue/entity/troop/base_troop.hpp"
#include "utilities/exceptions.hpp" // Ensure exception definitions are included

class MapManagerTest : public ::testing::Test {
  protected:
    void
    SetUp() override {
        map_manager = &MapManager::getInstance();
        // Initialize the map with size 5x5
        map_manager->make_map({5, 5});

        // Ensure all cells are passable
        for (size_t y = 0; y < 5; ++y) {
            for (size_t x = 0; x < 5; ++x) {
                Position pos(y, x);
                auto cell = map_manager->get_cell(pos);
                cell->set_passability(true);
            }
        }
    }

    void
    TearDown() override {
        MapManager::destroyInstance();
    }

    MapManager* map_manager;
};

TEST_F(MapManagerTest, AddEntityTest) {
    Position pos(1, 1);
    EXPECT_TRUE(map_manager->add_entity(1, pos));
    EXPECT_TRUE(map_manager->is_cell_occupied(pos));

    // Try to add entity to occupied cell
    EXPECT_FALSE(map_manager->add_entity(2, pos));

    // Try to add entity out of bounds
    Position invalid_pos(-1, -1);
    EXPECT_FALSE(map_manager->add_entity(3, invalid_pos));
}

TEST_F(MapManagerTest, MoveEntityTest) {
    Position start_pos(1, 1);
    Position target_pos(1, 2);

    // Ensure entity is added successfully
    EXPECT_TRUE(map_manager->add_entity(1, start_pos)) << "Failed to add entity at position (1,1)";

    // Verify the entity's initial position
    auto initial_pos = map_manager->get_entity_position(1);
    ASSERT_TRUE(initial_pos.has_value()) << "Entity position should have a value after adding.";
    EXPECT_EQ(initial_pos.value(), start_pos) << "Entity initial position mismatch.";

    // Attempt to move the entity to target position
    EXPECT_NO_THROW(map_manager->move_entity(1, target_pos)) << "move_entity threw an exception.";

    // Verify that the entity has moved to the target position
    auto new_pos = map_manager->get_entity_position(1);
    ASSERT_TRUE(new_pos.has_value()) << "Entity position should have a value after moving.";
    EXPECT_EQ(new_pos.value(), target_pos) << "Entity did not move to the target position.";

    // Verify cell occupancy
    EXPECT_FALSE(map_manager->is_cell_occupied(start_pos)) << "Start cell should not be occupied after moving.";
    EXPECT_TRUE(map_manager->is_cell_occupied(target_pos)) << "Target cell should be occupied after moving.";

    // Test invalid moves
    Position invalid_pos(-1, -1);
    EXPECT_THROW(map_manager->move_entity(1, invalid_pos), CellNotPassableException)
        << "move_entity should throw CellNotPassableException for out-of-bounds position.";

    // Test moving to occupied cell
    Position another_pos(1, 3);
    EXPECT_TRUE(map_manager->add_entity(2, another_pos)) << "Failed to add second entity at position (1,3)";
    EXPECT_THROW(map_manager->move_entity(1, another_pos), CellOccupiedException)
        << "move_entity should throw CellOccupiedException when moving to an occupied cell.";
}

TEST_F(MapManagerTest, RemoveEntityTest) {
    Position pos(1, 1);
    EXPECT_TRUE(map_manager->add_entity(1, pos));
    EXPECT_TRUE(map_manager->is_cell_occupied(pos));

    map_manager->remove_entity(1);
    EXPECT_FALSE(map_manager->is_cell_occupied(pos));

    // Test removing non-existent entity
    EXPECT_NO_THROW(map_manager->remove_entity(999));
}

TEST_F(MapManagerTest, GetEntityPositionTest) {
    Position pos(1, 1);
    EXPECT_TRUE(map_manager->add_entity(1, pos));

    auto entity_pos = map_manager->get_entity_position(1);
    EXPECT_TRUE(entity_pos.has_value());
    EXPECT_EQ(entity_pos.value(), pos);

    // Test non-existent entity
    auto invalid_pos = map_manager->get_entity_position(999);
    EXPECT_FALSE(invalid_pos.has_value());
}

TEST_F(MapManagerTest, CellPassabilityTest) {
    Position pos(1, 1);
    EXPECT_TRUE(map_manager->is_cell_passable(pos));

    // Test out of bounds
    Position invalid_pos(-1, -1);
    EXPECT_FALSE(map_manager->is_cell_passable(invalid_pos));
}

TEST_F(MapManagerTest, ChangeCellTypeTest) {
    Position pos(1, 1);
    EXPECT_NO_THROW(map_manager->change_cell_type(pos, EffectType::DAMAGE, 10, 5));

    // Test invalid position
    Position invalid_pos(-1, -1);
    EXPECT_THROW(map_manager->change_cell_type(invalid_pos, EffectType::DAMAGE), OutOfBoundsException);

    // Test changing back to normal cell
    EXPECT_NO_THROW(map_manager->change_cell_type(pos, EffectType::NONE));
}

TEST_F(MapManagerTest, CanEntityAttackTest) {
    Position attacker_pos(1, 1);
    Position target_pos(1, 2);

    EXPECT_TRUE(map_manager->add_entity(1, attacker_pos));
    EXPECT_TRUE(map_manager->add_entity(2, target_pos));

    EXPECT_TRUE(map_manager->can_entity_attack(1, target_pos));

    // Test attacking empty cell
    Position empty_pos(1, 3);
    EXPECT_FALSE(map_manager->can_entity_attack(1, empty_pos));

    // Test non-existent attacker
    EXPECT_FALSE(map_manager->can_entity_attack(999, target_pos));
}

TEST_F(MapManagerTest, CanMoveEntityTest) {
    Position start_pos(1, 1);
    Position target_pos(1, 2);

    EXPECT_TRUE(map_manager->add_entity(1, start_pos));
    EXPECT_TRUE(map_manager->can_move_entity(1, target_pos));

    // Test moving to occupied cell
    EXPECT_TRUE(map_manager->add_entity(2, target_pos));
    EXPECT_FALSE(map_manager->can_move_entity(1, target_pos));

    // Test non-existent entity
    EXPECT_FALSE(map_manager->can_move_entity(999, target_pos));
}

TEST_F(MapManagerTest, EffectCellsTest) {
    Position pos(1, 1);
    map_manager->change_cell_type(pos, EffectType::DAMAGE, 10, 5);

    const auto& effect_cells = map_manager->get_effect_cells();
    EXPECT_EQ(effect_cells.size(), 1);

    map_manager->change_cell_type(pos, EffectType::NONE);
    EXPECT_EQ(map_manager->get_effect_cells().size(), 0);
}

TEST_F(MapManagerTest, AddMultipleEntitiesTest) {
    Position pos1(0, 0);
    Position pos2(4, 4);
    Position pos3(2, 2);

    EXPECT_TRUE(map_manager->add_entity(1, pos1)) << "Failed to add first entity at position (0,0)";
    EXPECT_TRUE(map_manager->add_entity(2, pos2)) << "Failed to add second entity at position (4,4)";
    EXPECT_TRUE(map_manager->add_entity(3, pos3)) << "Failed to add third entity at position (2,2)";

    EXPECT_TRUE(map_manager->is_cell_occupied(pos1)) << "Cell (0,0) should be occupied by entity 1";
    EXPECT_TRUE(map_manager->is_cell_occupied(pos2)) << "Cell (4,4) should be occupied by entity 2";
    EXPECT_TRUE(map_manager->is_cell_occupied(pos3)) << "Cell (2,2) should be occupied by entity 3";
}

TEST_F(MapManagerTest, AddEntityOnMapBoundariesTest) {
    Position top_left(0, 0);
    Position top_right(0, 4);
    Position bottom_left(4, 0);
    Position bottom_right(4, 4);

    EXPECT_TRUE(map_manager->add_entity(1, top_left)) << "Failed to add entity at top-left corner (0,0)";
    EXPECT_TRUE(map_manager->add_entity(2, top_right)) << "Failed to add entity at top-right corner (0,4)";
    EXPECT_TRUE(map_manager->add_entity(3, bottom_left)) << "Failed to add entity at bottom-left corner (4,0)";
    EXPECT_TRUE(map_manager->add_entity(4, bottom_right)) << "Failed to add entity at bottom-right corner (4,4)";

    EXPECT_TRUE(map_manager->is_cell_occupied(top_left)) << "Cell (0,0) should be occupied by entity 1";
    EXPECT_TRUE(map_manager->is_cell_occupied(top_right)) << "Cell (0,4) should be occupied by entity 2";
    EXPECT_TRUE(map_manager->is_cell_occupied(bottom_left)) << "Cell (4,0) should be occupied by entity 3";
    EXPECT_TRUE(map_manager->is_cell_occupied(bottom_right)) << "Cell (4,4) should be occupied by entity 4";
}

TEST_F(MapManagerTest, RemoveEntityTwiceTest) {
    Position pos(2, 2);
    EXPECT_TRUE(map_manager->add_entity(1, pos)) << "Failed to add entity at position (2,2)";
    EXPECT_TRUE(map_manager->is_cell_occupied(pos)) << "Cell (2,2) should be occupied by entity 1";

    map_manager->remove_entity(1);
    EXPECT_FALSE(map_manager->is_cell_occupied(pos)) << "Cell (2,2) should be unoccupied after removing entity 1";

    // Attempt to remove the same entity again
    EXPECT_NO_THROW(map_manager->remove_entity(1)) << "Removing the same entity twice should not throw";
}

TEST_F(MapManagerTest, MoveNonExistentEntityTest) {
    Position pos(1, 1);
    Position target_pos(1, 2);

    // Attempt to move an entity that doesn't exist
    EXPECT_THROW(map_manager->move_entity(999, target_pos), EntityNotFoundException)
        << "Moving a non-existent entity should throw EntityNotFoundException";
}

TEST_F(MapManagerTest, ChangeCellTypeWithOccupiedCellTest) {
    Position pos(3, 2);
    EXPECT_TRUE(map_manager->add_entity(1, pos)) << "Failed to add entity at position (3,2)";

    // Change cell type to DAMAGE while occupied
    EXPECT_NO_THROW(map_manager->change_cell_type(pos, EffectType::DAMAGE, 10, 5))
        << "Changing cell type to DAMAGE on an occupied cell should not throw";

    auto cell = map_manager->get_cell(pos);
    EXPECT_FALSE(cell->is_empty()) << "Cell should remain occupied after changing its type to DAMAGE";
    EXPECT_EQ(cell->get_id_entity(), 1) << "Entity ID should remain unchanged after changing cell type";

    // Verify that the entity is still correctly associated
    auto entity_pos = map_manager->get_entity_position(1);
    ASSERT_TRUE(entity_pos.has_value()) << "Entity position should have a value after changing cell type";
    EXPECT_EQ(entity_pos.value(), pos) << "Entity position should remain unchanged after changing cell type";
}
