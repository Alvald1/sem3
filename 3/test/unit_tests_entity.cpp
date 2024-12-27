#include <gtest/gtest.h>
#include "queue/entity/builder/entity_director.hpp"
#include "schools/builders/director.hpp"

class TestEntity : public Entity {
  public:
    explicit TestEntity(const Ability& ability) : Entity(ability) {}
};

class EntityTest : public ::testing::Test {
  protected:
    Creature test_creature = Director::buildCreature("TestCreature", 5, 5, 3, 1, 10);
    Ability test_ability = Director::buildAbility("Test", test_creature, 1, 0, 0, 1000);
    TestEntity* entity{nullptr}; // Initialize to nullptr

    void
    SetUp() override {
        entity = new TestEntity(test_ability);
    }

    void
    TearDown() override {
        delete entity;
        entity = nullptr;
    }

    ~EntityTest() override {
        if (entity) {
            delete entity;
            entity = nullptr;
        }
    }
};

TEST_F(EntityTest, InitialValues) {
    EXPECT_EQ(entity->get_hp(), 1000);
    EXPECT_EQ(entity->get_max_hp(), 1000);
    EXPECT_EQ(entity->get_initiative(), 10);
    EXPECT_TRUE(entity->is_alive());
}

TEST_F(EntityTest, ModifyHP) {
    entity->modify_hp(-500);
    EXPECT_EQ(entity->get_hp(), 500);
    EXPECT_EQ(entity->get_health_percentage(), 50.0);

    entity->modify_hp(200);
    EXPECT_EQ(entity->get_hp(), 700);

    // Test overflow protection
    entity->modify_hp(1000);
    EXPECT_EQ(entity->get_hp(), 1000);
}

TEST_F(EntityTest, Death) {
    entity->modify_hp(-2000);
    EXPECT_EQ(entity->get_hp(), 0);
    EXPECT_FALSE(entity->is_alive());
}

TEST_F(EntityTest, HealthPercentage) {
    entity->set_hp(750);
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 75.0);
}
