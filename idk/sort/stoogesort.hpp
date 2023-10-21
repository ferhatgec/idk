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
class StoogeSort : public SortBase<Type> {
public:
    StoogeSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    StoogeSort(Vec<Type>&& vec) noexcept {
        this->_vec = idk::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_stoogesort(comp, 0, this->_vec.size() - 1);
    }
private:
    template<typename Compare>
    void
    _stoogesort(Compare comp, isize low, isize high) noexcept {
        if(low >= high)
            return;

        if(!comp(this->_vec.at_without_check_reference(low), this->_vec.at_without_check_reference(high))) {
            auto _temp = this->_vec.at_without_check(low);

            (void)this->_vec.change_val_at_index(low, this->_vec.at_without_check(high));
            (void)this->_vec.change_val_at_index(high, _temp);
        }

        if((high - low + 1) >= 3) {
            isize t = (high - low + 1) / 3;
            this->_stoogesort(comp, low, high - t);
            this->_stoogesort(comp, low + t, high);
            this->_stoogesort(comp, low, high - t);
        }
    }
};
} // namespace idk