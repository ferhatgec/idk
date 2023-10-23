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

#include "factorial.hpp"

namespace idk {
template<usize N, usize R>
class __idk_nodiscard CombinationGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        return FactorialGenerator<N>::generate() / (FactorialGenerator<R>::generate() * FactorialGenerator<N - R>::generate());
    }
};

__idk_nodiscard
__idk_constexpr usize
generate_combination(const usize& n, const usize& r) noexcept {
    return generate_factorial(n) / (generate_factorial(r) * generate_factorial(n - r));
}

__idk_nodiscard
__idk_constexpr usize
generate_combination(usize&& n, usize&& r) noexcept {
    return generate_combination(n, r);
}
} // namespace idk