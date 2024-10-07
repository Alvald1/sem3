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

    void inverstion();
    Complex_Signal& operator~();

    void add(const Complex_Signal& other_signal);
    Complex_Signal& operator+=(const Complex_Signal& other_signal);

    void insert(Complex_Signal& other_signal, int position);

    Complex_Signal& operator*(int multiplier);

    void erase(int position, int duration);

    int operator[](int position) const;

    void format_print(std::wostream& out) const;

  private:
    Allocator signals;

    int bin_search(int) const;
};

#endif