/**
 * @file complex_signal.cpp
 * @brief Реализация класса Complex_Signal для работы с последовательностями сигналов.
 *
 * Класс Complex_Signal предоставляет методы для управления сложными сигналами,
 * включая их инверсию, вставку, форматированный вывод и бинарный поиск.
 */

#include "complex_signal.hpp"
#include <algorithm>
#include <regex>

/**
 * @brief Конструктор Complex_Signal, создающий сигнал с заданным уровнем и длительностью.
 *
 * @param level Уровень сигнала (0 или 1).
 * @param duration Длительность сигнала.
 */
Complex_Signal::Complex_Signal(int level, int duration) {
    Signal signal(level, duration);
    signals.resize(1);
    signals.buffer_[0].time = duration;
    signals.buffer_[0].signal = signal;
    ++signals.size_;
}

/**
 * @brief Конструктор Complex_Signal, создающий объект из строки сигнала.
 *
 * @param str Строка, содержащая последовательность сигналов из нулей и единиц.
 * @throws std::invalid_argument если строка содержит недопустимые символы.
 */
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

/**
 * @brief Оператор [] для получения уровня сигнала в заданной позиции.
 *
 * @param position Позиция сигнала.
 * @return Уровень сигнала (0 или 1).
 * @throws std::out_of_range если позиция недопустима.
 */
int
Complex_Signal::operator[](int position) const {
    if (signals.size_ == 0 || position < 0 || position >= signals.buffer_[signals.size_ - 1].time) {
        throw std::out_of_range("Invalid position: " + std::to_string(position));
    }
    int index = bin_search(position + 1);
    return signals.buffer_[index].signal.get_level();
}

/**
 * @brief Бинарный поиск позиции сигнала.
 *
 * @param position Позиция для поиска.
 * @return Индекс сигнала на данной позиции.
 */
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

/**
 * @brief Инвертирует все сигналы в Complex_Signal.
 */
void
Complex_Signal::inverstion() {
    std::for_each(signals.buffer_, signals.buffer_ + signals.size_, [](Signals& sig) { sig.signal.inversion(); });
}

/**
 * @brief Оператор инверсии ~ для инверсии всех сигналов.
 * 
 * @return Ссылка на инвертированный Complex_Signal.
 */
Complex_Signal&
Complex_Signal::operator~() {
    inverstion();
    return *this;
}

/**
 * @brief Оператор += для добавления другого Complex_Signal к текущему.
 * 
 * @param other Другой Complex_Signal для добавления.
 * @return Ссылка на текущий объект после добавления.
 */
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

/**
 * @brief Вставляет другой Complex_Signal в текущий объект на указанную позицию.
 *
 * @param other Complex_Signal для вставки.
 * @param position Позиция вставки.
 * @throws std::out_of_range если позиция недопустима.
 */
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

/**
 * @brief Делит сигнал на части в массиве на основе позиции и размера.
 *
 * @param index Индекс сигнала для разделения.
 * @param position Позиция в сигнале для разделения.
 * @param size Размер сигнала после разделения.
 * @return Новый индекс после разделения.
 */
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

/**
 * @brief Оператор * для многократного умножения сигнала.
 *
 * @param multiplier Количество копий сигнала.
 * @return Новый Complex_Signal с повторенными сигналами.
 * @throws std::invalid_argument если multiplier отрицателен.
 */
Complex_Signal
Complex_Signal::operator*(int multiplier) {
    if (multiplier < 0) {
        throw std::invalid_argument("Multiply value must be a non-negative integer");
    }
    Complex_Signal tmp(*this);
    std::for_each_n(tmp.signals.buffer_, tmp.signals.size_, [multiplier](Signals& sig) {
        sig.signal.set_duration(sig.signal.get_duration() * multiplier);
        sig.time *= multiplier;
    });
    return std::move(tmp);
}

/**
 * @brief Форматированный вывод Complex_Signal в выходной поток.
 *
 * @param out Поток для вывода.
 */
void
Complex_Signal::format_print(std::wostream& out) const {
    int last_level = -1;
    std::for_each_n(signals.buffer_, signals.size_, [&out, &last_level](Signals& sig) {
        switch (last_level) {
            case -1: break;
            case 0: out << L'/'; break;
            case 1: out << L'\\'; break;
        }
        last_level = sig.signal.get_level();
        sig.signal.format_print(out);
    });
}

/**
 * @brief Оператор вывода для Complex_Signal.
 */
std::wostream&
operator<<(std::wostream& out, const Complex_Signal& signals) {
    signals.format_print(out);
    return out;
}

/**
 * @brief Оператор ввода для Complex_Signal.
 */
std::istream&
operator>>(std::istream& in, Complex_Signal& signals) {
    std::string str;
    in >> str;
    signals = Complex_Signal(str);
    return in;
}
