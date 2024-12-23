#include <gtest/gtest.h>
#include "queue/entity/entity.hpp"
#include "schools/school/ability/ability.hpp"
#include "schools/school/ability/creature.hpp"

class EntityTest : public ::testing::Test {
  protected:
    Creature mockCreature{"TestCreature", 0, 0, 0, 0, 5};
    Ability testAbility{"TestAbility", &mockCreature, 1, 10, 100, 50};
    Entity* entity{nullptr};

    void
    SetUp() override {
        entity = new Entity(testAbility);
    }

    void
    TearDown() override {
        delete entity;
    }
};

TEST_F(EntityTest, ConstructorTest) {
    EXPECT_EQ(entity->get_name(), "TestAbility");
    EXPECT_EQ(entity->get_initiative(), 5);
    EXPECT_EQ(entity->get_max_hp(), 50);
    EXPECT_EQ(entity->get_hp(), 50);
}

TEST_F(EntityTest, DamageTest) {
    // Нулевой урон
    entity->do_damage(0);
    EXPECT_EQ(entity->get_hp(), 50);

    // Об��чный урон
    entity->do_damage(20);
    EXPECT_EQ(entity->get_hp(), 30);

    // Урон равный текущему HP
    entity->do_damage(30);
    EXPECT_EQ(entity->get_hp(), 0);

    // Урон больше текущего HP
    entity->set_hp(20);
    entity->do_damage(100);
    EXPECT_EQ(entity->get_hp(), 0);

    // Урон по уже мертвому существу
    entity->do_damage(10);
    EXPECT_EQ(entity->get_hp(), 0);
}

TEST_F(EntityTest, HealTest) {
    // Нулевое лечение
    entity->do_damage(20);
    entity->heal(0);
    EXPECT_EQ(entity->get_hp(), 30);

    // Частичное лечение
    entity->heal(10);
    EXPECT_EQ(entity->get_hp(), 40);

    // Лечение до максимума
    entity->heal(10);
    EXPECT_EQ(entity->get_hp(), 50);

    // Лечение сверх максимума
    entity->heal(100);
    EXPECT_EQ(entity->get_hp(), 50);

    // Лечение мертвого существа
    entity->do_damage(50);
    EXPECT_EQ(entity->get_hp(), 0);
    entity->heal(25);
    EXPECT_EQ(entity->get_hp(), 25);
}

TEST_F(EntityTest, HealthPercentageTest) {
    // Полное здоровье
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 100.0);

    // 75% здоровья
    entity->do_damage(12);
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 76.0);

    // 50% здоровья
    entity->do_damage(13);
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 50.0);

    // 25% здоровья
    entity->do_damage(12);
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 26.0);

    // 0% здоровья
    entity->do_damage(13);
    EXPECT_DOUBLE_EQ(entity->get_health_percentage(), 0.0);
}

TEST_F(EntityTest, IsAliveTest) {
    EXPECT_TRUE(entity->is_alive());

    entity->do_damage(25);
    EXPECT_TRUE(entity->is_alive());

    entity->do_damage(25);
    EXPECT_FALSE(entity->is_alive());
}

TEST_F(EntityTest, ComparisonTest) {
    // Создаем существ с разной инициативой
    Creature fastCreature{"FastCreature", 0, 0, 0, 0, 10};
    Creature slowCreature{"SlowCreature", 0, 0, 0, 0, 1};

    Ability fastAbility("FastAbility", &fastCreature, 1, 10, 100, 30);
    Ability slowAbility("SlowAbility", &slowCreature, 1, 10, 100, 30);

    Entity fastEntity(fastAbility);
    Entity slowEntity(slowAbility);

    // Тест на строгое сравнение
    EXPECT_TRUE(slowEntity < fastEntity);
    EXPECT_TRUE(fastEntity > slowEntity);

    // Тест на равные значения инициативы
    Entity sameSpeedEntity(fastAbility);
    EXPECT_FALSE(fastEntity < sameSpeedEntity);
    EXPECT_FALSE(fastEntity > sameSpeedEntity);

    // Test equality operator
    Entity sameInitiativeEntity(fastAbility);
    EXPECT_TRUE(fastEntity == sameInitiativeEntity);
    EXPECT_FALSE(fastEntity == slowEntity);

    // Test less than or equal operator
    EXPECT_TRUE(slowEntity <= fastEntity);
    EXPECT_TRUE(sameInitiativeEntity <= fastEntity);
    EXPECT_FALSE(fastEntity <= slowEntity);

    // Test greater than or equal operator
    EXPECT_TRUE(fastEntity >= slowEntity);
    EXPECT_TRUE(sameInitiativeEntity >= fastEntity);
    EXPECT_FALSE(slowEntity >= fastEntity);
}

TEST_F(EntityTest, AdditionalComparisonOperatorsTest) {
    // Create entities with different initiatives
    Creature creature1{"Creature1", 0, 0, 0, 0, 5};
    Creature creature2{"Creature2", 0, 0, 0, 0, 5};
    Creature creature3{"Creature3", 0, 0, 0, 0, 10};

    Ability ability1("Ability1", &creature1, 1, 10, 100, 30);
    Ability ability2("Ability2", &creature2, 1, 10, 100, 30);
    Ability ability3("Ability3", &creature3, 1, 10, 100, 30);

    Entity entity1(ability1);
    Entity entity2(ability2);
    Entity entity3(ability3);

    // Test equality operator (==)
    EXPECT_TRUE(entity1 == entity2);  // Same initiative (5 == 5)
    EXPECT_FALSE(entity1 == entity3); // Different initiative (5 != 10)

    // Test less than or equal operator (<=)
    EXPECT_TRUE(entity1 <= entity2);  // Equal initiatives (5 <= 5)
    EXPECT_TRUE(entity1 <= entity3);  // Lower initiative (5 <= 10)
    EXPECT_FALSE(entity3 <= entity1); // Higher initiative (10 <= 5)

    // Test greater than or equal operator (>=)
    EXPECT_TRUE(entity1 >= entity2);  // Equal initiatives (5 >= 5)
    EXPECT_TRUE(entity3 >= entity1);  // Higher initiative (10 >= 5)
    EXPECT_FALSE(entity1 >= entity3); // Lower initiative (5 >= 10)
}

TEST_F(EntityTest, ComplexScenarioTest) {
    // Сценарий получения урона и лечения
    entity->do_damage(20); // 50 -> 30
    entity->heal(5);       // 30 -> 35
    entity->do_damage(15); // 35 -> 20
    entity->heal(40);      // 20 -> 50
    EXPECT_EQ(entity->get_hp(), 50);

    // Сценарий смерти и воскрешения
    entity->do_damage(50); // 50 -> 0
    EXPECT_FALSE(entity->is_alive());
    entity->heal(25); // 0 -> 25
    EXPECT_TRUE(entity->is_alive());

    // Проверка граничных значений HP
    entity->set_hp(1);
    EXPECT_TRUE(entity->is_alive());
    entity->do_damage(1);
    EXPECT_FALSE(entity->is_alive());
}

TEST_F(EntityTest, SetHPTest) {
    entity->set_hp(30);
    EXPECT_EQ(entity->get_hp(), 30);

    entity->set_hp(100);
    EXPECT_EQ(entity->get_hp(), 50); // Should not exceed max_hp
}
