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

    if(idk::generate_combination(5, 1) != arr[0])
        std::cerr << "[FAIL] idk::generate_combination(5, 1) != arr[0]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 1) != arr[0]\n";
    
    if(idk::generate_combination(5, 2) != arr[1])
        std::cerr << "[FAIL] idk::generate_combination(5, 2) != arr[1]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 2) != arr[1]\n";
    
    if(idk::generate_combination(5, 0) != arr[2])
        std::cerr << "[FAIL] idk::generate_combination(5, 0) != arr[2]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 0) != arr[2]\n";
    
    if(idk::generate_combination(5, 5) != arr[3])
        std::cerr << "[FAIL] idk::generate_combination(5, 5) != arr[3]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 5) != arr[3]\n";
    
    if(idk::generate_combination(5, 3) != arr[4])
        std::cerr << "[FAIL] idk::generate_combination(5, 3) != arr[4]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 3) != arr[4]\n";
    
    if(idk::generate_combination(5, 4) != arr[5])
        std::cerr << "[FAIL] idk::generate_combination(5, 4) != arr[5]\n";
    else
        std::cout << "[OK] idk::generate_combination(5, 4) != arr[5]\n";
        
}