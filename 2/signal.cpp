#include "signal.hpp"

#include <limits>
#include <regex>

Signal::Signal(int level, int duration) {
    set_level(level);
    set_duration(duration);
}

void
Signal::set_duration(int duration) {
    Signal::valid_duration(duration);
    duration_ = duration;
}

void
Signal::set_level(int level) {
    Signal::valid_level(level);
    level_ = level;
}

void
Signal::valid_duration(int duration) {
    if (duration < 0) {
        throw std::invalid_argument("Duration must be a positive integer.");
    }
}

void
Signal::valid_level(int level) {
    if (level != 0 && level != 1) {
        throw std::invalid_argument("Level must be either 0 or 1.");
    }
}

int
Signal::get_duration() const {
    return duration_;
}

int
Signal::get_level() const {
    return level_;
}

Signal::Signal(const std::string& str) {
    std::regex pattern("^(0+|1+)\\d*");
    std::smatch matches;
    std::string result;
    if (std::regex_match(str, matches, pattern)) {
        result = matches[0];
        set_duration(result.length());
        set_level(std::stoi(result.substr(0, 1)));
    } else {
        throw std::invalid_argument("Invalid input string: " + result);
    }
}

void
Signal::inversion() {
    level_ = (level_ == 0) ? 1 : 0;
}

void
Signal::increase(int value) {
    if (value < 0) {
        throw std::invalid_argument("Increase value must be a positive integer.");
    }
    if (duration_ > std::numeric_limits<int>::max() - value) {
        throw std::overflow_error("Result of addition would overflow.");
    }
    duration_ += value;
}

void
Signal::decrease(int value) {
    if (value < 0) {
        throw std::invalid_argument("Decrease value must be a positive integer.");
    }
    if (duration_ < value) {
        throw std::underflow_error("Result of subtraction would underflow.");
    }
    duration_ -= value;
}