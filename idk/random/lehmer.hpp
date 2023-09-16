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
class Lehmer : public idk::RandomBase<Type> {
    static constexpr u64 _a = 16807     ;
    static constexpr u64 _m = 2147483647; // using Park & Miller's suggested constants.
public:
    Lehmer(Type&& start, Type&& end) noexcept {
        this->_btw_start_pos = std::move(start);
        this->_btw_end_pos   = std::move(end);
        this->init();
    }
    
    Lehmer(usize seed) noexcept {
        this->_seed = seed;
        this->init();
    }

    Lehmer () = default;
    ~Lehmer() = default;
    
    Type
    take() noexcept {
        this->_seed = (this->_a * this->_seed) % this->_m;
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

using LehmerClass     = Lehmer<u32>;
using LehmerGenerator = Lehmer<u32>;
} // namespace idk