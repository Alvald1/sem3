#ifndef I_MORAL_HPP
#define I_MORAL_HPP

#include <cstddef>

class IMoral {
  public:
    virtual ~IMoral() = default;

    virtual void increase_morale(std::size_t amount) = 0;
    virtual void decrease_morale(std::size_t amount) = 0;
    virtual void balance_morale(std::size_t amount) = 0;
};

#endif // I_MORAL_HPP
