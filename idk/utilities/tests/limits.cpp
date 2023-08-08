#include "../limits.hpp"
#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");

    // taken from https://en.cppreference.com/w/cpp/types/numeric_limits
    std::cout
        << "type\t│ lowest()\t│ min()\t\t│ max()\n"
        << "bool\t│ "
        << idk::NumericLimits<bool>::lowest() << "\t\t│ "
        << idk::NumericLimits<bool>::min() << "\t\t│ "
        << idk::NumericLimits<bool>::max() << '\n'
        << "uchar\t│ "
        << +idk::NumericLimits<unsigned char>::lowest() << "\t\t│ "
        << +idk::NumericLimits<unsigned char>::min() << "\t\t│ "
        << +idk::NumericLimits<unsigned char>::max() << '\n'
        << "int\t│ "
        << idk::NumericLimits<int>::lowest() << "\t│ "
        << idk::NumericLimits<int>::min() << "\t│ "
        << idk::NumericLimits<int>::max() << '\n'
        << "float\t│ "
        << idk::NumericLimits<float>::lowest() << "\t│ "
        << idk::NumericLimits<float>::min() << "\t│ "
        << idk::NumericLimits<float>::max() << '\n'
        << "double\t│ "
        << idk::NumericLimits<double>::lowest() << "\t│ "
        << idk::NumericLimits<double>::min() << "\t│ "
        << idk::NumericLimits<double>::max() << '\n';
}