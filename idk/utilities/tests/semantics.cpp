#include <iostream>
#include "../semantics.hpp"

void
fn2(idk::isize val) noexcept {
    std::cout << val << '\n';
}

void 
fn1(idk::isize&& val) noexcept {
    fn2(idk::move(val));
    fn2(idk::forward<idk::isize>(val));
}


int main() {
    fn1(3);

    idk::isize x { 31 },
               y { -42 };

    idk::swap(x, y);

    if(!(x == -42 && y == 31))
        std::cerr << "[FAIL] !(x == -42 && y == 31)\n";
    else
        std::cout << "[OK] !(x == -42 && y == 31)\n";
}