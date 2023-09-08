#include <iostream>
#include "../combination.hpp"

constexpr idk::usize arr[6] = {
    5, 10, 1, 1, 10, 5
};

#define CHECK(n, r, y) if(idk::CombinationGenerator<n, r>::generate() != arr[y]) \
                    std::cerr << "[FAIL] idk::CombinationGenerator<" #n "," #r ">::generate != arr[" #y "]\n"; \
                 else \
                    std::cout << "[OK] idk::CombinationGenerator<" #n "," #r ">::generate != arr[" #y "]\n";

int main() {
    constexpr auto val = idk::CombinationGenerator<5, 2>::generate();
    
    std::cout << val << '\n';

    CHECK(5, 1, 0)
    CHECK(5, 2, 1)
    CHECK(5, 0, 2)
    CHECK(5, 5, 3)
    CHECK(5, 3, 4)
    CHECK(5, 4, 5)
}