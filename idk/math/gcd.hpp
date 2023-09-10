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
class [[nodiscard]] GreatestCommonDivisorGenerator {
public:
    [[nodiscard]]
    static constexpr usize 
    generate() noexcept {
        return (R == 0) ? N : GreatestCommonDivisorGenerator<R, N - (R * (N / ((R == 0) ? 1 : R)))>::generate();
    }
};
} // namespace idk