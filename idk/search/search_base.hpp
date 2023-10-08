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
#include "../containers/vector.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename Type>
class [[nodiscard]] SearchBase {
public:
    Vec<Type> _arr;

    explicit SearchBase(Vec<Type>&& vec) noexcept {
        this->_arr = idk::move(vec);
    }

    explicit SearchBase(const Vec<Type>& vec) noexcept {
        this->_arr = vec;
    }

    SearchBase () = default;
    ~SearchBase() = default;

    [[nodiscard]]
    virtual isize
    find(Type& find_val) noexcept {
        return -1;
    }
    
    [[nodiscard]]
    virtual isize
    find(Type&& find_val) noexcept {
        return -1;
    }

    [[nodiscard]]
    virtual Vec<isize>
    find_recursively(Type& find_val) noexcept {
        return Vec<isize>();
    }

    [[nodiscard]]
    virtual Vec<isize>
    find_recursively(Type&& find_val) noexcept {
        return Vec<isize>();
    }
};
} // namespace idk