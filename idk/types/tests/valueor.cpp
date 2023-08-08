#include "../valueor.hpp"
#include <iostream>

enum ErrorTypes {
    BlaBla,
    ExEx
};

idk::ValueOr<int, ErrorTypes>
test_function(bool&& x) {
    if(x) return idk::Unexpected<ErrorTypes>(ErrorTypes::ExEx);

    return idk::Expected<int>(12);
}

int main() {
    if(auto val = test_function(true); val.has_value()) {
        std::cout << "[FAIL] " << "test_function(true)::has_value()\n" 
                               << val._expected.get_value() << '\n';
    } else {
        std::cerr << "[OK] test_function(true)::has_value()\n";
        // std::cout << static_cast<int>(val._unexpected.get_value()) << '\n';
    }
}