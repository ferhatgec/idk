// idk libraries
// -------------
// disclaimer: don't forget that, idk libraries are not focused on replacing 
// standard library. (for some standard classes are directly being replaced by compiler, 
//                    like initializer_list will need compiler dependent codes)
// so, this is not *directly* an alternative to stl, some class- and functions may have different naming
// different outputs or attributes etc.
//
// MIT License
//
// Copyright (c) 2023 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "../types/predefined.hpp"
#include "../utilities/type_traits.hpp"
#include "../utilities/loop.hpp"

namespace idk {
// maybe using sieve of atkin / sieve of eratosthenes 
// much better idea for stability; but also bad for memory complexity.
[[nodiscard]]
constexpr bool
is_prime(const usize& n) noexcept {
    if(n == 2 || n == 3)
        return true;

    if(n < 2 || n % 2 == 0 || n % 3 == 0)
        return false;

    isize i = 5;
    bool prime { true };
    
    for(; i * i <= n; i += 6)
        if(n % i == 0 || n % (i + 2) == 0)
            return false;
    
    return true;
}

[[nodiscard]]
constexpr bool
is_prime(usize&& n) noexcept {
    return is_prime(n);
}

[[nodiscard]]
constexpr usize
generate_prime(const usize& nth) noexcept {
    isize n = 0,
          i = 3;

    while(n != nth) {
        if(is_prime(i++))
            ++n;
    }

    return i - 1;
}

[[nodiscard]]
constexpr usize
generate_prime(usize&& nth) noexcept {
    return generate_prime(nth);
}

template<isize N>
class [[nodiscard]] PrimeCheck {
public:
    // commentlined code removed due to template recursion limitations
    // (it can be bypassed by compiler flags but it's probably compiler specific
    // and messing with the compiler is not useful in this case)
    [[nodiscard]]
    static constexpr bool
    check() noexcept {
        return is_prime(N);
        /*if constexpr(N % 2 == 0 || N % 3 == 0)
            return false;

        isize i = 5;
        bool prime { true };
        
        idk::Loop<(N - 5) / 6>([&](idk::usize n) {
            if(N % i == 0 || N % (i + 2) == 0)
                prime = false;

            i += 6;
        });

        return prime;*/
    }
};

template<>
class [[nodiscard]] PrimeCheck<0> {
public:
    [[nodiscard]]
    static constexpr bool
    check() noexcept {
        return false;
    }
};

template<>
class [[nodiscard]] PrimeCheck<1> {
public:
    [[nodiscard]]
    static constexpr bool
    check() noexcept {
        return false;
    }
};

template<>
class [[nodiscard]] PrimeCheck<2> {
public:
    [[nodiscard]]
    static constexpr bool
    check() noexcept {
        return true;
    }
};

template<>
class [[nodiscard]] PrimeCheck<3> {
public:
    [[nodiscard]]
    static constexpr bool
    check() noexcept {
        return true;
    }
};

template<usize N>
class [[nodiscard]] PrimeGenerator {
public:
    [[nodiscard]]
    static constexpr usize
    generate() noexcept {
        return generate_prime(N);
    }
};
} // namespace idk