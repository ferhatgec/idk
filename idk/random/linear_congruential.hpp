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

#include "random_base.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename Type>
class LinearCongruential : public idk::RandomBase<Type> {
    static __idk_constexpr u64 _a = 1664525   ;
    static __idk_constexpr u64 _c = 1013904223;
    static __idk_constexpr u64 _m = 1013904223;
public:
    LinearCongruential(Type&& start, Type&& end) noexcept {
        this->_btw_start_pos = idk::move(start);
        this->_btw_end_pos   = idk::move(end);
        this->init();
    }
    
    LinearCongruential(usize seed) noexcept {
        this->_seed = seed;
        this->init();
    }

    LinearCongruential () = default;
    ~LinearCongruential() = default;

    Type
    take() noexcept {
        this->_seed = (this->_a * this->_seed + this->_c) % this->_m;
        return (this->_seed % (this->_btw_end_pos - this->_btw_start_pos + 1) + this->_btw_start_pos);
    }

    Type
    operator()() {
        return this->take();
    }
    
    void
    init() noexcept {
        return;
    }
};

using LinearCongruentialClass     = LinearCongruential<u32>;
using LinearCongruentialGenerator = LinearCongruential<u32>;
} // namespace idk