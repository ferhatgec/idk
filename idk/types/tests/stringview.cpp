#include "../stringview.hpp"
#include <iostream>

int main() {
    idk::StringViewChar x("      Test"),
                        l(x);
    
    x.trim_spaces_left();
    l.trim_spaces();

    char abc[] = "Hello";
    x.copy_n(abc, 1, 2);
    
    if(x.contains('T') && x.contains("es"))
        std::cout << "[OK] x.contains('T') && x.contains(\"es\")\n";
    else 
        std::cerr << "[FAIL] x.contains('T') && x.contains(\"es\")\n";
    
    if(x.starts_with('T') && x.ends_with('t'))
        std::cout << "[OK] x.starts_with('T') && x.ends_with('t')\n";
    else
        std::cerr << "[FAIL] x.starts_with('T') && x.ends_with('t')\n";

    if(x.starts_with("Test") == x.ends_with("Test"))
        std::cout << "[OK] x.starts_with(\"Test\") == x.ends_with(\"Test\")\n";
    else
        std::cerr << "[FAIL] x.starts_with(\"Test\") == x.ends_with(\"Test\")\n";

    if(auto v = x.substr(1, 2); !v.is_empty())
        std::cout << v << '\n';
    
    std::cout << abc << " " << x << ' ' << l << ' ' << x + l << '\n';

    if((x + l) == "TestTest")
        std::cout << "[OK] (x + l) == \"TestTest\"\n";
    else
        std::cerr << "[FAIL] (x + l) == \"TestTest\"\n";

    idk::StringViewChar test = "idk";

    std::cout << test << '\n';

    test.clear();

    if(!test.is_empty())
        std::cerr << "[FAIL] !test.is_empty()\n";
    else
        std::cout << "[OK] !test.is_empty()\n";
}