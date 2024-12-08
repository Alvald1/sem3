#include <gtest/gtest.h>
#include "../src/queue/entity/summoner.hpp"
#include "../src/schools/school/ability/creature.hpp"
#include "../src/schools/schools.hpp"

class SummonerTest : public ::testing::Test {
  protected:
    SummonerTest() : creature(nullptr), ability(nullptr), schools(), school_id(0) {} // Initialize school_id

    void
    SetUp() override {
        creature = new Creature("TestCreature", 5);
        ability = new Ability("TestAbility", creature);
        School test_school("TestSchool");
        school_id = test_school.get_id(); // Get the school ID before adding
        schools.add_school(std::move(test_school));
    }

    void
    TearDown() override {
        delete creature;
        delete ability;
    }

    Creature* creature;
    Ability* ability;
    Schools schools;
    size_t school_id; // Store school ID
    const size_t default_max_energy{100};
    const size_t default_accum_index{10};
};

// Test constructor and basic getters
TEST_F(SummonerTest, ConstructorAndGetters) {
    Summoner summoner(*ability, default_max_energy, schools);

    EXPECT_EQ(summoner.get_energy(), default_max_energy);
    EXPECT_EQ(summoner.get_max_energy(), default_max_energy);
    EXPECT_EQ(summoner.get_experience(), 0);
    EXPECT_EQ(summoner.get_accum_index(), 1);
    EXPECT_EQ(summoner.get_school_level(school_id), 1); // Use stored school_id
}

// Test energy management
TEST_F(SummonerTest, EnergyManagement) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Test spending energy
    summoner.spend_energy(50);
    EXPECT_EQ(summoner.get_energy(), 50);

    // Test energy accumulation
    summoner.accum_energy();
    EXPECT_EQ(summoner.get_energy(), 51); // Default accum_index is 1

    // Test reset energy
    summoner.reset_energy();
    EXPECT_EQ(summoner.get_energy(), default_max_energy);
}

// Test experience system
TEST_F(SummonerTest, ExperienceSystem) {
    Summoner summoner(*ability, default_max_energy, schools);

    summoner.add_experience(100);
    EXPECT_EQ(summoner.get_experience(), 100);

    EXPECT_TRUE(summoner.can_level_up(school_id, 50)); // Use stored school_id
    EXPECT_FALSE(summoner.can_level_up(school_id, 150));

    summoner.upgrade(school_id); // Use stored school_id
    EXPECT_EQ(summoner.get_school_level(school_id), 2);
}

// Test energy validation
TEST_F(SummonerTest, EnergyValidation) {
    EXPECT_THROW(Summoner(*ability, 0, schools), std::invalid_argument);

    Summoner summoner(*ability, default_max_energy, schools);
    EXPECT_TRUE(summoner.has_enough_energy(50));
    EXPECT_FALSE(summoner.has_enough_energy(150));

    EXPECT_THROW(summoner.spend_energy(150), std::runtime_error);
}

// Test accumulation mechanics
TEST_F(SummonerTest, AccumulationMechanics) {
    Summoner summoner(*ability, default_max_energy, schools, default_accum_index);

    summoner.spend_energy(80);
    EXPECT_EQ(summoner.get_energy(), 20);

    summoner.accum_energy();
    EXPECT_EQ(summoner.get_energy(), 30); // 20 + 10(accum_index)

    // Test accumulation doesn't exceed max_energy
    summoner.reset_energy();
    summoner.accum_energy();
    EXPECT_EQ(summoner.get_energy(), default_max_energy);
}

// Test invalid school upgrade
TEST_F(SummonerTest, InvalidSchoolUpgrade) {
    Summoner summoner(*ability, default_max_energy, schools);

    EXPECT_THROW(summoner.upgrade(999), std::invalid_argument); // Non-existent school
    EXPECT_EQ(summoner.get_school_level(999), 0);               // Invalid school returns 0
}

