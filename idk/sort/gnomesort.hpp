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
class GnomeSort : public SortBase<Type> {
public:
    GnomeSort(const Vec<Type>& vec) noexcept {
        this->_vec = vec;
    }

    GnomeSort(Vec<Type>&& vec) noexcept {
        this->_vec = idk::move(vec);
    }

    template<typename Compare = decltype(idk::Less<Type>())>
    void
    sort(Compare comp = idk::Less<Type>()) noexcept {
        this->_gnomesort(comp);
    }
private:
    template<typename Compare>
    void
    _gnomesort(Compare comp) noexcept {
        isize pos = 0;

        while(pos < this->_vec.size()) {
            if(pos == 0 || (!comp(this->_vec.at_without_check_reference(pos), this->_vec.at_without_check_reference(pos - 1)) 
                        || this->_vec.at_without_check_reference(pos) == this->_vec.at_without_check_reference(pos - 1))) {
                ++pos;
            } else {
                auto _temp = this->_vec.at_without_check_reference(pos);

                (void)this->_vec.change_val_at_index(pos, this->_vec.at_without_check_reference(pos - 1));
                (void)this->_vec.change_val_at_index(pos - 1, _temp);
                --pos;
            }
        }
    }
};
} // namespace idk