#include <iostream>
#include "../forward_list.hpp"

int main() {
    idk::ForwardList<idk::usize> x;

    x.push_front(5);

    if(x[0].try_get_value() != 5)
        std::cerr << "[FAIL] x[0].try_get_value() != 5\n";
    else
        std::cout << "[OK] x[0].try_get_value() != 5\n";

    x.push_front(3);

    if(x[0].try_get_value() != 3)
        std::cerr << "[FAIL] x[0].try_get_value() != 3\n";
    else
        std::cout << "[OK] x[0].try_get_value() != 3\n";


    if(x.size() != 2)
        std::cerr << "[FAIL] x.size() != 2\n";
    else
        std::cout << "[OK] x.size() != 2\n";

    idk::ForwardList<idk::usize> y {
        1, 2, 3
    };

    std::cout << y << '\n';
    
    if(x == y)
        std::cerr << "[FAIL] x == y\n";
    else
        std::cout << "[OK] x == y\n";

    y.at_without_check_reference(0) = 13;

    if(y.at_without_check_reference(0) != 13)
        std::cerr << "[FAIL] y.at_without_check_reference(0) != 13\n";
    else
        std::cout << "[OK] y.at_without_check_reference(0) != 13\n";
}