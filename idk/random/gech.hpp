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
class Gech : public idk::RandomBase<Type> {
    u32 _index { 0 }, 
        _bits  { 1 };
public:
    Gech(Type&& start, Type&& end) noexcept {
        this->_btw_start_pos = idk::move(start);
        this->_btw_end_pos   = idk::move(end);
        this->init();
    }
    
    Gech(usize seed) noexcept {
        this->_seed = seed;
        this->init();
    }

    Gech () = default;
    ~Gech() = default;
    
    Type
    take() noexcept {
        this->_bits ^= (this->_seed >> 1) | (this->_seed >> 2) | (this->_seed >> 3) | (this->_seed >> 4);
        this->_bits  = (this->_bits >> 1) | (this->_bits >> 2) | (this->_bits >> 3) | (this->_bits >> 4);
        this->_bits *= (this->_bits >> 1) | (this->_seed >> 2) | (this->_bits >> 3) | (this->_seed >> 4);

        this->_bits |= (this->_seed << 1) ^ (this->_seed << 2) ^ (this->_seed << 3) ^ (this->_seed << 4);

        this->_seed <<= 32;
        
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

using GechClass     = Gech<u32>;
using GechGenerator = Gech<u32>;
} // namespace idk