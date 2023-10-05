#include <iostream>
#include "../insertionsort.hpp"

const bool
Comp(idk::usize n, idk::usize y) noexcept {
    return n < y;
}

int main() {
    idk::Vec<idk::usize> n { 1, 2, 3, 9, 11, 2 };

    idk::InsertionSort<idk::usize> x(n);
    x.sort();

    if(x._vec != idk::Vec<idk::usize> { 1, 2, 2, 3, 9, 11 })
        std::cerr << "[FAIL] x._vec != idk::Vec<idk::usize> { 1, 2, 2, 3, 9, 11}\n";
    else
        std::cout << "[OK] x._vec != idk::Vec<idk::usize> { 1, 2, 2, 3, 9, 11}\n";

    x.sort(idk::Greater<idk::usize>());
    
    if(x._vec != idk::Vec<idk::usize> { 11, 9, 3, 2, 2, 1 })
        std::cerr << "[FAIL] x._vec != idk::Vec<idk::usize> { 11, 9, 3, 2, 2, 1 }\n";
    else
        std::cout << "[OK] x._vec != idk::Vec<idk::usize> { 11, 9, 3, 2, 2, 1 }\n";
}