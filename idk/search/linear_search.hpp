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

#include "search_base.hpp"

namespace idk {
template<typename Type>
class [[nodiscard]] LinearSearch : public SearchBase<Type> {
public:
    LinearSearch(const Vec<Type>& arr) {
        this->_arr = arr; 
    }
    LinearSearch(Vec<Type>&& arr) {
        this->_arr = std::move(arr);
    }

    LinearSearch () = default;
    ~LinearSearch() = default;

    [[nodiscard]]
    isize
    find(Type& find_val) noexcept override {
        for(isize n = 0; n < this->_arr.size(); ++n) {
            if(this->_arr[n].try_get_value() == find_val)
                return n;
        }

        return -1;
    }

    [[nodiscard]]
    isize
    find(Type&& find_val) noexcept override {
        return this->find(find_val);
    }

    [[nodiscard]]
    Vec<isize> 
    find_recursively(Type& find_val) noexcept override {
        Vec<isize> index_arr;

        for(isize n = 0; n < this->_arr.size(); ++n)
            if(this->_arr[n].try_get_value() == find_val)
                index_arr.push_back(n);

        return index_arr;
    }

    [[nodiscard]]
    Vec<isize>
    find_recursively(Type&& find_val) noexcept override {
        return this->find_recursively(find_val);
    }
};
} // namespace idk