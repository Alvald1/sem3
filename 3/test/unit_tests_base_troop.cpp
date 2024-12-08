#include <gtest/gtest.h>
#include "../src/queue/entity/troop/base_troop.hpp"

class BaseTroopTest : public ::testing::Test {
  protected:
    Creature* creature;
    Ability* ability;
    BaseTroop* troop;

    void
    SetUp() override {
        creature = new Creature("TestCreature", 5, 10, 2, 1, 3);
        ability = new Ability("TestAbility", creature, 1, 50, 100, 20);
        troop = new BaseTroop(*ability);
    }

    void
    TearDown() override {
        delete troop;
        delete ability;
        delete creature;
    }
};

TEST_F(BaseTroopTest, ConstructorTest) {
    EXPECT_EQ(troop->get_speed(), 5);
    EXPECT_EQ(troop->get_damage(), 10);
    EXPECT_EQ(troop->get_range(), 2);
    EXPECT_EQ(troop->get_type(), 1);
}

TEST_F(BaseTroopTest, SettersTest) {
    troop->set_speed(7);
    EXPECT_EQ(troop->get_speed(), 7);

    troop->set_damage(15);
    EXPECT_EQ(troop->get_damage(), 15);

    troop->set_range(3);
    EXPECT_EQ(troop->get_range(), 3);

    troop->set_type(2);
    EXPECT_EQ(troop->get_type(), 2);
}

TEST_F(BaseTroopTest, InheritanceTest) {
    EXPECT_EQ(troop->get_initiative(), 3);
    EXPECT_EQ(troop->get_hp(), 20);
    EXPECT_EQ(troop->get_max_hp(), 20);
    EXPECT_TRUE(troop->is_alive());
}

TEST_F(BaseTroopTest, MultipleInstancesTest) {
    Creature creature2("Creature2", 6, 12, 3, 2, 4);
    Ability ability2("Ability2", &creature2, 2, 60, 120, 30);
    BaseTroop troop2(ability2);

    EXPECT_NE(troop->get_id(), troop2.get_id());
    EXPECT_EQ(troop2.get_speed(), 6);
    EXPECT_EQ(troop2.get_damage(), 12);
    EXPECT_EQ(troop2.get_range(), 3);
    EXPECT_EQ(troop2.get_type(), 2);
}

TEST_F(BaseTroopTest, ZeroValuesTest) {
    Creature zeroCreature("ZeroCreature", 0, 0, 0, 0, 0);
    Ability zeroAbility("ZeroAbility", &zeroCreature, 0, 0, 0, 0);
    BaseTroop zeroTroop(zeroAbility);

    EXPECT_EQ(zeroTroop.get_speed(), 0);
    EXPECT_EQ(zeroTroop.get_damage(), 0);
    EXPECT_EQ(zeroTroop.get_range(), 0);
    EXPECT_EQ(zeroTroop.get_type(), 0);
}

TEST_F(BaseTroopTest, LargeValuesTest) {
    Creature largeCreature("LargeCreature", SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX);
    Ability largeAbility("LargeAbility", &largeCreature, 1, 50, 100, SIZE_MAX);
    BaseTroop largeTroop(largeAbility);

    EXPECT_EQ(largeTroop.get_speed(), SIZE_MAX);
    EXPECT_EQ(largeTroop.get_damage(), SIZE_MAX);
    EXPECT_EQ(largeTroop.get_range(), SIZE_MAX);
    EXPECT_EQ(largeTroop.get_type(), SIZE_MAX);
    EXPECT_EQ(largeTroop.get_hp(), SIZE_MAX);
}

TEST_F(BaseTroopTest, DamageAndHealingTest) {
    // Initial HP check
    EXPECT_EQ(troop->get_hp(), 20);
    // Damage tests
    troop->do_damage(5);
    EXPECT_EQ(troop->get_hp(), 15);

    // Overflow damage
    troop->do_damage(20);
    EXPECT_EQ(troop->get_hp(), 0);
    EXPECT_FALSE(troop->is_alive());

    // Healing tests
    troop->heal(10);
    EXPECT_EQ(troop->get_hp(), 10);

    // Overflow healing
    troop->heal(100);
    EXPECT_EQ(troop->get_hp(), 20); // Should not exceed max_hp
}

TEST_F(BaseTroopTest, HealthPercentageTest) {
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 100.0);

    troop->do_damage(10); // 50% damage
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 50.0);

    troop->do_damage(20); // Complete damage
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 0.0);

    troop->heal(5); // 25% heal
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 25.0);
}

TEST_F(BaseTroopTest, InitiativeComparisonTest) {
    Creature creature1("Creature1", 5, 10, 2, 1, 5);
    Creature creature2("Creature2", 5, 10, 2, 1, 3);
    Creature creature3("Creature3", 5, 10, 2, 1, 5);

    Ability ability1("Ability1", &creature1, 1, 50, 100, 20);
    Ability ability2("Ability2", &creature2, 1, 50, 100, 20);
    Ability ability3("Ability3", &creature3, 1, 50, 100, 20);

    BaseTroop troop1(ability1);
    BaseTroop troop2(ability2);
    BaseTroop troop3(ability3);

    EXPECT_TRUE(troop1 > troop2);  // Higher initiative
    EXPECT_FALSE(troop1 < troop2); // Higher initiative
    EXPECT_FALSE(troop1 < troop3); // Equal initiative
    EXPECT_FALSE(troop1 > troop3); // Equal initiative
}

