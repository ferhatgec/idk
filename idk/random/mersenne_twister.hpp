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
#include "../containers/array.hpp"

namespace idk {
template<typename Type>
class MersenneTwister : public idk::RandomBase<Type> {
    static constexpr u32 _n         = 624       ;
    static constexpr u32 _m         = 397       ;
    static constexpr u32 _matrix_a  = 0x9908b0df;
    static constexpr u32 _upper_mask= 0x80000000;
    static constexpr u32 _lower_mask= 0x7fffffff;

    idk::Arr<u32, _n> _state {};
    u32 _index { 0 };
public:
    MersenneTwister(Type&& start, Type&& end) noexcept {
        _state.fill(0);
        this->_btw_start_pos = std::move(start);
        this->_btw_end_pos   = std::move(end);
        this->init();
    }
    
    MersenneTwister(usize seed) noexcept {
        _state.fill(0);
        this->_seed = seed;
        this->init();
    }

    MersenneTwister() noexcept {
        this->_state.fill(0);
        // you need to call init() when seed is applied.
    }

    ~MersenneTwister() = default;

    Type
    take() noexcept {
        if(this->_index >= this->_n)
            this->_twist();

        Type y = this->_state[this->_index++].try_get_value();
        
        y ^= ((y >> 11) & 0xffffffff);
        y ^= ((y << 7) & 0x9d2c5680);
        y ^= ((y << 15) & 0xefc60000);
        y ^= (y >> 18);

        return (y % (this->_btw_end_pos - this->_btw_start_pos + 1) + this->_btw_start_pos);
    }

    Type
    operator()() {
        return this->take();
    }
    
    void
    init() noexcept {
        (void)this->_state.change_val_at_index(0, this->_seed);

        for(usize i = 1; i < this->_n; ++i)
            (void)this->_state.change_val_at_index(
                i, 
                1812433253UL * (this->_state[i - 1].try_get_value() ^
                                (this->_state[i - 1].try_get_value() >> 30))
            );

        this->_index = this->_n;
    }
private:
    void
    _twist() noexcept {
        for(usize i = 0; i < this->_n; ++i) {
            usize x = (this->_state[i].try_get_value() & this->_upper_mask) 
                        + (this->_state[(i + 1) % this->_n].try_get_value() & this->_lower_mask);
            usize xa= x >> 1;

            if(x % 2 != 0)
                xa ^= this->_matrix_a;

            (void)this->_state.change_val_at_index(i, this->_state[(i + this->_m) % this->_n].try_get_value() ^ xa);
        }

        this->_index = 0;
    }
};

using MersenneTwisterClass     = MersenneTwister<u32>;
using MersenneTwisterGenerator = MersenneTwister<u32>;
} // namespace idk