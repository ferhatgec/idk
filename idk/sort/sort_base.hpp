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
#include <utility>

namespace idk {
template<typename Type>
struct Greater {
    bool
    operator()(const Type& lhs, const Type& rhs) noexcept {
        return lhs > rhs;
    } 
};

template<typename Type>
struct Less {
    bool
    operator()(const Type& lhs, const Type& rhs) noexcept {
        return lhs < rhs;
    } 
};

template<typename Type>
class [[nodiscard]] SortBase {
public:
    Vec<Type> _vec;
    
    explicit SortBase(const Vec<Type>& vec) noexcept : _vec(vec) {}
    explicit SortBase(Vec<Type>&& vec) noexcept : _vec(std::move(vec)) {}

    SortBase() = default;
    ~SortBase() = default;

//    virtual void
//    sort(Compare comp) noexcept {}
};
} // namespace idk