#include <iostream>
#include "../loop.hpp"

class Test {
    static constexpr idk::usize n = 3;
public:
    static constexpr void test() {
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