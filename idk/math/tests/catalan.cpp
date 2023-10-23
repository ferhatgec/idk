#include <iostream>
#include "../catalan.hpp"

__idk_constexpr idk::usize arr[12] = {
    1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786
};

#define CHECK(x) if(idk::CatalanGenerator<x>::generate() != arr[x]) \
                    std::cerr << "[FAIL] idk::CatalanGenerator<" #x ">::generate != arr[" #x "]\n"; \
                 else \
                    std::cout << "[OK] idk::CatalanGenerator<" #x ">::generate != arr[" #x "]\n";

int main() {
    __idk_constexpr auto val = idk::CatalanGenerator<20>::generate();
    
    std::cout << val << '\n';

    CHECK(0)
    CHECK(1)
    CHECK(2)
    CHECK(3)
    CHECK(4)
    CHECK(5)
    CHECK(6)
    CHECK(7)
    CHECK(8)
    CHECK(9)
    CHECK(10)
    CHECK(11)

    for(idk::isize n = 0; n < 11; ++n)
        if(idk::generate_catalan(n) != arr[n])
            std::cerr << "[FAIL] idk::generate_catalan(" << n << ") != arr[" << n << "]\n";
        else
            std::cout << "[OK] idk::generate_catalan(" << n << ") != arr[" << n << "]\n"; 
}