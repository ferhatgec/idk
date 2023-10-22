#include <iostream>
#include "../gcd.hpp"

int main() {
    if(idk::GreatestCommonDivisorGenerator<10, 5>::generate() != 5)
        std::cerr << "[FAIL] idk::GreatestCommonDivisorGenerator<10, 5>::generate() != 5\n";
    else
        std::cout << "[OK] idk::GreatestCommonDivisorGenerator<10, 5>::generate() != 5\n";

    if(idk::GreatestCommonDivisorGenerator<0, 0>::generate() != 0)
        std::cerr << "[FAIL] idk::GreatestCommonDivisorGenerator<0, 0>::generate() != 0\n";
    else
        std::cout << "[OK] idk::GreatestCommonDivisorGenerator<0, 0>::generate() != 0\n";

    if(idk::GreatestCommonDivisorGenerator<42, 4>::generate() != 2)
        std::cerr << "[FAIL] idk::GreatestCommonDivisorGenerator<42, 4>::generate() != 2\n";
    else
        std::cout << "[OK] idk::GreatestCommonDivisorGenerator<42, 4>::generate() != 2\n";

    if(idk::generate_gcd(10, 5) != 5)
        std::cerr << "[FAIL] idk::generate_gcd(10, 5) != 5\n";
    else
        std::cout << "[OK] idk::generate_gcd(10, 5) != 5\n";

    if(idk::generate_gcd(0, 0) != 0)
        std::cerr << "[FAIL] idk::generate_gcd(0, 0) != 0\n";
    else
        std::cout << "[OK] idk::generate_gcd(0, 0) != 0\n";

    if(idk::generate_gcd(42, 4) != 2)
        std::cerr << "[FAIL] idk::generate_gcd(42, 4) != 2\n";
    else
        std::cout << "[OK] idk::generate_gcd(42, 4) != 2\n";
}