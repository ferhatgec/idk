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
class MergeSort : public SortBase<Type> {
public:
    MergeSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    MergeSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_mergesort(0, this->_vec.size() - 1, comp);
    }
private:
    template<typename Compare>
    void
    _mergesort(isize left, isize right, Compare comp) noexcept {
        if(left < right) {
            isize middle = left + (right - left) / 2;

            this->_mergesort(left, middle, comp);
            this->_mergesort(middle + 1, right, comp);

            this->_merge(left, middle, right, comp);
        } 
    }

    template<typename Compare>
    void
    _merge(isize left, isize middle, isize right, Compare comp) noexcept {
        isize n1 = middle - left + 1,
              n2 = right - middle;

        Vec<Type> _left_vec(n1),
                  _right_vec(n2);

        for(isize i = 0; i < n1; ++i)
            (void)_left_vec.change_val_at_index(i, this->_vec.at_without_check(left + i));

        for(isize i = 0; i < n2; ++i)
            (void)_right_vec.change_val_at_index(i, this->_vec.at_without_check(middle + 1 + i));

        isize i { 0 },
              j { 0 },
              k = left;

        while(i < n1 && j < n2) {
            if(comp(_left_vec.at_without_check(i), _right_vec.at_without_check(j))) {
                (void)this->_vec.change_val_at_index(k, _left_vec.at_without_check(i));
                ++i;
            } else {
                (void)this->_vec.change_val_at_index(k, _right_vec.at_without_check(j));
                ++j;
            }

            ++k;
        }

        while(i < n1) {
            (void)this->_vec.change_val_at_index(k, _left_vec.at_without_check(i));
            ++i;
            ++k;
        }

        while(j < n2) {
            (void)this->_vec.change_val_at_index(k, _right_vec.at_without_check(j));
            ++j;
            ++k;
        }
    }
};
} // namespace idk