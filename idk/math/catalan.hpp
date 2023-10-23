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
class __idk_nodiscard CatalanGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        return CatalanGenerator<N - 1>::generate() * (4 * N - 2) / (N + 1);
    }
};

template<>
class __idk_nodiscard CatalanGenerator<0> {
public:
    __idk_nodiscard
    static __idk_constexpr usize
    generate() noexcept {
        return 1;
    }
};

__idk_nodiscard
__idk_constexpr usize
generate_catalan(const usize& nth) noexcept {
    if(nth == 0)
        return 1;
    
    return generate_catalan(nth - 1) * (4 * nth - 2) / (nth + 1);
}

__idk_nodiscard
__idk_constexpr usize
generate_catalan(usize&& nth) noexcept {
    return generate_catalan(nth);
}
} // namespace idk