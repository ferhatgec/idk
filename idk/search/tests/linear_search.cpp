#include <iostream>
#include "../search.hpp"

int main() {
    const idk::Vec<idk::i32> sequence = {
        1, 1, 2, 3, 5, 8, 13, 21, 34, 55
    };

    idk::LinearSearch<idk::i32> val(sequence);

    if(val.find(5) != 4)
        std::cerr << "[FAIL] val.find(5) != 4\n";
    else
        std::cout << "[OK] val.find(5) != 4\n";

    if(val.find_recursively(1).size() != 2)
        std::cerr << "[FAIL] val.find_recursively(1).size() != 2\n";
    else
        std::cout << "[OK] val.find_recursively(1).size() != 2\n";
}