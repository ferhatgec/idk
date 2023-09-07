#include <iostream>
#include "../factorial.hpp"

int main() {
    constexpr auto x = idk::FactorialGenerator<12>::generate();

    std::cout << "12! = " << x << '\n';
}