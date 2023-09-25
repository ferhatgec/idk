#include "../predefined.hpp"
#include "../../utilities/type_traits.hpp"
#include <iostream>
#include <iomanip>

using namespace idk;

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

    idk::u32 x = 42_u32;
    auto y = 31_u32;

    idk::i64 z = 69_i64;
    auto q = 7_i16;

    if(!idk::IsSameVal<decltype(x), decltype(y)>)
        std::cerr << "[FAIL] !idk::IsSameVal<decltype(x), decltype(y)>()\n";
    else
        std::cout << "[OK] !idk::IsSameVal<decltype(x), decltype(y)>()\n";

    if(idk::IsSameVal<decltype(z), decltype(q)>)
        std::cerr << "[FAIL] idk::IsSameVal<decltype(z), decltype(q)>()\n";
    else
        std::cout << "[OK] idk::IsSameVal<decltype(z), decltype(q)>()\n";
}