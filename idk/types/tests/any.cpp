#include <iostream>
#include "../stringview.hpp"
#include "../any.hpp"

int main() {
    idk::Any x = idk::StringViewChar("Hello world!");
    
    if(auto val = x.cast_to<idk::StringViewChar>(); val.has_value()) {
        if(val.try_get_value() != "Hello world!")
            std::cerr << "[FAIL] val.try_get_value() != \"Hello world!\"\n";
        else
            std::cout << "[OK] val.try_get_value() != \"Hello world!\"\n";
    }
}