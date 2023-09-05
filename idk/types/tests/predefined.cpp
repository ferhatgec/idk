#include "../predefined.hpp"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << idk::os_platform 
              << " " 
              << idk::cpu_arch 
              << " " 
              << std::boolalpha 
              << idk::is_cpp20_supported()
              << "\n"
              << std::setprecision(21)
              << idk::pi
              << " "
              << idk::e << '\n';
}