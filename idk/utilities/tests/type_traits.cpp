#define __idk_experimental
#include "../type_traits.hpp"
#include "../../containers/vector.hpp"
#include <iostream>

class Test {};

int main() {
    __idk_constexpr auto i = 12l;
    idk::u8 j = 12;
    if(idk::IsIntegralVal<bool>)
        std::cout << "[OK] idk::IsIntegralVal<bool>\n";
    else
        std::cerr << "[FAIL] idk::IsIntegralVal<bool>\n";
    
    std::cout << std::boolalpha << idk::IsIntegralVal<bool> << ' ' << 
                                   idk::IsConstVal<decltype(i)> << ' ' << 
                                   idk::IsFloatingPointVal<decltype(j)> << '\n';

    if __idk_constexpr(idk::is_cpp23_supported()) {
        std::cout << "cpp23 supported compiler\n";
    }
    
    if constexpr(idk::IsPrintable<idk::Vec<int>>::value) // idk::Vec<T> has overloads over std::ostream and std::wstream.
        std::cout << "[OK] idk::IsPrintable<idk::Vec<int>>::value\n";
    else
        std::cout << "[FAIL] idk::IsPrintable<idk::Vec<int>>::value\n";

    if constexpr(idk::IsSameVal<idk::IsPrintable<int>, idk::false_type>)
        std::cout << "[FAIL] idk::IsSameVal<idk::IsPrintable<int>, idk::false_type>\n";
    else
        std::cout << "[OK] idk::IsSameVal<idk::IsPrintable<int>, idk::false_type>\n";
        
    if constexpr(idk::IsSameVal<idk::IsPrintable<Test>, idk::true_type>)
        std::cout << "[FAIL] idk::IsSameVal<idk::IsPrintable<Test>, idk::true_type>\n";
    else
        std::cout << "[OK] idk::IsSameVal<idk::IsPrintable<Test>, idk::true_type>\n";
}