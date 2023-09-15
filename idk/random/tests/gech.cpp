#include <iostream>
#include "../gech.hpp"

int main() {
    idk::GechGenerator x(static_cast<idk::u32>(::time(NULL)));
    
    x._btw_start_pos = 10;
    x._btw_end_pos = 140;

    std::cout << x.take() << '\n';
}