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
class SelectionSort : public SortBase<Type> {
public:
    SelectionSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    SelectionSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_selectionsort(comp);
    }
private:
    template<typename Compare>
    void
    _selectionsort(Compare comp) noexcept {
        isize i, j;

        for(i = 0; i < this->_vec.size() - 1; ++i) {
            isize min_j = i;

            for(j = i + 1; j < this->_vec.size(); ++j)
                if(comp(this->_vec.at_without_check(j), this->_vec.at_without_check(min_j)))
                    min_j = j;
        
            
            if(min_j != i) {
                auto _temp = this->_vec.at_without_check(i),
                     _temp2= this->_vec.at_without_check(min_j);

                (void)this->_vec.change_val_at_index(i, _temp2);
                (void)this->_vec.change_val_at_index(min_j, _temp);
            }
        }
    }
};
} // namespace idk