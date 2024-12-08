#include <gtest/gtest.h>
#include "../src/schools/school/ability/ability.hpp"
#include "../src/schools/school/ability/creature.hpp"
#include "../src/schools/school/school.hpp"
#include "../src/schools/schools.hpp"

class SchoolsTest : public ::testing::Test {
  protected:
    Schools schools;
    School school1{"Magic"};
    School school2{"Science"};
    Creature creature1{"Dragon"};
    Creature creature2{"Phoenix"};
    Ability ability1{"Fly", &creature1, 1, 10, 5};
    Ability ability2{"Rebirth", &creature2, 2, 20, 10};

    void
    SetUp() override {
        school1.add_ability(ability1);
        school2.add_ability(ability2);
        schools.add_school(school1);
        schools.add_school(school2);
    }
};

TEST_F(SchoolsTest, Constructor) {
    Schools empty_schools;
    EXPECT_EQ(empty_schools.count_schools(), 0);
}

TEST_F(SchoolsTest, AddSchool) {
    Schools new_schools;
    new_schools.add_school(school1);
    EXPECT_EQ(new_schools.count_schools(), 1);
}

TEST_F(SchoolsTest, CountSchools) { EXPECT_EQ(schools.count_schools(), 2); }

TEST_F(SchoolsTest, CountCreatures) { EXPECT_EQ(schools.count_creatures(), 2); }

TEST_F(SchoolsTest, GetAvailableAbilities_SchoolInLevels) {
    std::unordered_map<size_t, size_t> levels = {{school1.get_id(), 1}};
    auto abilities = schools.get_available_abilities(levels, 10);
    EXPECT_EQ(abilities.size(), 1);
}

TEST_F(SchoolsTest, GetAvailableAbilities_SchoolNotInLevels) {
    std::unordered_map<size_t, size_t> levels = {{999, 1}};
    auto abilities = schools.get_available_abilities(levels, 10);
    EXPECT_TRUE(abilities.empty());
}

TEST_F(SchoolsTest, GetUpgradableAbilities_SchoolInLevels) {
    std::unordered_map<size_t, size_t> levels = {{school2.get_id(), 2}};
    auto abilities = schools.get_upgradable_abilities(levels, 15);
    EXPECT_EQ(abilities.size(), 1);
}

TEST_F(SchoolsTest, GetUpgradableAbilities_SchoolNotInLevels) {
    std::unordered_map<size_t, size_t> levels = {{999, 1}};
    auto abilities = schools.get_upgradable_abilities(levels, 10);
    EXPECT_TRUE(abilities.empty());
}

TEST_F(SchoolsTest, FindSchoolById_Exists) {
    const School* found = schools.find_school_by_id(school1.get_id());
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->get_name(), "Magic");
}

TEST_F(SchoolsTest, FindSchoolById_NotExists) {
    const School* found = schools.find_school_by_id(999);
    EXPECT_EQ(found, nullptr);
}

TEST_F(SchoolsTest, FindSchoolByName_Exists) {
    const School* found = schools.find_school_by_name("Science");
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->get_id(), school2.get_id());
}

TEST_F(SchoolsTest, FindSchoolByName_NotExists) {
    const School* found = schools.find_school_by_name("Alchemy");
    EXPECT_EQ(found, nullptr);
}

TEST_F(SchoolsTest, CountTotalAbilities) { EXPECT_EQ(schools.count_total_abilities(), 2); }

TEST_F(SchoolsTest, GetSchools) {
    const auto& all_schools = schools.get_schools();
    EXPECT_EQ(all_schools.size(), 2);
}

TEST_F(SchoolsTest, HasSchool_Exists) { EXPECT_TRUE(schools.has_school(school1.get_id())); }

TEST_F(SchoolsTest, HasSchool_NotExists) { EXPECT_FALSE(schools.has_school(999)); }

TEST_F(SchoolsTest, RemoveSchool_Exists) {
    bool removed = schools.remove_school(school1.get_id());
    EXPECT_TRUE(removed);
    EXPECT_EQ(schools.count_schools(), 1);
}

TEST_F(SchoolsTest, RemoveSchool_NotExists) {
    bool removed = schools.remove_school(999);
    EXPECT_FALSE(removed);
    EXPECT_EQ(schools.count_schools(), 2);
}

TEST_F(SchoolsTest, AddDuplicateSchool) {
    Schools new_schools;
    new_schools.add_school(school1);
    new_schools.add_school(school1);  // Adding same school twice
    EXPECT_EQ(new_schools.count_schools(), 2);  // Should add both as separate schools
}

TEST_F(SchoolsTest, EmptySchoolOperations) {
    School empty_school("Empty");
    schools.add_school(empty_school);
    EXPECT_EQ(schools.count_schools(), 3);
    EXPECT_EQ(schools.count_creatures(), 2);  // Should not affect creature count
}

TEST_F(SchoolsTest, GetAvailableAbilities_NoEnergy) {
    std::unordered_map<size_t, size_t> levels = {{school1.get_id(), 10}};
    auto abilities = schools.get_available_abilities(levels, 0);
    EXPECT_TRUE(abilities.empty());
}

TEST_F(SchoolsTest, GetAvailableAbilities_HighEnergy) {
    std::unordered_map<size_t, size_t> levels = {{school1.get_id(), 10}, {school2.get_id(), 10}};
    auto abilities = schools.get_available_abilities(levels, 1000);
    EXPECT_EQ(abilities.size(), 2);  // Should get all abilities
}

TEST_F(SchoolsTest, GetUpgradableAbilities_NoExperience) {
    std::unordered_map<size_t, size_t> levels = {{school1.get_id(), 10}};
    auto abilities = schools.get_upgradable_abilities(levels, 0);
    EXPECT_TRUE(abilities.empty());
}

TEST_F(SchoolsTest, GetUpgradableAbilities_AllSchools) {
    std::unordered_map<size_t, size_t> levels;
    for (const auto& school : schools.get_schools()) {
        levels[school.get_id()] = 10;
    }
    auto abilities = schools.get_upgradable_abilities(levels, 1000);
    EXPECT_EQ(abilities.size(), 2);  // Should get all abilities
}

TEST_F(SchoolsTest, RemoveAllSchools) {
    for (const auto& school : schools.get_schools()) {
        EXPECT_TRUE(schools.remove_school(school.get_id()));
    }
    EXPECT_EQ(schools.count_schools(), 0);
    EXPECT_EQ(schools.count_creatures(), 0);
}

TEST_F(SchoolsTest, FindSchoolByName_CaseSensitive) {
    const School* found1 = schools.find_school_by_name("magic");  // lowercase
    const School* found2 = schools.find_school_by_name("Magic");  // correct case
    EXPECT_EQ(found1, nullptr);
    EXPECT_NE(found2, nullptr);
}

TEST_F(SchoolsTest, FindSchoolByName_EmptyString) {
    const School* found = schools.find_school_by_name("");
    EXPECT_EQ(found, nullptr);
}

TEST_F(SchoolsTest, SchoolsWithSameCreature) {
    // Create a school with an ability using the same creature
    School school3{"Nature"};
    Ability ability3{"SuperFly", &creature1, 3, 30, 15};  // Using creature1 again
    school3.add_ability(ability3);
    schools.add_school(school3);
    
    EXPECT_EQ(schools.count_schools(), 3);
    EXPECT_EQ(schools.count_creatures(), 2);  // Should still be 2 creatures
}
