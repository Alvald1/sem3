#ifndef LAB2_2_SIGNAL_HPP
#define LAB2_2_SIGNAL_HPP

#include <fstream>
#include <string>

class Signal {
  public:
    Signal() = default;
    Signal(int, int);
    Signal(const std::string&);

    int get_level() const;
    int get_duration() const;

    void set_level(int);
    void set_duration(int);

    void inversion();
    Signal& operator~();

    void increase(int);
    void decrease(int);

    void format_print(std::wostream&) const;

  private:
    int level_ = 0, duration_ = 0;
};

#endif