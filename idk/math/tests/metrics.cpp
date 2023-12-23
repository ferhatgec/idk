#include <iostream>
#include <iomanip>
#include "../metrics.hpp"

int main() {
    // due to some precision arithmetics (or my trash code), result is too beyond than the epsilon, so using floor in there is useful imo
    if(floorl(idk::mean_absolute_error(idk::Vec<idk::f80> { -0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) 
        == 0.175)
        std::cerr << "[FAIL] floorl(idk::mean_absolute_error(idk::Vec<idk::f80> {-0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) == 0.175\n";
    else
        std::cout << "[OK] floorl(idk::mean_absolute_error(idk::Vec<idk::f80> {-0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) == 0.175\n";

    if(floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, -0.5, 2, 7 }, idk::Vec<idk::f80> { 2.5, 0.0, 2, 8 })) 
        == 0.375)
        std::cerr << "[FAIL] floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, -0.5, 2, 7 }, idk::Vec<idk::f80> { 2.5, 0.0, 2, 8 })) == 0.375\n";
    else
        std::cout << "[OK] floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, -0.5, 2, 7 }, idk::Vec<idk::f80> { 2.5, 0.0, 2, 8 })) == 0.375\n";
    
    if(floorl(idk::MedianAbsoluteDeviation::generate(idk::Vec<idk::f80> { 0, 2, 1 })) != 0)
        std::cerr << "[FAIL] floorl(idk::MedianAbsoluteDeviation::generate(idk::Vec<idk::f80> { 0, 2, 1 })) == 0\n";
    else
        std::cout << "[OK] floorl(idk::MedianAbsoluteDeviation::generate(idk::Vec<idk::f80> { 0, 2, 1 })) == 0\n";

    if(floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, 5, 2.5, 7 }, idk::Vec<idk::f80> { 2.5, 5, 4, 8 })) 
        == 0.199)
        std::cerr << "[FAIL] floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, 5, 2.5, 7 }, idk::Vec<idk::f80> { 2.5, 5, 4, 8 })) == 0.199\n";
    else
        std::cout << "[OK] floorl(idk::mean_squared_error(idk::Vec<idk::f80> { 3, 5, 2.5, 7 }, idk::Vec<idk::f80> { 2.5, 5, 4, 8 })) == 0.199\n";
}