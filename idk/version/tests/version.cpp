#include <iostream>
#include "../version.hpp"

int main() {
    idk::Version x(1, 3, 1, idk::Beta, 3),
                 y(1, 3, 1, idk::Rc, 1);

    std::cout <<  x.as_str() << " " << y.as_str() << '\n';

    if(x > y)
        std::cerr << "[FAIL] x > y\n";
    else
        std::cout << "[OK] x > y\n";

    if(idk::Version(1, 3, 1, idk::Beta, 1) != idk::Version(1, 3, 1, idk::Beta, 1))
        std::cerr << "[FAIL] idk::Version(1, 3, 1, idk::Beta, 1) != idk::Version(1, 3, 1, idk::Beta, 1)\n";
    else
        std::cout << "[OK] idk::Version(1, 3, 1, idk::Beta, 1) != idk::Version(1, 3, 1, idk::Beta, 1)\n";

    if(idk::Version(1, 3, 1, idk::Beta, 2) <= idk::Version(1, 3, 1, idk::Beta, 1))
        std::cerr << "[FAIL] idk::Version(1, 3, 1, idk::Beta, 2) <= idk::Version(1, 3, 1, idk::Beta, 1)\n";
    else
        std::cout << "[OK] idk::Version(1, 3, 1, idk::Beta, 2) <= idk::Version(1, 3, 1, idk::Beta, 1)\n";

    if(x.build("major.minor-tag") != "1.3-beta")
        std::cerr << "[FAIL] x.build(\"major.minor-tag\") != \"1.3-beta\"\n";
    else
        std::cout << "[OK] x.build(\"major.minor-tag\") != \"1.3-beta\"\n";
}