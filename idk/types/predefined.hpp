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

#if defined(_WIN16) \
    || defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__)
    constexpr const char* os_platform { "windows" };
#elif defined(macintosh) \
    || defined(Macintosh) \
    || (defined(__APPLE__) && defined(__MACH__))
    constexpr const char* os_platform { "macos" };
#elif defined(__linux__) \
    || defined(linux) \
    || defined(__linux) \
    || defined(__gnu_linux__)
    constexpr const char* os_platform { "linux" };
#elif defined(__ANDROID__)
    constexpr const char* os_platform { "android" };
#elif (defined(__FreeBSD_kernel__) && defined(__GLIBC__)) \
    || defined(__FreeBSD__) \
    || defined(__FreeBSD_kernel__)
    constexpr const char* os_platform { "freebsd" };
#elif defined(__DragonFly__)
    constexpr const char* os_platform { "dragonfly" };
#elif defined(__OpenBSD__)
    constexpr const char* os_platform { "openbsd" };
#elif defined(__NetBSD__)
    constexpr const char* os_platform { "netbsd" };
#else
    constexpr const char* os_platform { "" };
#endif

#if defined(__x86_64__) \
    || defined(_M_X64)
    constexpr const char* cpu_arch { "x86_64" };
#elif defined(i386) \
    || defined(__i386__) \
    || defined(__i386) \
    || defined(_M_IX86)
    constexpr const char* cpu_arch { "x86_32" };
#elif defined(__aarch64__) \
    || defined(_M_ARM64)
    constexpr const char* cpu_arch { "arm64" };
#elif defined(mips) \
    || defined(__mips__) \
    || defined(__mips)
    constexpr const char* cpu_arch { "mips" };
#elif defined(__sparc__) \
    || defined(__sparc)
    constexpr const char* cpu_arch { "sparc" };
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