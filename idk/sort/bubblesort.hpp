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
class BubbleSort : public SortBase<Type> {
public:
    BubbleSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    BubbleSort(Vec<Type>&& vec) noexcept {
        this->_vec = idk::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_bubblesort(comp);
    }
private:
    template<typename Compare>
    void
    _bubblesort(Compare comp) noexcept {
        isize n = this->_vec.size();

        do {
            isize new_n = 0;

            for(isize i = 1; i <= (n - 1); ++i) {
                if(!comp(this->_vec.at_without_check(i - 1), this->_vec.at_without_check(i))) {
                    auto _temp = this->_vec.at_without_check(i - 1),
                         _temp2= this->_vec.at_without_check(i);

                    (void)this->_vec.change_val_at_index(i - 1, _temp2);
                    (void)this->_vec.change_val_at_index(i, _temp);
                    
                    new_n = i;
                }
            }

            n = new_n;
        } while(!(n <= 1)); 
    }
};
} // namespace idk