// Test move constructor
TEST_F(SummonerTest, MoveConstructor) {
    Summoner original(*ability, default_max_energy, schools);
    original.add_experience(100);
    original.spend_energy(30);

    Summoner moved(std::move(original));

    EXPECT_EQ(moved.get_energy(), 70);
    EXPECT_EQ(moved.get_experience(), 100);
    EXPECT_EQ(moved.get_school_level(school_id), 1);
}

// Test experience edge cases
TEST_F(SummonerTest, ExperienceEdgeCases) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Adding zero experience
    summoner.add_experience(0);
    EXPECT_EQ(summoner.get_experience(), 0);

    // Adding normal experience
    summoner.add_experience(50);
    EXPECT_EQ(summoner.get_experience(), 50);

    // Adding more experience
    summoner.add_experience(25);
    EXPECT_EQ(summoner.get_experience(), 75);

    // Test overflow protection
    summoner.add_experience(SIZE_MAX - 50); // Try to get close to SIZE_MAX
    EXPECT_EQ(summoner.get_experience(), SIZE_MAX);

    // Try to add more after reaching SIZE_MAX
    summoner.add_experience(100);
    EXPECT_EQ(summoner.get_experience(), SIZE_MAX);
}

// Test complex energy scenarios
TEST_F(SummonerTest, ComplexEnergyScenarios) {
    Summoner summoner(*ability, default_max_energy, schools, 10);

    // Multiple energy operations
    summoner.spend_energy(30); // 100 -> 70
    summoner.accum_energy();   // 70 -> 80
    summoner.spend_energy(50); // 80 -> 30
    summoner.accum_energy();   // 30 -> 40
    EXPECT_EQ(summoner.get_energy(), 40);

    // Test accumulation near max_energy
    summoner.reset_energy();  // -> 100
    summoner.spend_energy(5); // 100 -> 95
    summoner.accum_energy();  // Should stay at 100
    EXPECT_EQ(summoner.get_energy(), 100);
}

// Test multiple school levels
TEST_F(SummonerTest, MultipleSchoolLevels) {
    // Add another school
    School second_school("SecondSchool");
    size_t second_school_id = second_school.get_id();
    schools.add_school(std::move(second_school));

    Summoner summoner(*ability, default_max_energy, schools);

    // Check initial levels
    EXPECT_EQ(summoner.get_school_level(school_id), 1);
    EXPECT_EQ(summoner.get_school_level(second_school_id), 1);

    // Upgrade first school
    summoner.add_experience(100);
    summoner.upgrade(school_id);
    EXPECT_EQ(summoner.get_school_level(school_id), 2);
    EXPECT_EQ(summoner.get_school_level(second_school_id), 1);
}

// Test energy overflow prevention
TEST_F(SummonerTest, EnergyOverflowPrevention) {
    Summoner summoner(*ability, default_max_energy, schools, SIZE_MAX);

    summoner.spend_energy(50); // 100 -> 50
    summoner.accum_energy();   // Should handle potential overflow
    EXPECT_EQ(summoner.get_energy(), default_max_energy);
}

// Test complex level up scenarios
TEST_F(SummonerTest, ComplexLevelUpScenarios) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Test multiple upgrades
    summoner.add_experience(300);
    summoner.upgrade(school_id);
    summoner.upgrade(school_id);
    summoner.upgrade(school_id);
    EXPECT_EQ(summoner.get_school_level(school_id), 4);

    // Test can_level_up after multiple upgrades
    EXPECT_TRUE(summoner.can_level_up(school_id, 200));
    EXPECT_FALSE(summoner.can_level_up(school_id, 400));
}

// Test levels map consistency
TEST_F(SummonerTest, LevelsMapConsistency) {
    Summoner summoner(*ability, default_max_energy, schools);

    const auto& levels = summoner.get_level();
    EXPECT_EQ(levels.size(), schools.count_schools());

    // Verify all schools are initialized with level 1
    for (const auto& [id, level] : levels) {
        EXPECT_EQ(level, 1);
    }
}

