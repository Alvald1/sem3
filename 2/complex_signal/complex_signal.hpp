/**
 * @file Complex_Signal.hpp
 * @brief Определение класса Complex_Signal для управления сложными сигналами.
 *
 * Класс Complex_Signal представляет последовательность сигналов, позволяя управлять
 * их состоянием, вставкой, инверсией, форматированием и доступом по индексу.
 */

#ifndef LAB2_2_COMPLEX_SIGNAL_HPP
#define LAB2_2_COMPLEX_SIGNAL_HPP

#include <string>
#include "../allocator/allocator.hpp"
#include "../signal/signal.hpp"

/**
 * @class Complex_Signal
 * @brief Класс для представления и управления сложной последовательностью сигналов.
 *
 * Complex_Signal предоставляет методы для инверсии сигналов, вставки других Complex_Signal,
 * поиска сигнала по индексу, форматированного вывода и множественного умножения сигналов.
 */
class Complex_Signal {
  public:
    /**
     * @brief Конструктор по умолчанию. Создает пустой Complex_Signal.
     */
    Complex_Signal() = default;

    /**
     * @brief Конструктор, инициализирующий Complex_Signal с заданным уровнем и длительностью сигнала.
     * 
     * @param level Уровень сигнала (0 или 1).
     * @param duration Длительность сигнала.
     */
    Complex_Signal(int level, int duration);

    /**
     * @brief Конструктор, создающий Complex_Signal из строки.
     * 
     * @param str Строка, представляющая сигнал.
     */
    Complex_Signal(const std::string& str);

    // Конструкторы копирования и перемещения
    Complex_Signal(const Complex_Signal& other) = default;
    Complex_Signal(Complex_Signal&& other) noexcept = default;

    // Операторы присваивания копированием и перемещением
    Complex_Signal& operator=(const Complex_Signal&) = default;
    Complex_Signal& operator=(Complex_Signal&&) noexcept = default;

    /**
     * @brief Инвертирует уровни всех сигналов в Complex_Signal.
     */
    void inverstion();

    /**
     * @brief Оператор инверсии ~ для инверсии всех сигналов.
     * 
     * @return Ссылка на инвертированный Complex_Signal.
     */
    Complex_Signal& operator~();

    /**
     * @brief Оператор += для добавления другого Complex_Signal к текущему.
     * 
     * @param other Другой Complex_Signal для добавления.
     * @return Ссылка на текущий объект после добавления.
     */
    Complex_Signal& operator+=(const Complex_Signal& other);

    /**
     * @brief Вставляет другой Complex_Signal в текущий объект на указанную позицию.
     * 
     * @param other Complex_Signal для вставки.
     * @param position Позиция вставки.
     */
    void insert(const Complex_Signal& other, int position);

    /**
     * @brief Оператор [] для доступа к уровню сигнала на указанной позиции.
     * 
     * @param position Позиция в последовательности сигналов.
     * @return Уровень сигнала на данной позиции.
     */
    int operator[](int position) const;

    /**
     * @brief Форматированный вывод Complex_Signal в выходной поток.
     * 
     * @param out Поток для вывода.
     */
    void format_print(std::wostream& out) const;

    /**
     * @brief Оператор * для многократного умножения сигнала.
     * 
     * @param multiplier Количество копий сигнала.
     * @return Новый Complex_Signal с повторенными сигналами.
     */
    Complex_Signal operator*(int multiplier);

    /**
     * @brief Оператор вывода для вывода Complex_Signal в поток.
     * 
     * @param out Поток вывода.
     * @param signals Объект Complex_Signal для вывода.
     * @return Поток после вывода Complex_Signal.
     */
    friend std::wostream& operator<<(std::wostream& out, const Complex_Signal& signals);

    /**
     * @brief Оператор ввода для ввода Complex_Signal из потока.
     * 
     * @param in Поток ввода.
     * @param signals Объект Complex_Signal для ввода данных.
     * @return Поток после ввода данных в Complex_Signal.
     */
    friend std::istream& operator>>(std::istream& in, Complex_Signal& signals);

  private:
    Allocator signals; ///< Объект Allocator для хранения последовательности сигналов.

    /**
     * @brief Выполняет бинарный поиск позиции сигнала.
     * 
     * @param position Позиция для поиска.
     * @return Индекс сигнала на данной позиции.
     */
    int bin_search(int position) const;

    /**
     * @brief Делит сигнал на части в массиве на основе позиции и размера.
     * 
     * @param index Индекс сигнала для разделения.
     * @param position Позиция в сигнале для разделения.
     * @param size Размер сигнала после разделения.
     * @return Новый индекс после разделения.
     */
    int split(int index, int position, int size);
};

std::wostream& operator<<(std::wostream& out, const Complex_Signal& signals);
std::istream& operator>>(std::istream& in, Complex_Signal& signals);

#endif // LAB2_2_COMPLEX_SIGNAL_HPP
