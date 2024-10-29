/**
 * @file Allocator.hpp
 * @brief Определение класса Allocator для управления динамическим массивом объектов Signals.
 *
 * Класс Allocator позволяет выделять, освобождать и управлять массивом объектов Signals,
 * представляющих сигналы с временем их выполнения.
 */

#ifndef LAB2_2_ALLOCATOR_HPP
#define LAB2_2_ALLOCATOR_HPP

#include "../signal/signal.hpp"

/**
 * @struct Signals
 * @brief Структура для хранения сигнала и времени его выполнения.
 * 
 * Содержит объект Signal и переменную time, представляющую время сигнала.
 */
struct Signals {
    Signal signal; ///< Объект сигнала.
    int time;      ///< Время сигнала.
};

/**
 * @class Allocator
 * @brief Класс для управления динамическим массивом объектов Signals.
 *
 * Allocator предоставляет базовые методы для управления массивом сигналов, включая
 * выделение памяти, копирование, перемещение и изменение размера массива.
 */
class Allocator {
  public:
    /**
     * @brief Конструктор по умолчанию. Создает пустой Allocator.
     */
    Allocator() = default;

    /**
     * @brief Конструктор, инициализирующий Allocator с заданной емкостью.
     * @param n Начальная емкость массива.
     */
    Allocator(int n);

    /**
     * @brief Деструктор. Освобождает выделенную память.
     */
    ~Allocator();

    /**
     * @brief Конструктор копирования. Копирует данные из другого Allocator.
     * @param other Другой объект Allocator для копирования.
     */
    Allocator(const Allocator& other);

    /**
     * @brief Конструктор перемещения. Перемещает данные из другого Allocator.
     * @param other Другой объект Allocator для перемещения.
     */
    Allocator(Allocator&& other) noexcept;

    /**
     * @brief Оператор присваивания копированием.
     * @param other Другой объект Allocator для копирования.
     * @return Ссылка на текущий объект после присваивания.
     */
    Allocator& operator=(const Allocator& other);

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Другой объект Allocator для перемещения.
     * @return Ссылка на текущий объект после присваивания.
     */
    Allocator& operator=(Allocator&& other) noexcept;

    /**
     * @brief Изменяет размер массива.
     * 
     * Если новый размер больше текущей емкости, выделяется новая память,
     * а существующие элементы копируются в новую область памяти.
     * 
     * @param new_size Новый размер массива.
     */
    void resize(int new_size);

    int size_ = 0;              ///< Текущий размер массива.
    int capacity_ = 0;          ///< Емкость массива.
    Signals* buffer_ = nullptr; ///< Указатель на динамический массив объектов Signals.
};

#endif // LAB2_2_ALLOCATOR_HPP
