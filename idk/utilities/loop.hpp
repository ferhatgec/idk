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
#include "type_traits.hpp"

namespace idk {
template<idk::usize N, 
         idk::EnableIfType<static_cast<bool>(N >= 0), bool> = true>
class Loop {
public: 
    template<typename Fn, typename... Args>
    __idk_constexpr explicit Loop(Fn&& fn, Args&&... args) noexcept {
        fn(N);
        Loop<N - 1>(fn, args...);
    }
};

template<>
class Loop<0> {
public:
    template<typename Fn, typename... Args>
    __idk_constexpr explicit Loop(Fn&&, Args&&...) noexcept {}
};
} // namespace idk