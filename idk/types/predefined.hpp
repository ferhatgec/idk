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

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define DEFLIT(type, name) \
                    constexpr type operator""_##name(long double val) noexcept { return static_cast<type>(val); } \
                    constexpr type operator""_##name(char val) noexcept { return static_cast<type>(val); } \
                    constexpr type operator""_##name(idk::usize val) noexcept { return static_cast<type>(val); }

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

constexpr usize cpp98 { 199711 },
                cpp11 { 201103 },
                cpp14 { 201402 },
                cpp17 { 201703 },
                cpp20 { 202002 },
                cpp23 { 202302 };

constexpr auto  e          { 2.71828182845904523536 },
                log2e      { 1.44269504088896340736 },
                log10e     { 0.434294481903251827651},
                ln2        { 0.693147180559945309417},
                ln10       { 2.30258509299404568402 },
                pi         { 3.14159265358979323846 },
                pi_2       { 1.57079632679489661923 },
                pi_4       { 0.785398163397448309616},
                invpi      { 0.318309886183790671538},
                _2invpi    { 0.636619772367581343076},
                _2invsqrtpi{ 1.12837916709551257390 },
                sqrt2      { 1.41421356237309504880 },
                sqrt5      { 2.23606797749978980505 },
                phi        { 1.61803398874989490252 },
                invsqrt2   { 0.707106781186547524401};

#if defined(_WIN16) \
    || defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__)
    constexpr const char* os_platform { "windows" };
#   define               _windows
#elif defined(macintosh) \
    || defined(Macintosh) \
    || (defined(__APPLE__) && defined(__MACH__))
    constexpr const char* os_platform { "macos" };
#   define               _macos
#elif defined(__linux__) \
    || defined(linux) \
    || defined(__linux) \
    || defined(__gnu_linux__)
    constexpr const char* os_platform { "linux" };
#   define               _linux
#elif defined(__ANDROID__)
    constexpr const char* os_platform { "android" };
#   define               _android
#elif (defined(__FreeBSD_kernel__) && defined(__GLIBC__)) \
    || defined(__FreeBSD__) \
    || defined(__FreeBSD_kernel__)
    constexpr const char* os_platform { "freebsd" };
#   define               _freebsd
#elif defined(__DragonFly__)
    constexpr const char* os_platform { "dragonfly" };
#   define               _dragonfly
#elif defined(__OpenBSD__)
    constexpr const char* os_platform { "openbsd" };
#   define               _openbsd
#elif defined(__NetBSD__)
    constexpr const char* os_platform { "netbsd" };
#   define               _netbsd
#else
    constexpr const char* os_platform { "" };
#endif

#if defined(__x86_64__) \
    || defined(_M_X64)
    constexpr const char* cpu_arch { "x86_64" };
#   define               _x86_64
#elif defined(i386) \
    || defined(__i386__) \
    || defined(__i386) \
    || defined(_M_IX86)
    constexpr const char* cpu_arch { "x86_32" };
#   define               _x86_32
#elif defined(__aarch64__) \
    || defined(_M_ARM64)
    constexpr const char* cpu_arch { "arm64" };
#   define               _arm64
#elif defined(mips) \
    || defined(__mips__) \
    || defined(__mips)
    constexpr const char* cpu_arch { "mips" };
#   define               _mips
#elif defined(__sparc__) \
    || defined(__sparc)
    constexpr const char* cpu_arch { "sparc" };
#   define               _sparc
#else
    constexpr const char* cpu_arch { "" };
#endif

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