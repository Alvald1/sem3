#include <gtest/gtest.h>
#include "../src/schools/school/school.hpp"
#include "../src/schools/school/ability/creature.hpp"

class SchoolTest : public ::testing::Test {
protected:
    School school{"Test School"};
    Creature creature1{"FireDragon", 5, 10, 2, 1, 3};
    Creature creature2{"IceGolem", 3, 15, 1, 2, 2};
    Creature creature3{"ThunderBird", 7, 8, 3, 3, 4};
    
    size_t first_ability_id;
    size_t second_ability_id;
    size_t third_ability_id;

    void SetUp() override {
        Ability ability1("Fireball", &creature1, 1, 10, 5);
        Ability ability2("Ice Shield", &creature2, 2, 15, 8);
        Ability ability3("Lightning", &creature3, 3, 20, 12);
        
        first_ability_id = ability1.get_id();
        second_ability_id = ability2.get_id();
        third_ability_id = ability3.get_id();
        
        school.add_ability(ability1);
        school.add_ability(ability2);
        school.add_ability(ability3);
    }
};

TEST_F(SchoolTest, Constructor) {
    School s("Magic School");
    EXPECT_EQ(s.get_name(), "Magic School");
    EXPECT_TRUE(s.get_abilities().empty());
}

TEST_F(SchoolTest, AddAbility) {
    Ability new_ability("Test Ability", &creature1, 1, 5, 3);
    size_t initial_size = school.get_abilities().size();
    school.add_ability(new_ability);
    
    EXPECT_EQ(school.get_abilities().size(), initial_size + 1);
    auto found = school.find_ability_by_id(new_ability.get_id());
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->get_name(), "Test Ability");
}

TEST_F(SchoolTest, FindAbilityById) {
    auto found = school.find_ability_by_id(first_ability_id);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->get_name(), "Fireball");
    
    auto not_found = school.find_ability_by_id(999);
    EXPECT_FALSE(not_found.has_value());
}

TEST_F(SchoolTest, GetAvailableAbilities) {
    auto abilities = school.get_available_abilities(2, 15);
    EXPECT_FALSE(abilities.empty());
    for (const auto& ability : abilities) {
        EXPECT_LE(ability.get_level(), 2);
        EXPECT_LE(ability.get_energy(), 15);
    }
    
    auto no_abilities = school.get_available_abilities(0, 0);
    EXPECT_TRUE(no_abilities.empty());
}

TEST_F(SchoolTest, GetUpgradableAbilities) {
    auto abilities = school.get_upgradable_abilities(2, 20);
    EXPECT_FALSE(abilities.empty());
    for (const auto& ability : abilities) {
        EXPECT_TRUE(ability.can_upgrade(20, 2));
    }
    
    auto no_abilities = school.get_upgradable_abilities(0, 0);
    EXPECT_TRUE(no_abilities.empty());
}

TEST_F(SchoolTest, CountCreatures) {
    EXPECT_EQ(school.count_creatures(), 3);
    
    Ability new_ability("New Fire", &creature1, 1, 5, 3);
    school.add_ability(new_ability);
    EXPECT_EQ(school.count_creatures(), 3);  // Same creature
    
    Creature creature4{"WindSpirit", 4, 12, 2, 2, 3};
    Ability wind_ability("Wind Blast", &creature4, 1, 8, 4);
    school.add_ability(wind_ability);
    EXPECT_EQ(school.count_creatures(), 4);  // New creature
}

TEST_F(SchoolTest, CopyConstructor) {
    School copied_school = school;
    EXPECT_EQ(copied_school.get_abilities().size(), school.get_abilities().size());
    EXPECT_EQ(copied_school.count_creatures(), school.count_creatures());
    
    auto original = school.find_ability_by_id(first_ability_id);
    auto copied = copied_school.find_ability_by_id(first_ability_id);
    ASSERT_TRUE(original.has_value() && copied.has_value());
    EXPECT_EQ(copied->get_name(), original->get_name());
}

TEST_F(SchoolTest, MoveConstructor) {
    size_t initial_size = school.get_abilities().size();
    size_t initial_creatures = school.count_creatures();
    
    School moved_school = std::move(School(school));
    EXPECT_EQ(moved_school.get_abilities().size(), initial_size);
    EXPECT_EQ(moved_school.count_creatures(), initial_creatures);
    
    auto ability = moved_school.find_ability_by_id(first_ability_id);
    ASSERT_TRUE(ability.has_value());
    EXPECT_EQ(ability->get_name(), "Fireball");
}

TEST_F(SchoolTest, CopyAssignmentOperator) {
    School other_school("Other School");
    other_school = school;
    
    EXPECT_EQ(other_school.get_abilities().size(), school.get_abilities().size());
    EXPECT_EQ(other_school.count_creatures(), school.count_creatures());
    
    auto ability = other_school.find_ability_by_id(first_ability_id);
    ASSERT_TRUE(ability.has_value());
    EXPECT_EQ(ability->get_name(), "Fireball");
}

TEST_F(SchoolTest, MoveAssignmentOperator) {
    School other_school("Other School");
    size_t initial_size = school.get_abilities().size();
    size_t initial_creatures = school.count_creatures();
    
    other_school = std::move(School(school));
    
    EXPECT_EQ(other_school.get_abilities().size(), initial_size);
    EXPECT_EQ(other_school.count_creatures(), initial_creatures);
    
    auto ability = other_school.find_ability_by_id(first_ability_id);
    ASSERT_TRUE(ability.has_value());
    EXPECT_EQ(ability->get_name(), "Fireball");
}
