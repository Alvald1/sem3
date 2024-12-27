#include <gtest/gtest.h>

#include "managers/entity_manager.hpp"
#include "managers/map_manager.hpp"
#include "managers/summon_manager.hpp"
#include "queue/entity/builder/summoner_builder.hpp"
#include "schools/builders/director.hpp"
#include "utilities/type_system.hpp"

class SummonManagerTest : public ::testing::Test {
  protected:
    void
    SetUp() override {
        // Initialize managers
        MapManager::getInstance();
        EntityManager::getInstance();
        SummonManager::getInstance();

        // Create a 10x10 passable map
        Matrix<bool> passability(10, 10, true);
        MapManager::getInstance().load_from_passability_matrix(passability);
    }

    void
    TearDown() override {
        MapManager::destroyInstance();
        EntityManager::destroyInstance();
        SummonManager::destroyInstance();
    }

    Summoner
    createTestSummoner() {
        // Use Bio-Engineer from schools.json
        Creature creature = Director::buildCreature("Bio-Engineer", // name
                                                    2,              // speed
                                                    3,              // damage
                                                    2,              // range
                                                    13,             // type (moral)
                                                    3               // initiative
        );

        return SummonerBuilder(Director::buildAbility("Bio-Engineer", // name
                                                      creature,       // creature
                                                      1,              // level
                                                      10,             // energy
                                                      100,            // experience
                                                      15              // hp
                                                      ))
            .build();
    }

    Ability
    createTestAbility(size_t type) {
        if (TypeSystem::getTroopType(type) == TroopType::MORAL) {
            // Use Cell Guardian from Biomancy
            return Director::buildAbility("Healing Spores", Director::buildCreature("Cell Guardian", 2, 3, 2, type, 3),
                                          1, 3, 100, 8);
        } else {
            // Use Skeleton Warriors from Necromancy
            return Director::buildAbility("Raise Dead", Director::buildCreature("Skeleton Warriors", 2, 3, 0, type, 2),
                                          1, 3, 100, 10);
        }
    }
};

TEST_F(SummonManagerTest, SummonMoralTroop) {
    auto summoner = createTestSummoner();
    auto ability = createTestAbility(769); // Moral type from schools.json
    Position summoner_pos(2, 2);
    Position summon_pos(2, 3); // Adjacent position

    MapManager::getInstance().add_entity(summoner.get_id(), summoner_pos);
    EXPECT_NO_THROW(SummonManager::getInstance().summon(summoner, ability, summon_pos));
    EXPECT_TRUE(MapManager::getInstance().is_cell_occupied(summon_pos));
}

TEST_F(SummonManagerTest, SummonAmoralTroop) {
    auto summoner = createTestSummoner();
    auto ability = createTestAbility(18);
    Position summoner_pos(2, 2);
    Position summon_pos(3, 3); // Diagonal position (distance = 2)

    MapManager::getInstance().add_entity(summoner.get_id(), summoner_pos);

    EXPECT_NO_THROW(SummonManager::getInstance().summon(summoner, ability, summon_pos));
    EXPECT_TRUE(MapManager::getInstance().is_cell_occupied(summon_pos));
}

TEST_F(SummonManagerTest, SummonOutOfRange) {
    auto summoner = createTestSummoner();
    auto ability = createTestAbility(13);
    Position summoner_pos(2, 2);
    Position summon_pos(5, 5); // Too far (distance > 2)

    MapManager::getInstance().add_entity(summoner.get_id(), summoner_pos);

    EXPECT_THROW(SummonManager::getInstance().summon(summoner, ability, summon_pos), InvalidPositionException);
}

TEST_F(SummonManagerTest, SummonOnOccupiedCell) {
    auto summoner = createTestSummoner();
    auto ability = createTestAbility(13);
    Position summoner_pos(2, 2);
    Position summon_pos(2, 3); // Adjacent position

    MapManager::getInstance().add_entity(summoner.get_id(), summoner_pos);

    // First summon should succeed
    EXPECT_NO_THROW(SummonManager::getInstance().summon(summoner, ability, summon_pos));
    EXPECT_TRUE(MapManager::getInstance().is_cell_occupied(summon_pos));

    // Second summon to same position should fail
    EXPECT_THROW(SummonManager::getInstance().summon(summoner, ability, summon_pos), InvalidPositionException);
}
