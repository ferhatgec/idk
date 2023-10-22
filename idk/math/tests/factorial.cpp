#include <iostream>
#include "../factorial.hpp"

int main() {
    constexpr auto x = idk::FactorialGenerator<12>::generate();

    std::cout << "12! = " << x << '\n';

    if(x != idk::generate_factorial(12))
        std::cerr << "[FAIL] x != idk::generate_factorial(12)\n";
    else
        std::cout << "[OK] x != idk::generate_factorial(12)\n";
}