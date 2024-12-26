#ifndef TYPE_SYSTEM_HPP
#define TYPE_SYSTEM_HPP

#include <cstdint>
#include <utility>
#include <vector>

enum class EffectType : uint8_t { DAMAGE = 0, SPEED = 1, RANGE = 2, HEALTH = 3, NONE };
enum class TroopType : uint8_t { SUMMONER = 0, MORAL = 1, AMORAL = 2 };

class TypeSystem {
  private:
    static constexpr uint8_t DIGITS_PER_EFFECT = 2;
    static constexpr uint8_t MAX_EFFECTS = 4;

  public:
    static void
    setEffect(uint8_t& encoded, EffectType type, bool hasEffect, bool isPositive) {
        uint8_t pos = static_cast<uint8_t>(type) * DIGITS_PER_EFFECT;
        encoded &= ~(0b11 << pos);

        if (hasEffect) {
            encoded |= (1 << pos);
            if (isPositive) {
                encoded |= (1 << (pos + 1));
            }
        }
    }

    static bool
    hasEffect(uint8_t encoded, EffectType type) {
        uint8_t pos = static_cast<uint8_t>(type) * DIGITS_PER_EFFECT;
        return (encoded >> pos) & 1;
    }

    static bool
    isPositive(uint8_t encoded, EffectType type) {
        uint8_t pos = static_cast<uint8_t>(type) * DIGITS_PER_EFFECT;
        return (encoded >> (pos + 1)) & 1;
    }

    static void
    setTroopType(uint8_t& encoded, TroopType type) {
        encoded &= 0b00111111;
        encoded |= (static_cast<uint8_t>(type) << 6);
    }

    static TroopType
    getTroopType(uint8_t encoded) {
        return static_cast<TroopType>(encoded >> 6);
    }

    static std::vector<std::pair<EffectType, bool>>
    get_effects(uint8_t encoded) {
        std::vector<std::pair<EffectType, bool>> active_effects;

        for (uint8_t i = 0; i < MAX_EFFECTS; ++i) {
            auto type = static_cast<EffectType>(i);
            if (hasEffect(encoded, type)) {
                active_effects.emplace_back(type, isPositive(encoded, type));
            }
        }

        return active_effects;
    }
};

#endif // TYPE_SYSTEM_HPP