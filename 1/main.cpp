#include <iostream>

#include "detail.hpp"

int
main() {
    Detail_info a("a1", "a2", 1);
    a.print();
    std::cout << a.encode() << std::endl;
    Detail_info b("{'id':'b1','name':'b2','count':3}");
    b.print();
    return 0;
}