// Test copy constructor (should not compile)
TEST_F(SummonerTest, CopyConstructorDisabled) {
    Summoner summoner(*ability, default_max_energy, schools);
    // Следующая строка не должна компилироваться:
    // Summoner copy(summoner);
    SUCCEED();
}

// Test zero energy spending
TEST_F(SummonerTest, ZeroEnergySpending) {
    Summoner summoner(*ability, default_max_energy, schools);
    size_t initial_energy = summoner.get_energy();

    summoner.spend_energy(0);
    EXPECT_EQ(summoner.get_energy(), initial_energy);
}

// Test basic school level management
TEST_F(SummonerTest, SchoolLevelManagement) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Test non-existing school
    size_t invalid_school_id = 999;
    EXPECT_FALSE(summoner.can_level_up(invalid_school_id, 0));

    // Test with insufficient experience
    EXPECT_FALSE(summoner.can_level_up(school_id, 150));

    // Test with sufficient experience
    summoner.add_experience(200);
    EXPECT_TRUE(summoner.can_level_up(school_id, 150));

    // Test multiple level ups
    for (size_t i = 0; i < 5; ++i) {
        size_t current_level = summoner.get_school_level(school_id);
        summoner.upgrade(school_id);
        EXPECT_EQ(summoner.get_school_level(school_id), current_level + 1);
    }
}

// Test maximum school level
TEST_F(SummonerTest, MaximumSchoolLevel) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Set experience high enough for multiple upgrades
    summoner.add_experience(SIZE_MAX);

    // Test level up to a reasonable high value
    const size_t test_upgrades = 1000;
    for (size_t i = 0; i < test_upgrades; ++i) {
        size_t before_level = summoner.get_school_level(school_id);
        summoner.upgrade(school_id);
        size_t after_level = summoner.get_school_level(school_id);

        // Проверяем, что ур��вень увеличился на 1
        EXPECT_EQ(after_level, before_level + 1);
    }

    // Проверяем, что уровень успешно увеличился
    EXPECT_EQ(summoner.get_school_level(school_id), test_upgrades + 1);

    // Проверяем, что можем продолжать повышать уровень
    summoner.upgrade(school_id);
    EXPECT_EQ(summoner.get_school_level(school_id), test_upgrades + 2);
}

// Test constructor validation
TEST_F(SummonerTest, ConstructorValidation) {
    // Test zero max_energy
    EXPECT_THROW(Summoner(*ability, 0, schools), std::invalid_argument);

    // Test zero accum_index
    EXPECT_THROW(Summoner(*ability, default_max_energy, schools, 0), std::invalid_argument);

    // Test valid parameters
    EXPECT_NO_THROW(Summoner(*ability, default_max_energy, schools, 1));
}

// Test edge cases for accumulation index
TEST_F(SummonerTest, AccumulationIndexEdgeCases) {
    // Test with minimum valid accum_index
    Summoner summoner1(*ability, default_max_energy, schools, 1);
    EXPECT_EQ(summoner1.get_accum_index(), 1);

    // Test with large accum_index
    Summoner summoner2(*ability, default_max_energy, schools, SIZE_MAX / 2);
    summoner2.spend_energy(summoner2.get_max_energy() - 1);
    summoner2.accum_energy();
    EXPECT_EQ(summoner2.get_energy(), summoner2.get_max_energy());

    // Test accumulation with near-max energy
    Summoner summoner3(*ability, SIZE_MAX - 10, schools, 20);
    summoner3.spend_energy(15);
    summoner3.accum_energy();
    EXPECT_EQ(summoner3.get_energy(), SIZE_MAX - 10); // Should not overflow
}

