#ifndef TIME_HPP
#define TIME_HPP

#include <cstddef>

class EffectCellSpeedBuilder;
class EffectCellRangeBuilder;
class EffectCellHPBuilder;
class EffectCellDamageBuilder;

class Time {
  private:
    size_t time;

    friend class EffectCellSpeedBuilder;
    friend class EffectCellRangeBuilder;
    friend class EffectCellHPBuilder;
    friend class EffectCellDamageBuilder;

  public:
    explicit Time(size_t t) : time(t) {}

    inline size_t
    get_time() const {
        return time;
    }

    inline void
    set_time(size_t new_time) {
        time = new_time;
    }

    inline void
    decrease_time() {
        if (time > 0) {
            time--;
        }
    }

    inline bool
    is_not_zero() const {
        return time > 0;
    }
};

#endif // TIME_HPP
