#ifndef MORAL_TROOP_HPP
#define MORAL_TROOP_HPP

#include "base_troop.hpp"
#include "i_moral.hpp"

class MoralTroop : public BaseTroop, public IMoral {
  private:
    int moral;

  public:
    explicit MoralTroop(const Ability& ability, int moral = 0) : BaseTroop(ability), moral(moral) {}

    // IMoral interface implementation
    inline void
    increase_morale() override {
        ++moral;
    }

    inline void
    decrease_morale() override {
        --moral;
    }

    void
    balance_morale() override {
        if (moral > 0) {
            --moral;
        } else if (moral < 0) {
            ++moral;
        }
    }

    // Getter and setter for moral
    [[nodiscard]] inline int
    get_moral() const noexcept {
        return moral;
    }

    inline void
    set_moral(int new_moral) noexcept {
        moral = new_moral;
    }
};

#endif // MORAL_TROOP_HPP
