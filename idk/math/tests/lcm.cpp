#include <iostream>
#include "../lcm.hpp"

int main() {
    if(idk::LeastCommonMultipleGenerator<10, 5>::generate() != 10)
        std::cerr << "[FAIL] idk::LeastCommonMultipleGenerator<10, 5>::generate() != 10\n";
    else
        std::cout << "[OK] idk::LeastCommonMultipleGenerator<10, 5>::generate() != 10\n";

    if(idk::LeastCommonMultipleGenerator<0, 0>::generate() != 0)
        std::cerr << "[FAIL] idk::LeastCommonMultipleGenerator<0, 0>::generate() != 0\n";
    else
        std::cout << "[OK] idk::LeastCommonMultipleGenerator<0, 0>::generate() != 0\n";
    
    if(idk::LeastCommonMultipleGenerator<42, 4>::generate() != 84)
        std::cerr << "[FAIL] idk::LeastCommonMultipleGenerator<42, 4>::generate() != 84\n";
    else
        std::cout << "[OK] idk::LeastCommonMultipleGenerator<42, 4>::generate() != 84\n";
}