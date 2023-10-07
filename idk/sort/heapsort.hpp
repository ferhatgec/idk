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
#include <cmath>

namespace idk {
template<typename Type>
class HeapSort : public SortBase<Type> {
public:
    HeapSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    HeapSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_heapsort(comp);
    }
private:
    template<typename Compare>
    void
    _heapsort(Compare comp) noexcept {
        isize n = this->_vec.size();

        for(isize i = n / 2 - 1; i >= 0; --i)
            this->_heapify(n, i, comp);
        
        for(isize i = n - 1; i > 0; --i) {
            auto _temp = this->_vec.at_without_check(0),
                 _temp2= this->_vec.at_without_check(i);
                
            (void)this->_vec.change_val_at_index(0, _temp2);
            (void)this->_vec.change_val_at_index(i, _temp);

            this->_heapify(i, 0, comp);
        }
    }

    template<typename Compare>
    void
    _heapify(isize n, isize i, Compare comp) noexcept {
        isize largest = i,
              left = 2 * i + 1,
              right = 2 * i + 2;

        if(left < n && !comp(this->_vec.at_without_check(left), this->_vec.at_without_check(largest)))
            largest = left;

        if(right < n && !comp(this->_vec.at_without_check(right), this->_vec.at_without_check(largest)))
            largest = right;

        if(largest != i) {
            auto _temp = this->_vec.at_without_check(i),
                 _temp2= this->_vec.at_without_check(largest);

            (void)this->_vec.change_val_at_index(i, _temp2);
            (void)this->_vec.change_val_at_index(largest, _temp);

            this->_heapify(n, largest, comp);
        }
    }
};
} // namespace idk