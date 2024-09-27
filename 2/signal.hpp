#ifndef LAB2_2_SIGNAL_HPP
#define LAB2_2_SIGNAL_HPP

#include <fstream>
#include <string>

class Signal {
  public:
    Signal() = default;
    Signal(int, int);
    Signal(std::string);

    int get_level() const;
    int get_duration() const;

    void set_level(int);
    void set_duration(int);

    void inversion();

    void increase(int);
    void decrease(int);

    void input(std::ifstream);
    void print(std::ofstream) const;
    void format_print(std::ofstream) const;

  private:
    int level_ = 0, duration_ = 0;
    int read_level(std::ifstream);
    int read_duration(std::ifstream);
};

#endif