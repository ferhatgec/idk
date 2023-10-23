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
template<usize N, usize R>
class __idk_nodiscard GreatestCommonDivisorGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        return (R == 0) ? N : GreatestCommonDivisorGenerator<R, N - (R * (N / ((R == 0) ? 1 : R)))>::generate();
    }
};

__idk_nodiscard
__idk_constexpr usize
generate_gcd(const usize& n, const usize& r) noexcept {
    if(r == 0)
        return n;
    
    return generate_gcd(r, n - (r * (n / ((r == 0) ? 1 : r))));
}

__idk_nodiscard
__idk_constexpr usize
generate_gcd(usize&& n, usize&& r) noexcept {
    return generate_gcd(n, r);
}
} // namespace idk