#include "../mean.hpp"
#include "../../types/predefined.hpp"
#include "../math.hpp"
#include <iomanip>
#include <iostream>

int main() {
  idk::Vec<idk::isize> x{1, 2, 3, 4};

  if (idk::ArithmeticMeanGenerator::generate(x) != 2.5)
    std::cerr << "[FAIL] idk::ArithmeticMeanGenerator::generate(x) != 2.5\n";
  else
    std::cout << "[OK] idk::ArithmeticMeanGenerator::generate(x) != 2.5\n";

  // on 32bit systems this kind of thing may fail.
  if (!idk::nearly_equals(
          idk::GeometricMeanGenerator::generate(x),
          2.213363839400642962829124371637590229511260986328125L, 0.0000001L))
    std::cerr << "[FAIL] idk::GeometricMeanGenerator::generate(x) != "
                 "2.213363839400642962829124371637590229511260986328125\n";
  else
    std::cout << "[OK] idk::GeometricMeanGenerator::generate(x) != "
                 "2.213363839400642962829124371637590229511260986328125\n";

  if (idk::GeometricMeanGenerator::generate(idk::Vec<idk::isize>{1_isize}) != 1)
    std::cerr
        << "[FAIL] idk::GeometricMeanGenerator::generate(idk::Vec<idk::isize> "
           "{ 1_isize }) != 1\n";
  else
    std::cout
        << "[OK] idk::GeometricMeanGenerator::generate(idk::Vec<idk::isize> { "
           "1_isize }) != 1\n";
}