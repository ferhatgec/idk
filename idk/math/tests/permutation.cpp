#include <iostream>
#include "../permutation.hpp"

constexpr idk::usize arr[6] = {
    5, 20, 1, 120, 60, 120
};

#define CHECK(n, r, y) if(idk::PermutationGenerator<n, r>::generate() != arr[y]) \
                    std::cerr << "[FAIL] idk::PermutationGenerator<" #n "," #r ">::generate != arr[" #y "]\n"; \
                 else \
                    std::cout << "[OK] idk::PermutationGenerator<" #n "," #r ">::generate != arr[" #y "]\n";

int main() {
    constexpr auto val = idk::PermutationGenerator<5, 2>::generate();
    
    std::cout << val << '\n';

    CHECK(5, 1, 0)
    CHECK(5, 2, 1)
    CHECK(5, 0, 2)
    CHECK(5, 5, 3)
    CHECK(5, 3, 4)
    CHECK(5, 4, 5)
}