// Test complex experience and level up scenarios
TEST_F(SummonerTest, ComplexExperienceAndLevelUp) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Test experience near SIZE_MAX
    summoner.add_experience(SIZE_MAX - 10);
    summoner.add_experience(5);
    EXPECT_EQ(summoner.get_experience(), SIZE_MAX - 5);
    summoner.add_experience(10); // Should cap at SIZE_MAX
    EXPECT_EQ(summoner.get_experience(), SIZE_MAX);

    // Test multiple school upgrades with max experience
    for (size_t i = 0; i < 100; ++i) {
        size_t current = summoner.get_school_level(school_id);
        summoner.upgrade(school_id);
        EXPECT_EQ(summoner.get_school_level(school_id), current + 1);
        EXPECT_TRUE(summoner.can_level_up(school_id, SIZE_MAX - 1));
    }
}

// Test energy management edge cases
TEST_F(SummonerTest, EnergyManagementEdgeCases) {
    // Test with minimum valid energy
    Summoner summoner1(*ability, 1, schools);
    summoner1.spend_energy(1);
    EXPECT_EQ(summoner1.get_energy(), 0);
    summoner1.accum_energy();
    EXPECT_EQ(summoner1.get_energy(), 1);

    // Test energy accumulation with large values
    const size_t large_energy = 1000000;
    const size_t accum_rate = 1000; // Явно задаем индекс накопления
    Summoner summoner2(*ability, large_energy, schools, accum_rate);

    // Тратим почти всю энергию
    summoner2.spend_energy(large_energy - accum_rate);
    EXPECT_EQ(summoner2.get_energy(), accum_rate);

    // Проверяем накопление
    summoner2.accum_energy();
    EXPECT_EQ(summoner2.get_energy(), accum_rate * 2);

    // Тест быстрых изменений энергии
    Summoner summoner3(*ability, 100, schools, 10);
    for (size_t i = 0; i < 10; ++i) {
        summoner3.spend_energy(5);
        summoner3.accum_energy();
        summoner3.spend_energy(3);
        summoner3.reset_energy();
    }
    EXPECT_EQ(summoner3.get_energy(), 100);
}

// Test multi-school level management
TEST_F(SummonerTest, MultiSchoolLevelManagement) {
    // Setup multiple schools
    std::vector<size_t> school_ids;
    for (size_t i = 0; i < 5; ++i) {
        School school("School" + std::to_string(i));
        school_ids.push_back(school.get_id());
        schools.add_school(std::move(school));
    }

    Summoner summoner(*ability, default_max_energy, schools);
    summoner.add_experience(1000);

    // Test upgrading multiple schools alternately
    for (size_t i = 0; i < 10; ++i) {
        for (size_t id : school_ids) {
            size_t current = summoner.get_school_level(id);
            summoner.upgrade(id);
            EXPECT_EQ(summoner.get_school_level(id), current + 1);
        }
    }

    // Verify levels are independent
    for (size_t i = 1; i < school_ids.size(); ++i) {
        EXPECT_EQ(summoner.get_school_level(school_ids[i]), summoner.get_school_level(school_ids[i - 1]));
    }
}

// Test concurrent energy and experience management
TEST_F(SummonerTest, ConcurrentEnergyAndExperience) {
    Summoner summoner(*ability, default_max_energy, schools);

    // Simulate complex gameplay scenario
    for (size_t i = 0; i < 100; ++i) {
        // Spend energy
        if (summoner.has_enough_energy(10)) {
            summoner.spend_energy(10);
            summoner.add_experience(5);
        }

        // Accumulate energy
        summoner.accum_energy();

        // Try to level up if possible
        if (summoner.can_level_up(school_id, i * 5)) {
            summoner.upgrade(school_id);
        }
    }

    // Verify final state
    EXPECT_GT(summoner.get_experience(), 0);
    EXPECT_GT(summoner.get_school_level(school_id), 1);
    EXPECT_LE(summoner.get_energy(), summoner.get_max_energy());
}
