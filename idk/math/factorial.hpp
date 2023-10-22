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

namespace idk {
template<usize N>
class [[nodiscard]] FactorialGenerator {
public:
    [[nodiscard]]
    static constexpr usize 
    generate() noexcept {
        return N * FactorialGenerator<N - 1>::generate();
    }
};

template<>
class [[nodiscard]] FactorialGenerator<0> {
public:
    [[nodiscard]]
    static constexpr usize
    generate() noexcept {
        return 1;
    }
};

[[nodiscard]]
constexpr usize
generate_factorial(const usize& nth) noexcept {
    if(nth == 0)
        return 1;

    return nth * generate_factorial(nth - 1);
}

[[nodiscard]]
constexpr usize
generate_factorial(usize&& nth) noexcept {
    return generate_factorial(nth);
}
} // namespace idk