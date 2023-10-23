#include "../pair.hpp"
#include <iostream>

int main() {
    __idk_constexpr double _s = 3.1415926535;
    idk::Pair<idk::i16, double> val(42, _s);

    val.first() = 12;
    
    if(val.first() == 12)
        std::cout << "[OK] val.first() == 12\n";
    else
        std::cout << "[FAIL] val.first() == 12\n";
    
    std::cout << val.first() << ' ' << val.second() << '\n';

    idk::Pair<idk::i16, double> val1(3, 3.14);

    if(val == val1)
        std::cout << "[FAIL] val == val1\n";
    else
        std::cout << "[OK] val == val1\n";
}