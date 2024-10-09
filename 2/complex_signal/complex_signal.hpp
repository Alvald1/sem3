#ifndef LAB2_2_COMPLEX_SIGNAL_HPP
#define LAB2_2_COMPLEX_SIGNAL_HPP

#include <string>

#include "../allocator/allocator.hpp"
#include "../signal/signal.hpp"

class Complex_Signal {
  public:
    Complex_Signal() = default;
    Complex_Signal(int level, int duration);
    Complex_Signal(const std::string& str);

    Complex_Signal(const Complex_Signal& other) = default;
    Complex_Signal(Complex_Signal&& other) noexcept = default;

    Complex_Signal& operator=(const Complex_Signal&) = default;
    Complex_Signal& operator=(Complex_Signal&&) noexcept = default;

    void inverstion();
    Complex_Signal& operator~();

    Complex_Signal& operator+=(const Complex_Signal& other);

    void insert(const Complex_Signal& other, int position);

    Complex_Signal& operator*(int multiplier);

    void erase(int position, int duration);

    int operator[](int position) const;

    void format_print(std::wostream& out) const;

  private:
    Allocator signals;

    int bin_search(int position) const;
    int split(int index, int position, int size);
};

#endif