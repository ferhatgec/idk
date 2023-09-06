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
class [[nodiscard]] FrontAndBackSearch : public SearchBase<Type> {
public:
    FrontAndBackSearch(const Vec<Type>& arr) {
        this->_arr = arr; 
    }
    FrontAndBackSearch(Vec<Type>&& arr) {
        this->_arr = std::move(arr);
    }

    FrontAndBackSearch () = default;
    ~FrontAndBackSearch() = default;

    [[nodiscard]]
    isize
    find(Type& find_val) noexcept override {
        usize front_index = 0, 
              back_index = this->_arr.size() - 1;

        while(front_index <= back_index) {
            if(this->_arr[front_index].try_get_value() == find_val)
                return front_index;
            else if(this->_arr[back_index].try_get_value() == find_val)
                return back_index;

            ++front_index;
            --back_index;
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

        usize front_index = 0, 
              back_index = this->_arr.size() - 1;

        while(front_index <= back_index) {
            if(this->_arr[front_index].try_get_value() == find_val)
                index_arr.push_back(front_index);
            else if(this->_arr[back_index].try_get_value() == find_val)
                index_arr.push_back(back_index);

            ++front_index;
            --back_index;
        }

        return index_arr;
    }

    [[nodiscard]]
    Vec<isize>
    find_recursively(Type&& find_val) noexcept override {
        return this->find_recursively(find_val);
    }
};
} // namespace idk