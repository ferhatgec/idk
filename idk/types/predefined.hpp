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

// maybe using stdint.h directly would be much better great idea,
// there can be something implementation defined for older systems.
namespace idk {
using i8    = signed char       ;
using i16   = short             ;
using i32   = int               ;
using i64   = long long         ;

using u8    = unsigned char     ;
using u16   = unsigned short    ;
using u32   = unsigned int      ;
using u64   = unsigned long long;

using usize = unsigned long long;
using size  = long long         ;

constexpr usize cpp98 { 199711 },
                cpp11 { 201103 },
                cpp14 { 201402 },
                cpp17 { 201703 },
                cpp20 { 202002 },
                cpp23 { 202302 };

[[nodiscard]]
constexpr bool
is_cpp98_supported() noexcept {
    return true;
}

[[nodiscard]]
constexpr bool
is_cpp11_supported() noexcept {
    return true;
}

[[nodiscard]]
constexpr bool
is_cpp14_supported() noexcept {
    return true;
}

[[nodiscard]]
constexpr bool
is_cpp17_supported() noexcept {
    return true;
}

[[nodiscard]]
constexpr bool
is_cpp20_supported() noexcept {
    return __cplusplus >= cpp20;
}

[[nodiscard]]
constexpr bool
is_cpp23_supported() noexcept {
    return __cplusplus >= cpp23;
}
} // namespace idk