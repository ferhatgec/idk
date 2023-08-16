#include "../predefined.hpp"
#include <iostream>

int main() {
    std::cout << idk::os_platform 
              << " " 
              << idk::cpu_arch 
              << " " 
              << std::boolalpha 
              << idk::is_cpp20_supported() << '\n';
}