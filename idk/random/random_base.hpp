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
template<typename Type>
class RandomBase {
public:
    RandomBase(const Type& start_pos, 
                const Type& end_pos) : _btw_start_pos(start_pos), _btw_end_pos(end_pos) {}
    RandomBase(Type start_pos, 
                Type end_pos) : _btw_start_pos(start_pos), _btw_end_pos(end_pos) {}
    RandomBase() = default;

    void 
    feed(usize seed = 0) noexcept {
        this->_seed = seed;
    }

    void
    feed(const usize& seed) noexcept {
        this->_seed = const_cast<usize&>(seed);
    }

    Type _btw_start_pos,
         _btw_end_pos;
        
    usize _seed { 0 };
private:
};
} // namespace idk