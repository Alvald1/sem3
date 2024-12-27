#include <gtest/gtest.h>
#include "../src/utilities/type_system.hpp"

class TypeSystemTest : public ::testing::Test {
  protected:
    size_t encoded = 0;
};

TEST_F(TypeSystemTest, SetAndGetTroopType) {
    TypeSystem::setTroopType(encoded, TroopType::SUMMONER);
    EXPECT_EQ(TypeSystem::getTroopType(encoded), TroopType::SUMMONER);

    TypeSystem::setTroopType(encoded, TroopType::MORAL);
    EXPECT_EQ(TypeSystem::getTroopType(encoded), TroopType::MORAL);
}

TEST_F(TypeSystemTest, SetAndGetEffect) {
    TypeSystem::setEffect(encoded, EffectType::DAMAGE, true, true);
    EXPECT_TRUE(TypeSystem::hasEffect(encoded, EffectType::DAMAGE));
    EXPECT_TRUE(TypeSystem::isPositive(encoded, EffectType::DAMAGE));

    TypeSystem::setEffect(encoded, EffectType::SPEED, true, false);
    EXPECT_TRUE(TypeSystem::hasEffect(encoded, EffectType::SPEED));
    EXPECT_FALSE(TypeSystem::isPositive(encoded, EffectType::SPEED));
}

TEST_F(TypeSystemTest, GetEffects) {
    TypeSystem::setEffect(encoded, EffectType::DAMAGE, true, true);
    TypeSystem::setEffect(encoded, EffectType::HEALTH, true, false);

    auto effects = TypeSystem::get_effects(encoded);
    EXPECT_EQ(effects.size(), 2);

    EXPECT_EQ(effects[0].first, EffectType::DAMAGE);
    EXPECT_TRUE(effects[0].second);

    EXPECT_EQ(effects[1].first, EffectType::HEALTH);
    EXPECT_FALSE(effects[1].second);
}

TEST_F(TypeSystemTest, NoEffects) {
    auto effects = TypeSystem::get_effects(encoded);
    EXPECT_TRUE(effects.empty());
}
