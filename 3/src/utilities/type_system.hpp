#ifndef TYPE_SYSTEM_HPP
#define TYPE_SYSTEM_HPP

#include <bitset>
#include <cstdint>
#include <utility>
#include <vector>

/**
 * @brief Types of effects that can be applied to troops
 */
enum class EffectType : size_t { DAMAGE = 0, SPEED = 1, RANGE = 2, HEALTH = 3, NONE };

/**
 * @brief Types of troops in the game
 */
enum class TroopType : size_t { SUMMONER = 0, MORAL = 1, AMORAL = 2 };

/**
 * @brief System for managing troop types and their effects using bit encoding
 */
class TypeSystem {
  private:
    static constexpr size_t DIGITS_PER_EFFECT = 2;
    static constexpr size_t MAX_EFFECTS = 4;
    static constexpr size_t TROOP_TYPE_OFFSET = 0;
    static constexpr size_t EFFECT_OFFSET = 2; // Effects start after troop type

  public:
    /**
     * @brief Sets an effect for a troop
     * @param encoded Reference to the encoded value storing troop information
     * @param type Type of effect to set
     * @param hasEffect Whether the effect is present
     * @param isPositive Whether the effect is positive or negative
     */
    static void
    setEffect(size_t& encoded, EffectType type, bool hasEffect, bool isPositive) {
        size_t pos = EFFECT_OFFSET + static_cast<size_t>(type) * DIGITS_PER_EFFECT;
        encoded &= ~(0b11 << pos);

        if (hasEffect) {
            encoded |= (1 << pos);
            if (isPositive) {
                encoded |= (1 << (pos + 1));
            }
        }
    }

    /**
     * @brief Checks if a troop has a specific effect
     * @param encoded The encoded value storing troop information
     * @param type Type of effect to check
     * @return True if the troop has the effect, false otherwise
     */
    static bool
    hasEffect(size_t encoded, EffectType type) {
        size_t pos = EFFECT_OFFSET + static_cast<size_t>(type) * DIGITS_PER_EFFECT;
        return (encoded >> pos) & 1;
    }

    /**
     * @brief Checks if an effect is positive
     * @param encoded The encoded value storing troop information
     * @param type Type of effect to check
     * @return True if the effect is positive, false if negative
     */
    static bool
    isPositive(size_t encoded, EffectType type) {
        size_t pos = EFFECT_OFFSET + static_cast<size_t>(type) * DIGITS_PER_EFFECT;
        return (encoded >> (pos + 1)) & 1;
    }

    /**
     * @brief Sets the troop type
     * @param encoded Reference to the encoded value storing troop information
     * @param type Type of troop to set
     */
    static void
    setTroopType(size_t& encoded, TroopType type) {
        encoded &= ~(0b11 << TROOP_TYPE_OFFSET); // Clear first 2 bits
        encoded |= static_cast<size_t>(type) << TROOP_TYPE_OFFSET;
    }

    /**
     * @brief Gets the troop type from encoded value
     * @param encoded The encoded value storing troop information
     * @return The type of the troop
     */
    static TroopType
    getTroopType(size_t encoded) {
        return static_cast<TroopType>((encoded >> TROOP_TYPE_OFFSET) & 0b11);
    }

    /**
     * @brief Gets all active effects and their types
     * @param encoded The encoded value storing troop information
     * @return Vector of pairs containing effect type and whether it's positive
     */
    static std::vector<std::pair<EffectType, bool>>
    get_effects(size_t encoded) {
        std::vector<std::pair<EffectType, bool>> active_effects;

        for (size_t i = 0; i < MAX_EFFECTS; ++i) {
            auto type = static_cast<EffectType>(i);
            if (hasEffect(encoded, type)) {
                active_effects.emplace_back(type, isPositive(encoded, type));
            }
        }

        return active_effects;
    }
};

#endif // TYPE_SYSTEM_HPP