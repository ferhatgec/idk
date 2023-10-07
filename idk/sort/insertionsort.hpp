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
#include <utility>

namespace idk {
template<typename Type>
class InsertionSort : public SortBase<Type> {
public:
    InsertionSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    InsertionSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_insertionsort(comp);
    }
private:
    template<typename Compare>
    void
    _insertionsort(Compare comp) noexcept {
        isize i = 1;

        while(i < this->_vec.size()) {
            isize j = i;

            while(j > 0 && !comp(this->_vec.at_without_check(j - 1), this->_vec.at_without_check(j))) {
                auto _temp = this->_vec.at_without_check(j),
                     _temp2= this->_vec.at_without_check(j - 1);

                (void)this->_vec.change_val_at_index(j, _temp2);
                (void)this->_vec.change_val_at_index(j - 1, _temp);

                --j;
            }

            ++i;
        }
    }
};
} // namespace idk