#include <iostream>
#include <iomanip>
#include "../variance.hpp"
#include "../../types/predefined.hpp"

int main() {
    idk::Vec<idk::isize> x {
        3, 7, 11
    };
    
    if(idk::PopulationVarianceGenerator::generate(x) != 10.6666666666666660745477201999165117740631103515625)
        std::cerr << "[FAIL] idk::PopulationVarianceGenerator::generate(x) != 10.6666666666666660745477201999165117740631103515625\n";
    else
        std::cout << "[OK] idk::PopulationVarianceGenerator::generate(x) != 10.6666666666666660745477201999165117740631103515625\n";

    if(idk::SampleStandardDeviationGenerator::generate(idk::Vec<idk::isize> { 5, 5, 9, 9, 9, 10, 5, 10, 10 }) != 2.291287847477919914496169440099038183689117431640625)
        std::cerr << "[FAIL] idk::SampleStandardDeviationGenerator::generate(idk::Vec<idk::isize> { 5, 5, 9, 9, 9, 10, 5, 10, 10 }) != 2.291287847477919914496169440099038183689117431640625\n";
    else
        std::cout << "[OK] idk::SampleStandardDeviationGenerator::generate(idk::Vec<idk::isize> { 5, 5, 9, 9, 9, 10, 5, 10, 10 }) != 2.291287847477919914496169440099038183689117431640625\n";

    if(idk::PopulationStandardDeviationGenerator::generate(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 }) !=
        std::sqrtl(idk::PopulationVarianceGenerator::generate(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 })))
        std::cerr << "[FAIL] idk::PopulationStandardDeviationGenerator(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 }) != std::sqrtl(idk::PopulationVarianceGenerator(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 }))\n";
    else
        std::cout << "[OK] idk::PopulationStandardDeviationGenerator(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 }) != std::sqrtl(idk::PopulationVarianceGenerator(idk::Vec<idk::isize> { 2, 3, 5, 7, 11, 13, 17, 19 }))\n";
}