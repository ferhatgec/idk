#include "../vector.hpp"
#include <iostream>
#include "../../types/stringview.hpp"

int main() {
    const idk::u8 _num = 1;
    idk::Vec<idk::u8> val(10, _num);
    
    idk::Vec<idk::StringViewChar> str_view_vector;
    
    str_view_vector.push_back(idk::StringViewChar("Hello world!"));
    str_view_vector.push_back(idk::StringViewChar("Hello world!"));

    
    if(str_view_vector.back_no_reference().try_get_value() != "Hello world!")
        std::cerr << "[FAIL] str_view_vector.back_no_reference().try_get_value() != \"Hello world!\"\n";
    else
        std::cout << "[OK] str_view_vector.back_no_reference().try_get_value() != \"Hello world!\"\n";
        
    
    // std::cout << val << '\n';
    
    for(auto& asd : val) {
        asd = 12;
    }
    
    val.push_back(5);
    val.push_back(5);
    val.push_back(5);
    val.push_back(5);
    val.push_back(5);

    std::cout << str_view_vector << '\n';

    for(auto& asd: val) {
        std::cout << static_cast<idk::u16>(asd) << '\n';
    }

    val.front() = 0;

    
    if(val.find(0) != 0)
        std::cerr << "[FAIL] val.find(0) != 0\n";
    else
        std::cout << "[OK] val.find(0) != 0\n";

    if(val.find(333) != -1)
        std::cerr << "[FAIL] val.find(333) != -1\n";
    else
        std::cout << "[OK] val.find(333) != -1\n";

    if(auto x = val.front_no_reference(); x.has_value()) {
        std::cout << static_cast<idk::u16>(x._expected.get_value()) << '\n';
    }

    idk::Vec<std::string> test(10, std::string("test"));

    std::cout << test.at_without_check(9) << '\n';

    idk::Vec<unsigned> numbers = {
        1, 2, 3, 5, 8, 13, 21, 34
    };

    if(numbers.back_no_reference().try_get_value() != 34)
        std::cerr << "[FAIL] numbers.back_no_reference().try_get_value() != 34\n";
    else
        std::cout << "[OK] numbers.back_no_reference().try_get_value() != 34\n";

    if(!numbers.contains(3))
        std::cerr << "[FAIL] !numbers.contains(3)\n";
    else
        std::cout << "[OK] !numbers.contains(3)\n";
}