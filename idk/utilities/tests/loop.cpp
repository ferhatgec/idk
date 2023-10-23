#include <iostream>
#include "../loop.hpp"

class Test {
    static __idk_constexpr idk::usize n = 3;
public:
    static __idk_constexpr void test() {
        idk::Loop<n>([&](auto) {
            std::cout << n << '\n';
        });
    }
};

int main() {
    idk::Loop<2>([](auto){
        std::cout << "Hello, world!\n";
    });

    idk::Loop<3>([](idk::usize i){
        std::cout << i << '\n';
    });

    Test::test();
}