#ifndef I_MORAL_HPP
#define I_MORAL_HPP

#include <cstddef>

class IMoral {
public:
    virtual ~IMoral() = default;
    
    virtual void increase_morale(size_t amount) = 0;
    virtual void decrease_morale(size_t amount) = 0;
    virtual void balance_morale() = 0;
};

#endif // I_MORAL_HPP