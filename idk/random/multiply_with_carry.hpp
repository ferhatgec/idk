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
class MultiplyWithCarry : public idk::RandomBase<Type> {
    static __idk_constexpr u64 _c = 6364136223846793005ULL;
public:
    MultiplyWithCarry(Type&& start, Type&& end) noexcept {
        this->_btw_start_pos = idk::move(start);
        this->_btw_end_pos   = idk::move(end);
        this->init();
    }
    
    MultiplyWithCarry(usize seed) noexcept {
        this->_seed = seed;
        this->init();
    }

    MultiplyWithCarry () = default;
    ~MultiplyWithCarry() = default;

    Type
    take() noexcept {
        this->_seed = this->_c * this->_seed + 1;
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

using MultiplyWithCarryClass     = MultiplyWithCarry<u32>;
using MultiplyWithCarryGenerator = MultiplyWithCarry<u32>;
} // namespace idk