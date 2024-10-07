#include "complex_signal.hpp"

#include <algorithm>
#include <regex>

Complex_Signal::Complex_Signal(int level, int duration) {
    Signal signal(level, duration);
    signals.resize(1);
    signals.buffer_[signals.size_].signal = signal;
    signals.buffer_[signals.size_++].time = duration;
}

Complex_Signal::Complex_Signal(const std::string& str) {
    std::regex re("(1+|0+)");
    std::smatch match;
    if (std::regex_search(str, match, std::regex("^[01]+"))) {
        std::string valid_part = match.str();
        std::sregex_iterator search_begin(valid_part.begin(), valid_part.end(), re);
        std::sregex_iterator search_end;
        int len = std::distance(search_begin, search_end);
        signals.resize(len);
        signals.buffer_->time = 0;
        for (auto it = search_begin; it != search_end; ++it) {
            std::string match_str = it->str();
            Signal signal(std::stoi(match_str.substr(0, 1)), match_str.length());
            signals.buffer_[signals.size_].signal = signal;
            signals.buffer_[signals.size_++].time = signal.get_duration() + signals.buffer_[signals.size_ - 1].time;
        }
    } else {
        throw std::invalid_argument("Invalid input string: " + str);
    }
}

Complex_Signal::Complex_Signal(const Complex_Signal& other) { signals = Allocator(other.signals); }

Complex_Signal::Complex_Signal(Complex_Signal&& other) noexcept { signals = Allocator(std::move(other.signals)); }

Complex_Signal&
Complex_Signal::operator=(const Complex_Signal& other) {
    signals = Allocator(other.signals);
    return *this;
}

Complex_Signal&
Complex_Signal::operator=(Complex_Signal&& other) noexcept {
    signals = Allocator(std::move(other.signals));
    return *this;
}

int
Complex_Signal::operator[](int position) const {
    if (position <= 0 || position > signals.buffer_[signals.size_ - 1].time) {
        throw std::invalid_argument("Invalid position: " + std::to_string(position));
    }
    int index = bin_search(position);
    return signals.buffer_[index].signal.get_level();
}

int
Complex_Signal::bin_search(int position) const {
    int R = signals.size_, L = 1, M;
    while (L < R) {
        M = L + (R - L) / 2;
        if (signals.buffer_[M].time < position) {
            L = M + 1;
        } else {
            R = M;
        }
    }
    return L;
}

void
Complex_Signal::inverstion() {
    std::for_each(signals.buffer_, signals.buffer_ + signals.size_, [](Signals& signal) { signal.signal.inversion(); });
}

Complex_Signal&
Complex_Signal::operator~() {
    inverstion();
    return *this;
}

Complex_Signal&
Complex_Signal::operator+=(const Complex_Signal& other) {
    Complex_Signal new_signal;
    new_signal.signals.resize(signals.size_ + other.signals.size_);
    int duration = signals.buffer_[signals.size_ - 1].time;
    std::move(signals.buffer_, signals.buffer_ + signals.size_, new_signal.signals.buffer_);
    std::copy(other.signals.buffer_ + 1, other.signals.buffer_ + other.signals.size_,
              new_signal.signals.buffer_ + signals.size_);
    new_signal.signals.size_ = signals.size_ + other.signals.size_ - 1;
    std::for_each(new_signal.signals.buffer_ + signals.size_, new_signal.signals.buffer_ + new_signal.signals.size_,
                  [duration](Signals& signal) { signal.time += duration; });
    return *this = std::move(new_signal);
}