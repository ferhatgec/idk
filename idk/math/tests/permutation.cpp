#include <iostream>
#include "../permutation.hpp"

__idk_constexpr idk::usize arr[6] = {
    5, 20, 1, 120, 60, 120
};

#define CHECK(n, r, y) if(idk::PermutationGenerator<n, r>::generate() != arr[y]) \
                    std::cerr << "[FAIL] idk::PermutationGenerator<" #n "," #r ">::generate != arr[" #y "]\n"; \
                 else \
                    std::cout << "[OK] idk::PermutationGenerator<" #n "," #r ">::generate != arr[" #y "]\n";

int main() {
    __idk_constexpr auto val = idk::PermutationGenerator<5, 2>::generate();
    
    std::cout << val << '\n';

    CHECK(5, 1, 0)
    CHECK(5, 2, 1)
    CHECK(5, 0, 2)
    CHECK(5, 5, 3)
    CHECK(5, 3, 4)
    CHECK(5, 4, 5)

    if(idk::generate_permutation(5, 1) != arr[0])
        std::cerr << "[FAIL] idk::generate_permutation(5, 1) != arr[0]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 1) != arr[0]\n";
    
    if(idk::generate_permutation(5, 2) != arr[1])
        std::cerr << "[FAIL] idk::generate_permutation(5, 2) != arr[1]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 2) != arr[1]\n";
    
    if(idk::generate_permutation(5, 0) != arr[2])
        std::cerr << "[FAIL] idk::generate_permutation(5, 0) != arr[2]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 0) != arr[2]\n";
    
    if(idk::generate_permutation(5, 5) != arr[3])
        std::cerr << "[FAIL] idk::generate_permutation(5, 5) != arr[3]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 5) != arr[3]\n";
    
    if(idk::generate_permutation(5, 3) != arr[4])
        std::cerr << "[FAIL] idk::generate_permutation(5, 3) != arr[4]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 3) != arr[4]\n";
    
    if(idk::generate_permutation(5, 4) != arr[5])
        std::cerr << "[FAIL] idk::generate_permutation(5, 4) != arr[5]\n";
    else
        std::cout << "[OK] idk::generate_permutation(5, 4) != arr[5]\n";
}