TEST_F(BaseTroopTest, ConsecutiveDamageTest) {
    // Test multiple small damage instances
    for (size_t i = 0; i < 5; ++i) {
        troop->do_damage(1);
        EXPECT_EQ(troop->get_hp(), 20 - (i + 1));
    }

    // Test damage-heal-damage sequence
    troop->do_damage(5);
    EXPECT_EQ(troop->get_hp(), 10);
    troop->heal(2);
    EXPECT_EQ(troop->get_hp(), 12);
    troop->do_damage(3);
    EXPECT_EQ(troop->get_hp(), 9);
}

TEST_F(BaseTroopTest, EdgeCaseHealingTest) {
    // Heal at full health
    troop->heal(10);
    EXPECT_EQ(troop->get_hp(), 20);

    // Heal at zero health
    troop->do_damage(20);
    EXPECT_EQ(troop->get_hp(), 0);
    troop->heal(1);
    EXPECT_EQ(troop->get_hp(), 1);

    // Multiple small heals
    for (size_t i = 0; i < 5; ++i) {
        troop->heal(1);
        EXPECT_EQ(troop->get_hp(), std::min(size_t(2 + i), size_t(20)));
    }
}

TEST_F(BaseTroopTest, NegativeValuesTest) {
    size_t initial_hp = troop->get_hp();
    
    // Попытка нанести отрицательный урон не должна менять HP
    troop->do_damage(-5);
    EXPECT_EQ(troop->get_hp(), initial_hp);
    
    // Попытка отрицательного лечения не должна менять HP
    troop->heal(-10);
    EXPECT_EQ(troop->get_hp(), initial_hp);
}

TEST_F(BaseTroopTest, ZeroValueEffectsTest) {
    size_t initial_hp = troop->get_hp();
    
    // Урон в 0 единиц
    troop->do_damage(0);
    EXPECT_EQ(troop->get_hp(), initial_hp);
    
    // Лечение на 0 единиц
    troop->heal(0);
    EXPECT_EQ(troop->get_hp(), initial_hp);
}

TEST_F(BaseTroopTest, ZeroMaxHPTest) {
    Creature zeroHPCreature("ZeroHP", 1, 1, 1, 1, 1);
    Ability zeroHPAbility("ZeroAbility", &zeroHPCreature, 1, 0, 0, 0);
    BaseTroop zeroHPTroop(zeroHPAbility);
    
    EXPECT_EQ(zeroHPTroop.get_hp(), 0);
    EXPECT_EQ(zeroHPTroop.get_max_hp(), 0);
    EXPECT_FALSE(zeroHPTroop.is_alive());
    
    // Попытка лечения существа с нулевым максимальным здоровьем
    zeroHPTroop.heal(100);
    EXPECT_EQ(zeroHPTroop.get_hp(), 0);
}

TEST_F(BaseTroopTest, InitiativeEdgeCasesTest) {
    Creature maxInitCreature("MaxInit", 1, 1, 1, 1, SIZE_MAX);
    Ability maxInitAbility("MaxInitAbility", &maxInitCreature, 1, 50, 100, 20);
    BaseTroop maxInitTroop(maxInitAbility);
    
    Creature zeroInitCreature("ZeroInit", 1, 1, 1, 1, 0);
    Ability zeroInitAbility("ZeroInitAbility", &zeroInitCreature, 1, 50, 100, 20);
    BaseTroop zeroInitTroop(zeroInitAbility);
    
    EXPECT_TRUE(maxInitTroop > zeroInitTroop);
    EXPECT_TRUE(zeroInitTroop < maxInitTroop);
}

TEST_F(BaseTroopTest, RapidHealDamageTest) {
    // Быстрое чередование урона и лечения
    for(size_t i = 0; i < 1000; ++i) {
        troop->do_damage(1);
        troop->heal(1);
    }
    EXPECT_EQ(troop->get_hp(), troop->get_max_hp());
    
    // Быстрое нанесение большого количества минимального урона
    for(size_t i = 0; i < 1000; ++i) {
        troop->do_damage(1);
    }
    EXPECT_EQ(troop->get_hp(), 0);
}

TEST_F(BaseTroopTest, HealthPercentageEdgeCasesTest) {
    // Проверка процента здоровья при максимальном HP
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 100.0);
    
    // Проверка при HP = 1
    troop->do_damage(troop->get_hp() - 1);
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 100.0 / troop->get_max_hp());
    
    // Проверка при HP = 0
    troop->do_damage(1);
    EXPECT_DOUBLE_EQ(troop->get_health_percentage(), 0.0);
}
