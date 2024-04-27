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
#include "type_traits.hpp"

namespace idk {
template<typename Type>
__idk_nodiscard
__idk_constexpr Type&&
forward(idk::RemoveReferenceType<Type>& val) noexcept {
    return static_cast<Type&&>(val);
}

template<typename Type>
__idk_nodiscard
__idk_constexpr Type&&
forward(idk::RemoveReferenceType<Type>&& val) noexcept {
    static_assert(!idk::IsLvalueReferenceVal<Type>, "idk::forward(&&): cannot forward rvalue as lvalue.");
    return static_cast<Type&&>(val);
}

template<typename Type>
__idk_nodiscard
__idk_constexpr idk::RemoveReferenceType<Type>&&
move(Type&& val) noexcept {
    return static_cast<idk::RemoveReferenceType<Type>&&>(val);
}

// TODO: overload idk::swap for default containers such as idk::Vec, idk::Arr etc.
template<typename Type>
__idk_constexpr void
swap(Type& left, Type& right) noexcept {
    auto _left = idk::move(left);
    
    left       = idk::move(right);
    right      = idk::move(_left);
}
} // namespace idk