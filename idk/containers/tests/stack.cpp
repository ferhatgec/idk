#include "../stack.hpp"
#include <iostream>

int main() {
    idk::Stack<idk::u16> val;

    val.push(2);
    val.push(3);
    val.push(5);
    val.push(7);

    if(val.top() != 7)
        std::cerr << "[FAIL] val.top() != 7\n";
    else
        std::cout << "[OK] val.top() != 7\n";

    val.pop();

    if(val.top() != 5)
        std::cerr << "[FAIL] val.top() != 5\n";
    else
        std::cout << "[OK] val.top() != 5\n";
        
}