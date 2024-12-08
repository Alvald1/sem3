#include <gtest/gtest.h>
#include "../src/schools/school/ability/creature.hpp"
#include "../src/schools/school/school.hpp"

class SchoolTest : public ::testing::Test {
  protected:
    School school{"Test School"};
    Creature creature1{"FireDragon", 5, 10, 2, 1, 3};
    Creature creature2{"IceGolem", 3, 15, 1, 2, 2};
    Creature creature3{"ThunderBird", 7, 8, 3, 3, 4};

    size_t first_ability_id;
    size_t second_ability_id;
    size_t third_ability_id;

    void
    SetUp() override {
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
    EXPECT_EQ(school.count_creatures(), 3); // Same creature

    Creature creature4{"WindSpirit", 4, 12, 2, 2, 3};
    Ability wind_ability("Wind Blast", &creature4, 1, 8, 4);
    school.add_ability(wind_ability);
    EXPECT_EQ(school.count_creatures(), 4); // New creature
}

TEST_F(SchoolTest, CountCreaturesWithRemovedAbility) {
    size_t initial_count = school.count_creatures();
    
    // Create a new ability with a unique creature
    Creature unique_creature{"UniqueCreature", 1};
    Ability unique_ability("UniqueAbility", &unique_creature);
    school.add_ability(unique_ability);
    EXPECT_EQ(school.count_creatures(), initial_count + 1);

    // Remove the ability and verify count decreases
    auto& abilities = const_cast<std::vector<Ability>&>(school.get_abilities());
    size_t last_idx = abilities.size() - 1;
    abilities.pop_back();
    EXPECT_EQ(school.count_creatures(), initial_count);
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

TEST_F(SchoolTest, EmptySchoolOperations) {
    School empty_school("Empty");
    EXPECT_EQ(empty_school.count_creatures(), 0);
    EXPECT_TRUE(empty_school.get_available_abilities(100, 100).empty());
    EXPECT_TRUE(empty_school.get_upgradable_abilities(100, 100).empty());
    EXPECT_FALSE(empty_school.find_ability_by_id(1).has_value());
    EXPECT_FALSE(empty_school.has_ability(1));
}

TEST_F(SchoolTest, DuplicateAbilityAddition) {
    size_t initial_size = school.get_abilities().size();
    Ability duplicate("Fireball", &creature1, 1, 10, 5);
    duplicate = school.get_abilities()[0]; // Copy the first ability

    school.add_ability(duplicate);
    EXPECT_EQ(school.get_abilities().size(), initial_size);
}

TEST_F(SchoolTest, MaxValuesTest) {
    Creature max_creature("MaxCreature", SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX);
    Ability max_ability("MaxAbility", &max_creature, SIZE_MAX, SIZE_MAX, SIZE_MAX);

    school.add_ability(max_ability);
    auto available = school.get_available_abilities(SIZE_MAX, SIZE_MAX);
    EXPECT_FALSE(available.empty());
    EXPECT_TRUE(
        std::any_of(available.begin(), available.end(), [](const Ability& a) { return a.get_level() == SIZE_MAX; }));
}

TEST_F(SchoolTest, ZeroValuesTest) {
    Creature zero_creature("ZeroCreature", 0, 0, 0, 0, 0);
    Ability zero_ability("ZeroAbility", &zero_creature, 0, 0, 0);

    school.add_ability(zero_ability);
    auto available = school.get_available_abilities(1, 1);
    EXPECT_TRUE(std::any_of(available.begin(), available.end(), [](const Ability& a) { return a.get_level() == 0; }));
}

TEST_F(SchoolTest, BoundaryEnergyLevelTest) {
    auto abilities = school.get_available_abilities(1, 10);
    auto exact_match = std::count_if(abilities.begin(), abilities.end(),
                                     [](const Ability& a) { return a.get_level() == 1 && a.get_energy() == 10; });

    auto over_limit = std::count_if(abilities.begin(), abilities.end(),
                                    [](const Ability& a) { return a.get_level() > 1 || a.get_energy() > 10; });

    EXPECT_EQ(over_limit, 0);
}

TEST_F(SchoolTest, CascadingCopyTest) {
    School school1("School1");
    school1 = school;
    School school2("School2");
    school2 = school1;

    EXPECT_EQ(school2.get_abilities().size(), school.get_abilities().size());
    EXPECT_EQ(school2.count_creatures(), school.count_creatures());
}

TEST_F(SchoolTest, NullCreatureTest) {
    EXPECT_THROW(
        {
            Ability null_ability("NullCreature", nullptr, 1, 10, 5);
            school.add_ability(null_ability);
        },
        std::invalid_argument);

    size_t initial_count = school.count_creatures();
    EXPECT_EQ(school.count_creatures(), initial_count); // Count shouldn't change
}

TEST_F(SchoolTest, UpgradeAbilityBoundaryConditions) {
    // Test exact match
    auto abilities = school.get_upgradable_abilities(1, 5);
    EXPECT_TRUE(std::any_of(abilities.begin(), abilities.end(),
                            [](const Ability& a) { return a.get_level() == 1 && a.get_experience() == 5; }));

    // Test both conditions failing
    abilities = school.get_upgradable_abilities(0, 4);
    EXPECT_TRUE(std::none_of(abilities.begin(), abilities.end(), [](const Ability& a) { return a.can_upgrade(4, 0); }));
}

TEST_F(SchoolTest, NonConstAbilitiesAccess) {
    School modifiable_school("ModifiableSchool");
    Ability ability("Test", &creature1, 1, 10, 5);
    modifiable_school.add_ability(ability);

    // Attempt to modify through non-const access
    const_cast<std::vector<Ability>&>(modifiable_school.get_abilities())[0].set_level(2);
    EXPECT_EQ(modifiable_school.get_abilities()[0].get_level(), 2);
}

TEST_F(SchoolTest, FindAbilityByIdBoundary) {
    // Test with SIZE_MAX id
    EXPECT_FALSE(school.find_ability_by_id(SIZE_MAX).has_value());

    // Test with id = 0
    EXPECT_FALSE(school.find_ability_by_id(0).has_value());
}

TEST_F(SchoolTest, AvailableAbilitiesExactMatch) {
    auto abilities = school.get_available_abilities(1, 10);

    // Test exact boundary match
    bool has_exact_match = std::any_of(abilities.begin(), abilities.end(),
                                       [](const Ability& a) { return a.get_level() == 1 && a.get_energy() == 10; });
    EXPECT_TRUE(has_exact_match);
}

TEST_F(SchoolTest, CanUpgradeSingleCondition) {
    Ability ability("Test", &creature1, 2, 10, 5);
    
    // Only exp matches, level doesn't
    EXPECT_FALSE(ability.can_upgrade(5, 1));
    
    // Only level matches, exp doesn't
    EXPECT_FALSE(ability.can_upgrade(4, 2));
}

TEST_F(SchoolTest, UpgradableAbilitiesEdgeCases) {
    // Add ability with zero requirements
    Ability zero_ability("Zero", &creature1, 0, 0, 0);
    school.add_ability(zero_ability);
    
    auto abilities = school.get_upgradable_abilities(0, 0);
    EXPECT_FALSE(abilities.empty());
    EXPECT_TRUE(std::any_of(abilities.begin(), abilities.end(),
        [](const Ability& a) { return a.get_level() == 0 && a.get_experience() == 0; }));
}

TEST_F(SchoolTest, HasAbilityEdgeCases) {
    EXPECT_FALSE(school.has_ability(SIZE_MAX));
    EXPECT_FALSE(school.has_ability(0));
    
    // Test with recently deleted ability id
    size_t last_id = school.get_abilities().back().get_id();
    auto& abilities = const_cast<std::vector<Ability>&>(school.get_abilities());
    abilities.pop_back();
    EXPECT_FALSE(school.has_ability(last_id));
}

TEST_F(SchoolTest, EmptySchoolCopyMove) {
    School empty_school("Empty");
    
    // Copy empty school
    School copied = empty_school;
    EXPECT_TRUE(copied.get_abilities().empty());
    
    // Move empty school
    School moved = std::move(empty_school);
    EXPECT_TRUE(moved.get_abilities().empty());
    
    // Copy assignment of empty school
    School target("Target");
    target = copied;
    EXPECT_TRUE(target.get_abilities().empty());
    
    // Move assignment of empty school
    School target2("Target2");
    target2 = std::move(moved);
    EXPECT_TRUE(target2.get_abilities().empty());
}
