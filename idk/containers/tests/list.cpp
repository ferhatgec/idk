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
}