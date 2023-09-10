#include <iostream>
#include "../derangement.hpp"

constexpr idk::usize arr[10] = {
    1, 0, 1, 2, 9, 44, 265, 1854, 14833, 133496
};

#define CHECK(n) if(idk::DerangementGenerator<n>::generate() != arr[n]) \
                    std::cerr << "[FAIL] idk::DerangementGenerator<" #n ">::generate != arr[" #n "]\n"; \
                 else \
                    std::cout << "[OK] idk::DerangementGenerator<" #n ">::generate != arr[" #n "]\n";

int main() {
    constexpr auto val = idk::DerangementGenerator<5>::generate();
    
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
}