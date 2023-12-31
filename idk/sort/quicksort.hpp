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

#include "sort_base.hpp"
#include "sort.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename Type>
class QuickSort : public SortBase<Type> {
public:
    QuickSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    QuickSort(Vec<Type>&& vec) noexcept {
        this->_vec = idk::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_quicksort(0, this->_vec.size() - 1, comp);
    }
private:
    template<typename Compare>
    void
    _quicksort(isize low, isize high, Compare comp) noexcept {
        if(low < high) {
            isize i = this->_partition(low, high, (comp));
            
            this->_quicksort(low, i - 1, (comp));
            this->_quicksort(i + 1, high, (comp));   
        }
    }

    template<typename Compare>
    __idk_nodiscard
    isize
    _partition(isize low, isize high, Compare comp) noexcept {
        Type pivot = this->_vec.at_without_check(high);
        isize i = low - 1;

        for(isize j = low; j <= (high - 1); ++j) {
            if(comp(this->_vec.at_without_check(j), pivot)) {
                ++i;

                const auto _temp = this->_vec.at_without_check(j),
                           _temp2= this->_vec.at_without_check(i);
        
                (void)this->_vec.change_val_at_index(i, _temp);
                (void)this->_vec.change_val_at_index(j, _temp2);
            }
        }

        ++i;
        
        const auto _temp = this->_vec[i].try_get_value(),
                   _temp2= this->_vec[high].try_get_value();

        (void)this->_vec.change_val_at_index(i, _temp2);
        (void)this->_vec.change_val_at_index(high, _temp);

        return i;
    }
};
} // namespace idk