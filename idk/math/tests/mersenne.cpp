#include "../mersenne.hpp"
#include <iostream>

__idk_constexpr idk::usize arr[10] = {
    0, 1, 3, 7, 15, 31, 63, 127, 255, 511
};

#define CHECK(n) if(idk::MersenneGenerator<n>::generate() != arr[n]) \
                    std::cerr << "[FAIL] idk::MersenneGenerator<" #n ">::generate != arr[" #n "]\n"; \
                 else \
                    std::cout << "[OK] idk::MersenneGenerator<" #n ">::generate != arr[" #n "]\n";

int main() {
    __idk_constexpr auto val = idk::MersenneGenerator<5>::generate();
    
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
    
    for(idk::isize n = 0; n < 9; ++n)
        if(idk::generate_mersenne(n) != arr[n])
            std::cerr << "[FAIL] idk::generate_mersenne(" << n << ") != arr[" << n << "]\n";
        else
            std::cout << "[OK] idk::generate_mersenne(" << n << ") != arr[" << n << "]\n"; 
}