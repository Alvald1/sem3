/**
 * @file signal.cpp
 * @brief Реализация класса Signal, включающая методы для работы с уровнями и продолжительностью сигналов.
 */

#include "signal.hpp"
#include <limits>
#include <regex>

/**
 * @brief Конструктор Signal, инициализирующий объект с заданным уровнем и длительностью.
 * 
 * @param level Уровень сигнала (0 или 1).
 * @param duration Длительность сигнала (положительное целое число).
 * 
 * @throws std::invalid_argument Если level не равен 0 или 1, либо если duration отрицателен.
 */
Signal::Signal(int level, int duration) {
    set_level(level);
    set_duration(duration);
}

/**
 * @brief Конструктор Signal, инициализирующий объект из строки.
 * 
 * @param str Строка, содержащая последовательность нулей и единиц.
 * 
 * @throws std::invalid_argument Если строка не соответствует допустимому формату.
 */
Signal::Signal(const std::string& str) {
    std::regex pattern("^(0+|1+).*");
    std::smatch matches;
    std::string result;
    if (std::regex_match(str, matches, pattern)) {
        result = matches[1];
        set_duration(result.length());
        set_level(std::stoi(result.substr(0, 1)));
    } else {
        throw std::invalid_argument("Invalid input string: " + str);
    }
}

/**
 * @brief Устанавливает длительность сигнала.
 * 
 * @param duration Новое значение длительности сигнала (положительное целое число).
 * 
 * @throws std::invalid_argument Если длительность отрицательна.
 */
void
Signal::set_duration(int duration) {
    if (duration < 0) {
        throw std::invalid_argument("Duration must be a positive integer.");
    }
    duration_ = duration;
}

/**
 * @brief Устанавливает уровень сигнала.
 * 
 * @param level Новое значение уровня сигнала (0 или 1).
 * 
 * @throws std::invalid_argument Если уровень не равен 0 или 1.
 */
void
Signal::set_level(int level) {
    if (level != 0 && level != 1) {
        throw std::invalid_argument("Level must be either 0 or 1.");
    }
    level_ = level;
}

/**
 * @brief Возвращает текущую длительность сигнала.
 * 
 * @return Длительность сигнала.
 */
int
Signal::get_duration() const {
    return duration_;
}

/**
 * @brief Возвращает текущий уровень сигнала.
 * 
 * @return Уровень сигнала.
 */
int
Signal::get_level() const {
    return level_;
}

/**
 * @brief Инвертирует уровень сигнала.
 */
void
Signal::inversion() {
    level_ ^= 1;
}

/**
 * @brief Оператор инверсии уровня сигнала.
 * 
 * @return Ссылка на инвертированный объект Signal.
 */
Signal&
Signal::operator~() {
    inversion();
    return *this;
}

/**
 * @brief Увеличивает длительность сигнала на заданное значение.
 * 
 * @param value Значение, на которое увеличивается длительность.
 * 
 * @throws std::invalid_argument Если значение отрицательно.
 * @throws std::overflow_error Если результат превышает максимальное значение int.
 */
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

/**
 * @brief Уменьшает длительность сигнала на заданное значение.
 * 
 * @param value Значение, на которое уменьшается длительность.
 * 
 * @throws std::invalid_argument Если значение отрицательно.
 * @throws std::underflow_error Если результат меньше нуля.
 */
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

/**
 * @brief Выполняет форматированный вывод сигнала в поток.
 * 
 * @param out Поток для вывода.
 */
void
Signal::format_print(std::wostream& out) const {
    wchar_t symbol = level_ == 0 ? L'_' : L'‾';
    out << std::wstring(duration_, symbol);
}

/**
 * @brief Оператор вывода сигнала в поток.
 * 
 * @param out Поток вывода.
 * @param signal Объект Signal для вывода.
 * @return Поток вывода после вставки сигнала.
 */
std::wostream&
operator<<(std::wostream& out, const Signal& signal) {
    signal.format_print(out);
    return out;
}

/**
 * @brief Оператор ввода сигнала из потока. В формате "11000"
 * 
 * @param in Поток ввода.
 * @param signal Объект Signal для инициализации.
 * @return Поток ввода после получения сигнала.
 * 
 * @throws std::invalid_argument Если входные данные не соответствуют ожидаемому формату.
 */
std::istream&
operator>>(std::istream& in, Signal& signal) {
    std::string str;
    in >> str;
    signal = Signal(str);
    return in;
}
