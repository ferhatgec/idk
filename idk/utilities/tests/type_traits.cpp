#include "../type_traits.hpp"
#include <iostream>

int main() {
    constexpr auto i = 12l;
    idk::u8 j = 12;
    if(idk::IsIntegralVal<bool>)
        std::cout << "[OK] idk::IsIntegralVal<bool>\n";
    else
        std::cerr << "[FAIL] idk::IsIntegralVal<bool>\n";
    
    std::cout << std::boolalpha << idk::IsIntegralVal<bool> << ' ' << 
                                   idk::IsConstVal<decltype(i)> << ' ' << 
                                   idk::IsFloatingPointVal<decltype(j)> << '\n';

    if constexpr(idk::is_cpp23_supported()) {
        std::cout << "cpp23 supported compiler\n";
    }
}