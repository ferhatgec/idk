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
#include "factorial.hpp"

namespace idk {
template<usize N>
class [[nodiscard]] DerangementGenerator {
    static constexpr auto _val = (FactorialGenerator<N>::generate() / idk::e) + 0.5;
public:
    [[nodiscard]]
    static constexpr usize 
    generate() noexcept {
        // floor(_val)
        return (_val >= 0) ? static_cast<usize>(_val) : (static_cast<usize>(_val) - 1);
    }
};

template<>
class [[nodiscard]] DerangementGenerator<0> {
public:
    [[nodiscard]]
    static constexpr usize
    generate() noexcept {
        return 1;
    }
};
} // namespace idk