#include "../tuple.hpp"
#include <iostream>
#include "../stringview.hpp"

int main() {
    idk::Tuple<int, idk::StringViewChar> x(5, idk::StringViewChar("Hello world!"));
    
    if(x.Get<0>() != 5)
        std::cerr << "[FAIL] x.Get<0>() != 5\n";
    else
        std::cout << "[OK] x.Get<0>() != 5\n";
    
    std::cout << x.Get<0>() << " " << x.Get<1>() << ' ' << x.length() << ' ' << x.max_index() << '\n';
}