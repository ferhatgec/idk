#include "../xorshift.hpp"
#include <iostream>

int main() {
    idk::XorshiftGenerator x(static_cast<idk::u32>(::time(NULL)));

    x._btw_start_pos = 10;
    x._btw_end_pos = 140;

    std::cout << x.take() << '\n';
}