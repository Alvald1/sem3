#ifndef TIME_HPP
#define TIME_HPP

#include <cstddef>

class Time {
  private:
    size_t time;

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
