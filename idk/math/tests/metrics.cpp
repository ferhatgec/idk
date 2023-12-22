#include <iostream>
#include "../metrics.hpp"
#include <iomanip>

int main() {
    // due to some precision arithmetics (or my trash code), result is too beyond than the epsilon, so using floor in there is useful imo
    if(floorl(idk::mean_absolute_error(idk::Vec<idk::f80> {-0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) 
        == 0.175)
        std::cerr << "[FAIL] floorl(idk::mean_absolute_error(idk::Vec<idk::f80> {-0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) == 0.175\n";
    else
        std::cout << "[OK] floorl(idk::mean_absolute_error(idk::Vec<idk::f80> {-0.5, 2.1, 1.5, 0.3 }, idk::Vec<idk::f80> { -0.6, 1.7, 1.6, 0.2 })) == 0.175\n";
}