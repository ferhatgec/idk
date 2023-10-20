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
#include "sort_base.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename Type>
class CycleSort : public SortBase<Type> {
public:
    CycleSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    CycleSort(Vec<Type>&& vec) noexcept {
        this->_vec = idk::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_cyclesort(comp);
    }
private:
    template<typename Compare>
    void
    _cyclesort(Compare comp) noexcept {
        for(isize start = 0; start < this->_vec.size() - 1; ++start) {
            auto _val = this->_vec.at_without_check(start);
            isize _pos = start;

            for(isize i = start + 1; i < this->_vec.size(); ++i)
                if(comp(this->_vec.at_without_check(i), _val))
                    ++_pos;

            if(_pos == start)
                continue;

            while(_val == this->_vec.at_without_check(_pos))
                ++_pos;

            auto _temp = this->_vec.at_without_check(_pos);
            
            (void)this->_vec.change_val_at_index(_pos, _val);
            _val = _temp;

            while(_pos != start) {
                _pos = start;

                for(isize i = start + 1; i < this->_vec.size(); ++i)
                    if(comp(this->_vec.at_without_check(i), _val))
                        ++_pos;

                while(_val == this->_vec.at_without_check(_pos))
                    ++_pos;

                
                auto _temp = this->_vec.at_without_check(_pos);
            
                (void)this->_vec.change_val_at_index(_pos, _val);
                _val = _temp;
            }
        }
    }
};
} // namespace idk