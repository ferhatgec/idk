#include "../queue.hpp"
#include <iostream>

int main() {
    idk::Queue<idk::u16> val;
    val.push(2);
    val.push(3);
    val.push(5);
    val.push(7);

    if(val.top() != 2)
        std::cerr << "[FAIL] val.top() != 2\n";
    else
        std::cout << "[OK] val.top() != 2\n";

    val.pop();

    if(val.top() != 3)
        std::cerr << "[FAIL] val.top() != 3\n";
    else
        std::cout << "[OK] val.top() != 3\n";
}