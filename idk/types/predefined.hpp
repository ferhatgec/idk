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
// Copyright (c) 2023-2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#if defined(__GNUC__) || defined(__GNUG__)
#   pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

#define DEFLIT(type, name) \
                    __idk_constexpr inline type operator""_##name(long double val) noexcept { return static_cast<type>(val); } \
                    __idk_constexpr inline type operator""_##name(char val) noexcept { return static_cast<type>(val); } \
                    __idk_constexpr inline type operator""_##name(idk::usize val) noexcept { return static_cast<type>(val); }

#define __idk_cpp98 199711
#define __idk_cpp11 201103
#define __idk_cpp14 201402
#define __idk_cpp17 201703
#define __idk_cpp20 202002
#define __idk_cpp23 202302

#define __idk_e 2.71828182845904523536
#define __idk_log2e 1.44269504088896340736
#define __idk_log10e 0.434294481903251827651
#define __idk_ln2 0.693147180559945309417
#define __idk_ln10 2.30258509299404568402
#define __idk_pi 3.14159265358979323846
#define __idk_pi_2 1.57079632679489661923
#define __idk_pi_4 0.785398163397448309616
#define __idk_invpi 0.318309886183790671538
#define __idk_2invpi 0.636619772367581343076
#define __idk_2invsqrtpi 1.12837916709551257390
#define __idk_sqrt2 1.41421356237309504880
#define __idk_sqrt5 2.23606797749978980505
#define __idk_phi 1.61803398874989490252
#define __idk_invsqrt2 0.707106781186547524401
#define __idk_tau 6.283185307179586476925

#define __idk_is_cpp98_supported (__cplusplus >= __idk_cpp98)
#define __idk_is_cpp11_supported (__cplusplus >= __idk_cpp11)
#define __idk_is_cpp14_supported (__cplusplus >= __idk_cpp14)
#define __idk_is_cpp17_supported (__cplusplus >= __idk_cpp17)
#define __idk_is_cpp20_supported (__cplusplus >= __idk_cpp20)
#define __idk_is_cpp23_supported (__cplusplus >= __idk_cpp23)

// currently, idk has support from c++17 to latest standard.
// supporting from c++11 to latest standard is our goal. (some features won't be in c++11, 
// some definitions may change, especially some definitions based on c++ feature extensions.)

#if __idk_is_cpp17_supported
#   define __idk_nodiscard [[nodiscard]]
#   define __idk_constexpr constexpr
#   define __idk_noexcept noexcept
#else
#   define __idk_nodiscard
#   define __idk_constexpr
#   define __idk_noexcept
#endif

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
using isize = long long         ;

using f80   = long double       ;
using f64   = double            ;
using f32   = float             ;

__idk_constexpr inline usize cpp98 { __idk_cpp98 },
                cpp11 { __idk_cpp11 },
                cpp14 { __idk_cpp14 },
                cpp17 { __idk_cpp17 },
                cpp20 { __idk_cpp20 },
                cpp23 { __idk_cpp23 };

__idk_constexpr inline auto  e          { __idk_e },
                log2e      { __idk_log2e },
                log10e     { __idk_log10e},
                ln2        { __idk_ln2},
                ln10       { __idk_ln10 },
                pi         { __idk_pi },
                pi_2       { __idk_pi_2 },
                pi_4       { __idk_pi_4 },
                invpi      { __idk_invpi },
                _2invpi    { __idk_2invpi },
                _2invsqrtpi{ __idk_2invsqrtpi },
                sqrt2      { __idk_sqrt2 },
                sqrt5      { __idk_sqrt5 },
                phi        { __idk_phi },
                invsqrt2   { __idk_invsqrt2},
                tau        { __idk_tau };

#if defined(_WIN16) \
    || defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__)
    __idk_constexpr inline const char* os_platform { "windows" };
#   define               _windows
#elif defined(macintosh) \
    || defined(Macintosh) \
    || (defined(__APPLE__) && defined(__MACH__))
    __idk_constexpr inline const char* os_platform { "macos" };
#   define               _macos
#elif defined(__linux__) \
    || defined(linux) \
    || defined(__linux) \
    || defined(__gnu_linux__)
    __idk_constexpr inline const char* os_platform { "linux" };
#   define               _linux
#elif defined(__ANDROID__)
    __idk_constexpr inline const char* os_platform { "android" };
#   define               _android
#elif (defined(__FreeBSD_kernel__) && defined(__GLIBC__)) \
    || defined(__FreeBSD__) \
    || defined(__FreeBSD_kernel__)
    __idk_constexpr inline const char* os_platform { "freebsd" };
#   define               _freebsd
#elif defined(__DragonFly__)
    __idk_constexpr inline const char* os_platform { "dragonfly" };
#   define               _dragonfly
#elif defined(__OpenBSD__)
    __idk_constexpr inline const char* os_platform { "openbsd" };
#   define               _openbsd
#elif defined(__NetBSD__)
    __idk_constexpr inline const char* os_platform { "netbsd" };
#   define               _netbsd
#else
    __idk_constexpr inline const char* os_platform { "" };
#endif

#if defined(__x86_64__) \
    || defined(_M_X64)
    __idk_constexpr inline const char* cpu_arch { "x86_64" };
#   define               _x86_64
#elif defined(i386) \
    || defined(__i386__) \
    || defined(__i386) \
    || defined(_M_IX86)
    __idk_constexpr inline const char* cpu_arch { "x86_32" };
#   define               _x86_32
#elif defined(__aarch64__) \
    || defined(_M_ARM64)
    __idk_constexpr inline const char* cpu_arch { "arm64" };
#   define               _arm64
#elif defined(mips) \
    || defined(__mips__) \
    || defined(__mips)
    __idk_constexpr inline const char* cpu_arch { "mips" };
#   define               _mips
#elif defined(__sparc__) \
    || defined(__sparc)
    __idk_constexpr inline const char* cpu_arch { "sparc" };
#   define               _sparc
#else
    __idk_constexpr inline const char* cpu_arch { "" };
#endif

__idk_nodiscard
inline __idk_constexpr bool
is_cpp98_supported() noexcept {
    return __idk_is_cpp98_supported;
}

__idk_nodiscard
inline __idk_constexpr bool
is_cpp11_supported() noexcept {
    return __idk_is_cpp11_supported;
}

__idk_nodiscard
inline __idk_constexpr bool
is_cpp14_supported() noexcept {
    return __idk_is_cpp14_supported;
}

__idk_nodiscard
inline __idk_constexpr bool
is_cpp17_supported() noexcept {
    return __idk_is_cpp17_supported;
}

__idk_nodiscard
inline __idk_constexpr bool
is_cpp20_supported() noexcept {
    return __idk_is_cpp20_supported;
}

__idk_nodiscard
inline __idk_constexpr bool
is_cpp23_supported() noexcept {
    return __idk_is_cpp23_supported;
}
} // namespace idk

DEFLIT(idk::i8, i8)
DEFLIT(idk::i16, i16)
DEFLIT(idk::i32, i32)
DEFLIT(idk::i64, i64)

DEFLIT(idk::u8, u8)
DEFLIT(idk::u16, u16)
DEFLIT(idk::u32, u32)
DEFLIT(idk::u64, u64)

DEFLIT(idk::f80, f80)
DEFLIT(idk::f64, f64)
DEFLIT(idk::f32, f32)

DEFLIT(idk::usize, usize)
DEFLIT(idk::isize, isize)
DEFLIT(idk::size, size)

#undef DEFLIT