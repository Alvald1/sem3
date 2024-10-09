#include "complex_signal.hpp"

#include <algorithm>
#include <regex>

Complex_Signal::Complex_Signal(int level, int duration) {
    Signal signal(level, duration);
    signals.resize(1);
    signals.buffer_[0].time = duration;
    signals.buffer_[0].signal = signal;
    ++signals.size_;
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
        for (auto it = search_begin; it != search_end; ++it) {
            std::string match_str = it->str();
            Signal signal(match_str[0] - '0', match_str.length());
            signals.buffer_[signals.size_].signal = signal;
            if (signals.size_ == 0) {
                signals.buffer_[signals.size_].time = signal.get_duration();
            } else {
                signals.buffer_[signals.size_].time = signal.get_duration() + signals.buffer_[signals.size_ - 1].time;
            }
            ++signals.size_;
        }
    } else {
        throw std::invalid_argument("Invalid input string: " + str);
    }
}

int
Complex_Signal::operator[](int position) const {
    if (signals.size_ == 0 || position < 0 || position >= signals.buffer_[signals.size_ - 1].time) {
        throw std::out_of_range("Invalid position: " + std::to_string(position));
    }
    int index = bin_search(position + 1);
    return signals.buffer_[index].signal.get_level();
}

int
Complex_Signal::bin_search(int position) const {
    int R = signals.size_ - 1, L = 0, M;
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
    std::for_each(signals.buffer_, signals.buffer_ + signals.size_, [](Signals& sig) { sig.signal.inversion(); });
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
    std::copy(other.signals.buffer_, other.signals.buffer_ + other.signals.size_,
              new_signal.signals.buffer_ + signals.size_);
    new_signal.signals.size_ = signals.size_ + other.signals.size_;
    std::for_each(new_signal.signals.buffer_ + signals.size_, new_signal.signals.buffer_ + new_signal.signals.size_,
                  [duration](Signals& signal) { signal.time += duration; });
    return *this = std::move(new_signal);
}

void
Complex_Signal::insert(const Complex_Signal& other, int position) {
    if (position < 0 || position >= signals.buffer_[signals.size_ - 1].time) {
        throw std::out_of_range("Invalid position: " + std::to_string(position));
    }
    Complex_Signal tmp(other);
    int index = bin_search(position + 1);
    int flag = split(index, position, tmp.signals.size_);
    int duration{};
    std::copy(tmp.signals.buffer_, tmp.signals.buffer_ + tmp.signals.size_, signals.buffer_ + index + flag);
    signals.size_ += tmp.signals.size_ + flag;
    if (index == 0 && position != 0) {
        duration = signals.buffer_[0].time;
    } else if (index != 0) {
        duration = signals.buffer_[index - 1 + flag].time;
    }
    std::for_each(signals.buffer_ + index + flag, signals.buffer_ + index + flag + tmp.signals.size_,
                  [duration](Signals& signal) { signal.time += duration; });
    duration = tmp.signals.buffer_[tmp.signals.size_ - 1].time;
    int flag2 = flag == 1 ? -1 : 0;
    std::for_each(signals.buffer_ + index + tmp.signals.size_ + flag, signals.buffer_ + signals.size_ + flag + flag2,
                  [duration](Signals& signal) { signal.time += duration; });
}

int
Complex_Signal::split(int index, int position, int size) {
    if (index == 0 && position == 0 || index != 0 && position == signals.buffer_[index - 1].time) {
        signals.resize(size);
        std::move(signals.buffer_ + index, signals.buffer_ + signals.size_, signals.buffer_ + index + size);
        return 0;
    }
    int remains = index != 0 ? position - signals.buffer_[index - 1].time : position;
    int shift = signals.buffer_[index].signal.get_duration() - remains;
    signals.resize(size + 1);
    std::move(signals.buffer_ + index, signals.buffer_ + signals.size_, signals.buffer_ + index + size + 1);
    signals.buffer_[index].signal.set_duration(remains);
    signals.buffer_[index].time = position;
    signals.buffer_[index + size + 1].signal.set_duration(shift);
    return 1;
}