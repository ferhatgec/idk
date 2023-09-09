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

#include "gcd.hpp"

namespace idk {
template<usize N, usize R>
class [[nodiscard]] LeastCommonMultipleGenerator {
    static constexpr auto _val = GreatestCommonDivisorGenerator<N, R>::generate();
public:
    [[nodiscard]]
    static constexpr usize 
    generate() noexcept {
        return (N * R) / ((_val == 0) ? 1 : _val);
    }
};
} // namespace idk