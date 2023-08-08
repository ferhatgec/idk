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

namespace idk {
template<typename Type>
class LinearCongruential : public idk::RandomBase<Type> {
    static constexpr u64 _a = 1664525   ;
    static constexpr u64 _c = 1013904223;
    static constexpr u64 _m = 1013904223;
    
    u32 _index { 0 };
public:
    LinearCongruential(Type&& start, Type&& end) noexcept {
        _state.fill(0);
        this->_btw_start_pos = std::move(start);
        this->_btw_end_pos   = std::move(end);
        this->init();
    }
    
    LinearCongruential(usize seed) noexcept {
        this->_seed = seed;
        this->init();
    }

    LinearCongruential() noexcept = default;

    Type
    take() noexcept {
        this->_seed = (this->_a * this->_seed + this->_c) % this->_m;
        return (this->_seed % (this->_btw_end_pos - this->_btw_start_pos + 1) + this->_btw_start_pos);
    }

    Type operator()() {
        return this->take();
    }
    
    void
    init() noexcept {
        return;
    }
private:
};

using LinearCongruentialClass = LinearCongruential<u32>;
} // namespace idk