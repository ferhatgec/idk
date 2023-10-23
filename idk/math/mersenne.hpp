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
class MersenneGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        return (1_usize << N) - 1_usize;
    }  
};

__idk_nodiscard
__idk_constexpr usize
generate_mersenne(const usize& nth) noexcept {
    usize n { 1 };

    for(isize i = 0; i < nth; ++i) {
        n *= 2;
    }

    return n - 1;
}

__idk_nodiscard
__idk_constexpr usize
generate_mersenne(usize&& nth) noexcept {
    return generate_mersenne(nth);
}
} // namespace idk