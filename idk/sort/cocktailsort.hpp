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
class CocktailSort : public SortBase<Type> {
public:
    CocktailSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    CocktailSort(Vec<Type>&& vec) noexcept {
        this->_vec = std::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_cocktailsort(comp);
    }
private:
    template<typename Compare>
    void
    _cocktailsort(Compare comp) noexcept {
        bool swapped = true;
        isize start { 0 }, 
              end = this->_vec.size() - 1;

        while(swapped) {
            swapped = false;

            for(isize i = start; i < end; ++i) {
                if(!comp(this->_vec.at_without_check(i), this->_vec.at_without_check(i + 1))) {
                    auto _temp = this->_vec.at_without_check(i),
                         _temp2= this->_vec.at_without_check(i + 1);
                    
                    (void)this->_vec.change_val_at_index(i, _temp2);
                    (void)this->_vec.change_val_at_index(i + 1, _temp);

                    swapped = true;
                }
            }

            if(!swapped)
                break;

            --end;

            swapped = false;

            for(isize i = end - 1; i >= start; --i) {
                if(!comp(this->_vec.at_without_check(i), this->_vec.at_without_check(i + 1))) {
                    auto _temp = this->_vec.at_without_check(i),
                         _temp2= this->_vec.at_without_check(i + 1);
                    
                    (void)this->_vec.change_val_at_index(i, _temp2);
                    (void)this->_vec.change_val_at_index(i + 1, _temp);

                    swapped = true;
                }
            }

            ++start;
        }
    }
};
} // namespace idk