#include "../stringview.hpp"
#include <iostream>

int main() {
    idk::StringViewChar x("      Test"),
                        l(x),
                        y("Test   "),
                        z = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                            "sed do eiusmod tempor incididunt ut labore et dolore magna"
                            "aliqua. Ut enim ad minim veniam, quis nostrud exercitation"
                            "ullamco laboris nisi ut aliquip ex ea commodo consequat."
                            "Duis aute irure dolor in reprehenderit in voluptate velit"
                            "esse cillum dolore eu fugiat nulla pariatur. Excepteur"
                            "sint occaecat cupidatat non proident, sunt in culpa qui"
                            "officia deserunt mollit anim id est laborum.";
        

    x.trim_spaces_left();

    
    if(x.find('T') != 0)
        std::cerr << "[FAIL] x.find('T') != 0\n";
    else
        std::cout << "[OK] x.find('T') != 0\n";
    
    if(z.find("anim id") != 418)
        std::cerr << "[FAIL] z.find(\"anim id\") != 418\n";
    else
        std::cout << "[OK] z.find(\"anim id\") != 418\n";

    if(x.find("es") != 1)
        std::cerr << "[FAIL] x.find(\"es\") != 1\n";
    else
        std::cout << "[OK] x.find(\"es\") != 1\n";

    l.trim_spaces();

    y.trim_spaces_right();

    if(y != "Test")
        std::cerr << "[FAIL] y != \"Test\"\n";
    else
        std::cout << "[OK] y != \"Test\"\n";

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

    test = "idk";

    if(test != "idk")
        std::cerr << "[FAIL] test != \"idk\"\n";
    else
        std::cout << "[OK] test != \"idk\"\n";

    idk::StringViewChar one_character('f');

    if(one_character != "f")
        std::cerr << "[FAIL] one_character != \"f\"\n";
    else
        std::cout << "[OK] one_character != \"f\"\n";
}