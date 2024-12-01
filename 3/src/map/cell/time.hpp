#ifndef TIME_HPP
#define TIME_HPP

#include <cstddef>

class Time {
private:
    size_t time;

public:
    size_t get_time() const { return time; }
    void set_time(size_t new_time) { time = new_time; }
};

#endif // TIME_HPP
