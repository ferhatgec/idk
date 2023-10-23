#include "../prime.hpp"
#include <iomanip>
#include <iostream>

__idk_constexpr bool arr[32] = {
    false, false, true, true, false, true, false, true, false, false, false, 
    true, false, true, false, false, false, true, false, true, false,
    false, false, true, false, false, false, false, false, true, false, 
    true
};

__idk_constexpr idk::isize arr_prime_gen[25] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
    37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
    79, 83, 89, 97
};

__idk_constexpr idk::isize arr_mersenne_prime_gen[8] = {
    3, 7, 31, 127, 8191, 131071, 524287, 2147483647
};

#define CHECK(x) if(idk::PrimeCheck<x>::check() != arr[x]) \
                    std::cerr << "[FAIL] idk::PrimeCheck<" #x ">::check() != arr[" #x "]\n"; \
                 else \
                    std::cout << "[OK] idk::PrimeCheck<" #x ">::check() != arr[" #x "]\n";

#define CHECK_PRIME_GENERATOR(x) if(idk::PrimeGenerator<x>::generate() != arr_prime_gen[x]) \
                                    std::cerr << "[FAIL] idk::PrimeGenerator<" #x ">::generate() != arr_prime_gen[" #x "]\n"; \
                                else \
                                    std::cerr << "[OK] idk::PrimeGenerator<" #x ">::generate() != arr_prime_gen[" #x "]\n";

#define CHECK_MERSENNE_PRIME_GENERATOR(x) \
                                if(idk::MersennePrimeGenerator<x>::generate() != arr_mersenne_prime_gen[x]) \
                                    std::cerr << "[FAIL] idk::MersennePrimeGenerator<" #x ">::generate() != arr_mersenne_prime_gen[" #x "]\n"; \
                                else \
                                    std::cerr << "[OK] idk::MersennePrimeGenerator<" #x ">::generate() != arr_mersenne_prime_gen[" #x "]\n";


int main() {
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
    CHECK(14)
    CHECK(15)
    CHECK(16)
    CHECK(17)
    CHECK(18)
    CHECK(19)
    CHECK(20)
    CHECK(21)
    CHECK(22)
    CHECK(23)
    CHECK(24)
    CHECK(25)
    CHECK(26)
    CHECK(27)
    CHECK(28)
    CHECK(29)
    CHECK(30)
    CHECK(31)
    
    CHECK_PRIME_GENERATOR(0)
    CHECK_PRIME_GENERATOR(1)
    CHECK_PRIME_GENERATOR(2)
    CHECK_PRIME_GENERATOR(3)
    CHECK_PRIME_GENERATOR(4)
    CHECK_PRIME_GENERATOR(5)
    CHECK_PRIME_GENERATOR(6)
    CHECK_PRIME_GENERATOR(7)
    CHECK_PRIME_GENERATOR(8)
    CHECK_PRIME_GENERATOR(9)
    CHECK_PRIME_GENERATOR(10)
    CHECK_PRIME_GENERATOR(11)
    CHECK_PRIME_GENERATOR(12)
    CHECK_PRIME_GENERATOR(13)
    CHECK_PRIME_GENERATOR(14)
    CHECK_PRIME_GENERATOR(15)
    CHECK_PRIME_GENERATOR(16)
    CHECK_PRIME_GENERATOR(17)
    CHECK_PRIME_GENERATOR(18)
    CHECK_PRIME_GENERATOR(19)
    CHECK_PRIME_GENERATOR(20)
    CHECK_PRIME_GENERATOR(21)
    CHECK_PRIME_GENERATOR(22)
    CHECK_PRIME_GENERATOR(23)
    CHECK_PRIME_GENERATOR(24)
    
    if(idk::is_prime(-5))
        std::cerr << "[FAIL] idk::is_prime(-5)\n";
    else
        std::cout << "[OK] idk::is_prime(-5)\n";

    CHECK_MERSENNE_PRIME_GENERATOR(0)
    CHECK_MERSENNE_PRIME_GENERATOR(1)
    CHECK_MERSENNE_PRIME_GENERATOR(2)
    CHECK_MERSENNE_PRIME_GENERATOR(3)
    CHECK_MERSENNE_PRIME_GENERATOR(4)
    CHECK_MERSENNE_PRIME_GENERATOR(5)
    CHECK_MERSENNE_PRIME_GENERATOR(6)
    CHECK_MERSENNE_PRIME_GENERATOR(7)
 
    // idk::generate_prime starts from index 0.
    // so nth prime probably is idk::generate_prime(n - 1).
    if(idk::generate_prime(30) != 127)
        std::cerr << "[FAIL] idk::generate_prime(30) != 127\n";
    else
        std::cout << "[OK] idk::generate_prime(30) != 127\n";
    
    if(idk::generate_prime(41) != 181)
        std::cerr << "[FAIL] idk::generate_prime(41) != 181\n";
    else
        std::cout << "[OK] idk::generate_prime(41) != 181\n";

    if(idk::generate_prime(999) != 7919)
        std::cerr << "[FAIL] idk::generate_prime(999) != 7919\n";
    else
        std::cout << "[OK] idk::generate_prime(999) != 7919\n";

    //for(idk::isize n = 0; n < 100; ++n)
    //    std::cout << idk::generate_prime(n) << " " << n << " " << std::boolalpha << idk::is_prime(n) << '\n';

    if(idk::generate_mersenne_prime(0) != 3)
        std::cerr << "[FAIL] idk::generate_mersenne_prime(0) != 2\n";
    else
        std::cout << "[OK] idk::generate_mersenne_prime(0) != 2\n";
}