#ifndef LAB2_2_COMPLEX_SIGNAL_HPP
#define LAB2_2_COMPLEX_SIGNAL_HPP

#include <string>

#include "allocator.hpp"
#include "signal.hpp"

class Complex_Signal {
  public:
    Complex_Signal() = default;
    Complex_Signal(int level, int duration);
    Complex_Signal(std::string str);
    Complex_Signal(const Signal& signal);

    void inverstion();
    Complex_Signal& operator~();

    void add(const Complex_Signal& other_signal);
    Complex_Signal& operator+=(const Complex_Signal& other_signal);

    void insert(Complex_Signal& other_signal, int position);

    Complex_Signal& operator*(int multiplier);

    void erase(int position, int duration);

    int operator[](int position) const;
    int& operator[](int position);

    void format_print(std::wostream& out) const;

  private:
    Allocator signal;
};

#endif