#define __idk_convert_into_std_complex
#include "../complex.hpp"
#include <iostream>

#define test_condition(condition) if(condition) \
                                    std::cerr << "[FAIL] " #condition "\n"; \
                                  else \
                                    std::cout << "[OK] " #condition "\n";

using namespace std::complex_literals;

int main() {
    // i^2
    test_condition(idk::ComplexFloat80(0, 1) * idk::ComplexFloat80(0, 1) != -1)
    test_condition(idk::ComplexFloat80(idk::ComplexFloat80(0, 1)) * idk::ComplexFloat80(0, 1) != -1)
    test_condition(idk::ComplexFloat80(3, 1).conjugate() != idk::ComplexFloat80(3, -1))
    test_condition(idk::ComplexFloat80(3, 1).conjugate().abs() != idk::ComplexFloat80(3, -1).abs())
    test_condition(idk::ComplexFloat80(2, 0) * idk::ComplexFloat80(2, 0) != 4)
    test_condition(idk::ComplexFloat80(0, 1) + idk::ComplexFloat80(2, 0) != idk::ComplexFloat80(2, 1))
    test_condition(idk::ComplexFloat80(0, 1) * idk::ComplexFloat80(0, 1) != idk::ComplexFloat80(-1, 0))
    test_condition((idk::ComplexFloat80(0, 1) + (idk::ComplexFloat80(2, 0) / idk::ComplexFloat80(0, 1))) != idk::ComplexFloat80(0, -1))
    test_condition(1 / idk::ComplexFloat80(0, 1) != idk::ComplexFloat80(0, -1))
    test_condition(2_f80 * std::log(idk::ComplexFloat80(0, 1).convert()) != std::complex<long double>(0, idk::pi))
}