/**
 * @file Signal.hpp
 * @brief Файл содержит определение класса Signal для работы с сигналами, 
 *        позволяя управлять их уровнем и продолжительностью, а также поддерживает операции инверсии и форматированного вывода.
 */

#ifndef LAB2_2_SIGNAL_HPP
#define LAB2_2_SIGNAL_HPP

#include <ostream>
#include <string>

/**
 * @class Signal
 * @brief Класс Signal представляет сигнал с уровнем и продолжительностью.
 * 
 * Класс предоставляет методы для получения и изменения уровня и длительности сигнала,
 * а также для выполнения инверсии уровня и форматированного вывода.
 */
class Signal {
  public:
    /**
     * @brief Конструктор по умолчанию. Создаёт объект Signal с уровнем 0 и длительностью 0.
     */
    Signal() = default;

    /**
     * @brief Конструктор с параметрами.
     * @param level Уровень сигнала.
     * @param duration Длительность сигнала.
     */
    Signal(int level, int duration);

    /**
     * @brief Конструктор, инициализирующий сигнал из строки.
     * @param str Строка, содержащая информацию о сигнале.
     */
    Signal(const std::string& str);

    /**
     * @brief Возвращает текущий уровень сигнала.
     * @return Уровень сигнала.
     */
    int get_level() const;

    /**
     * @brief Возвращает текущую длительность сигнала.
     * @return Длительность сигнала.
     */
    int get_duration() const;

    /**
     * @brief Устанавливает уровень сигнала.
     * @param level Новый уровень сигнала.
     */
    void set_level(int level);

    /**
     * @brief Устанавливает длительность сигнала.
     * @param duration Новая длительность сигнала.
     */
    void set_duration(int duration);

    /**
     * @brief Инвертирует уровень сигнала.
     */
    void inversion();

    /**
     * @brief Оператор инверсии уровня сигнала.
     * @return Ссылка на инвертированный объект Signal.
     */
    Signal& operator~();

    /**
     * @brief Увеличивает уровень сигнала на заданное значение.
     * @param increment Значение, на которое увеличивается уровень сигнала.
     */
    void increase(int increment);

    /**
     * @brief Уменьшает уровень сигнала на заданное значение.
     * @param decrement Значение, на которое уменьшается уровень сигнала.
     */
    void decrease(int decrement);

    /**
     * @brief Выполняет форматированный вывод сигнала в поток.
     * @param os Поток для вывода.
     */
    void format_print(std::wostream& os) const;

    /**
     * @brief Оператор вывода сигнала в поток.
     * @param os Поток вывода.
     * @param signal Объект Signal для вывода.
     * @return Поток вывода после вставки сигнала.
     */
    friend std::wostream& operator<<(std::wostream& os, const Signal& signal);

    /**
     * @brief Оператор ввода сигнала из потока.
     * @param is Поток ввода.
     * @param signal Объект Signal для инициализации.
     * @return Поток ввода после получения сигнала.
     */
    friend std::istream& operator>>(std::istream& is, Signal& signal);

  private:
    int level_ = 0;    ///< Уровень сигнала.
    int duration_ = 0; ///< Длительность сигнала.
};

/**
 * @brief Оператор вывода сигнала в поток.
 * @param os Поток вывода.
 * @param signal Объект Signal для вывода.
 * @return Поток вывода после вставки сигнала.
 */
std::wostream& operator<<(std::wostream& os, const Signal& signal);

/**
 * @brief Оператор ввода сигнала из потока.
 * @param is Поток ввода.
 * @param signal Объект Signal для инициализации.
 * @return Поток ввода после получения сигнала.
 */
std::istream& operator>>(std::istream& is, Signal& signal);

#endif // LAB2_2_SIGNAL_HPP
