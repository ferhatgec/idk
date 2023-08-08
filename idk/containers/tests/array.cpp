#include "../array.hpp"
#include <iostream>

int main() {
    idk::Arr<idk::i32, 2> val {
        1, 2
    };

    idk::Arr<idk::i32, 2> val2 {
        1, 2
    };

    if(val == val2)
        std::cout << "[OK] val == val2\n";
    else
        std::cerr << "[FAIL] val == val2\n";
    
    for(int& v: val) {
        std::cout << v << '\n';
    }

    if(val.change_val_at_index(0, -5) && val.at(0).try_get_value() != -5)
        std::cerr << "[FAIL] val.change_val_at_index(0, -5) && val.at(0).try_get_value() != -5\n";
    else
        std::cout << "[OK] val.change_val_at_index(0, -5) && val.at(0).try_get_value() != -5\n";
    
    val.front() = 3;

    if(val.at(0).try_get_value() != 3)
        std::cerr << "[FAIL] val.at(0).try_get_value() != 3\n";
    else
        std::cout << "[OK] val.at(0).try_get_value() != 3\n";

    auto result = val.back_no_reference();
    
    if(result.has_value()) {
        std::cout << result._expected.get_value() << '\n';
    }

    std::cout << val << '\n';
}