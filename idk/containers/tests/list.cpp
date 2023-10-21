#include "../list.hpp"
#include <iostream>

int main() {
    idk::List<unsigned> x = {
        2, 3
    };

    x.push_back(4);
    x.push_front(1);

    for(auto& val: x) {
        std::cout << val << '\n';
    }

    std::cout << x.at(0).try_get_value() << " " << x.at(3).try_get_value() << '\n';

    x.at_without_check_reference(0) = 3;

    if(x.at_without_check_reference(0) != 3)
        std::cerr << "[FAIL] x.at_without_check_reference(0) != 3\n";
    else
        std::cout << "[OK] x.at_without_check_reference(0) != 3\n";
}