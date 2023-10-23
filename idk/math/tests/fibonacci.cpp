#include <iostream>
#include "../fibonacci.hpp"

__idk_constexpr idk::usize arr[14] = {
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
};

#define CHECK(x) if(idk::FibonacciGenerator<x>::generate() != arr[x]) \
                    std::cerr << "[FAIL] idk::FibonacciGenerator<" #x ">::generate != arr[" #x "]\n"; \
                 else \
                    std::cout << "[OK] idk::FibonacciGenerator<" #x ">::generate != arr[" #x "]\n";

int main() {
    __idk_constexpr auto val = idk::FibonacciGenerator<20>::generate();
    
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
    CHECK(12)
    CHECK(13)

     for(idk::isize n = 0; n < 13; ++n)
        if(idk::generate_fibonacci(n) != arr[n])
            std::cerr << "[FAIL] idk::generate_fibonacci(" << n << ") != arr[" << n << "]\n";
        else
            std::cout << "[OK] idk::generate_fibonacci(" << n << ") != arr[" << n << "]\n"; 
}