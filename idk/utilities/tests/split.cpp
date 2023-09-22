#include <iostream>
#include "../split.hpp"
#include "../../types/stringview.hpp"

int main() {
    idk::StringViewChar x = "Hello, worlld!";
    
    if(idk::split<char>(x, "ll") != (idk::Vec<idk::StringViewChar> { "He", "o, wor", "d!" }))
        std::cerr << "[FAIL] idk::split<char>(x, \"ll\") != (idk::Vec<idk::StringViewChar> { \"He\", \"o, wor\", \"d!\" })\n";
    else
        std::cout << "[OK] idk::split<char>(x, \"ll\") != (idk::Vec<idk::StringViewChar> { \"He\", \"o, wor\", \"d!\" })\n";

    if(idk::split<char>(x) != (idk::Vec<idk::StringViewChar> { "Hello,", "worlld!" }))
        std::cerr << "[FAIL] idk::split<char>(x) != (idk::Vec<idk::StringViewChar> { \"Hello,\", \"worlld!\" })\n";
    else
        std::cout << "[OK] idk::split<char>(x) != (idk::Vec<idk::StringViewChar> { \"Hello,\", \"worlld!\" })\n";

    idk::Vec<idk::u32> y { 0, 1, 1, 0, 0, 1, 1, 1 };

    if(idk::split(y, { 1 }) != (idk::Vec<idk::u32> { 0, 0, 0 }))
        std::cerr << "[FAIL] idk::split(y, { 1 }) != (idk::Vec<idk::u32> { 0, 0, 0 })\n";
    else
        std::cout << "[OK] idk::split(y, { 1 }) != (idk::Vec<idk::u32> { 0, 0, 0 })\n";

    if(!idk::split(y, { 1, 0 }).is_empty())
        std::cerr << "[FAIL] !idk::split(y, { 1, 0 }).is_empty()\n";
    else
        std::cout << "[OK] !idk::split(y, { 1, 0 }).is_empty()\n";

}