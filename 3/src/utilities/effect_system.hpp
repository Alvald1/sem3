#include <cstdint>
#include <utility>
#include <vector>

enum class EffectType : uint8_t { DAMAGE = 0, SPEED = 1, RANGE = 2, HEALTH = 3 };
enum class TroopType : uint8_t { SUMMONER = 0, MORAL = 1, AMORAL = 2 };

class TypeSystem {
  private:
    static constexpr uint8_t PRESENCE_MASK = 0x0F; // 0000 1111
    static constexpr uint8_t SIGN_MASK = 0xF0;     // 1111 0000
    static constexpr uint8_t SIGN_SHIFT = 4;
    static constexpr uint8_t TROOP_TYPE_MASK = 0xC0; // 1100 0000
    static constexpr uint8_t TROOP_TYPE_SHIFT = 6;

  public:
    static void
    setEffect(uint8_t& encoded, EffectType type, bool hasEffect, bool isPositive) {
        uint8_t effectBit = 1 << static_cast<uint8_t>(type);
        uint8_t signBit = 1 << (static_cast<uint8_t>(type) + SIGN_SHIFT);

        if (hasEffect) {
            encoded |= effectBit;
            if (isPositive) {
                encoded |= signBit;
            } else {
                encoded &= ~signBit;
            }
        } else {
            encoded &= ~effectBit;
            encoded &= ~signBit;
        }
    }

    static bool
    hasEffect(uint8_t encoded, EffectType type) {
        return (encoded & (1 << static_cast<uint8_t>(type))) != 0;
    }

    static bool
    isPositive(uint8_t encoded, EffectType type) {
        return (encoded & (1 << (static_cast<uint8_t>(type) + SIGN_SHIFT))) != 0;
    }

    static void
    setTroopType(uint8_t& encoded, TroopType type) {
        encoded &= ~TROOP_TYPE_MASK; // Clear troop type bits
        encoded |= (static_cast<uint8_t>(type) << TROOP_TYPE_SHIFT);
    }

    static TroopType
    getTroopType(uint8_t encoded) {
        uint8_t typeValue = (encoded & TROOP_TYPE_MASK) >> TROOP_TYPE_SHIFT;
        return static_cast<TroopType>(typeValue);
    }

    static std::vector<std::pair<EffectType, bool>>
    get_effects(uint8_t encoded) {
        std::vector<std::pair<EffectType, bool>> active_effects;

        for (uint8_t i = 0; i <= static_cast<uint8_t>(EffectType::HEALTH); ++i) {
            EffectType type = static_cast<EffectType>(i);
            if (hasEffect(encoded, type)) {
                active_effects.emplace_back(type, isPositive(encoded, type));
            }
        }

        return std::move(active_effects);
    }
};