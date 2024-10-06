#include "complex_signal.hpp"

#include <algorithm>
#include <regex>

Complex_Signal::Complex_Signal(int level, int duration) {
    Signal signal(level, duration);
    signals.resize(1);
    signals.buffer[signals.size_++] = signal;
}

Complex_Signal::Complex_Signal(const std::string& str) {
    std::regex re("(1+|0+)");
    std::smatch match;
    if (std::regex_search(str, match, std::regex("^[01]+"))) {
        std::string valid_part = match.str();
        std::sregex_iterator search_begin(valid_part.begin(), valid_part.end(), re);
        std::sregex_iterator search_end;
        int len = std::distance(search_begin, search_end);
        if (len == 0) {
            throw std::invalid_argument("Invalid input string: " + str);
        }
        signals.resize(len);
        for (auto it = search_begin; it != search_end; ++it) {
            std::string match_str = it->str();
            Signal signal(std::stoi(match_str.substr(0, 1)), match_str.length());
            signals.buffer[signals.size_++] = signal;
        }
    } else {
        throw std::invalid_argument("Invalid input string: " + str);
    }
}
