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
// contains some works from https://en.cppreference.com/w/cpp/meta reference implementations section.

#pragma once

#include "../types/predefined.hpp"
#include <cstddef>

namespace idk {
template<typename T, T val>
struct IntegralConstant {
    static constexpr T value = val;
    using value_type         = T;
    using type               = IntegralConstant;
};

template<bool B, typename T, typename F>
struct Conditional {
    using type = T;
};

template<typename T> struct RemoveReference     { 
    using type = T; 
};
template<typename T> struct RemoveReference<T&> { 
    using type = T; 
};
template<typename T> struct RemoveReference<T&&>{ 
    using type = T;
};


using true_type  = IntegralConstant<bool, true>;
using false_type = IntegralConstant<bool, false>;

template<typename> struct IsVoid             : false_type{};
template<> struct IsVoid<void>               : true_type {};
template<> struct IsVoid<const void>         : true_type {};
template<> struct IsVoid<volatile void>      : true_type {};
template<> struct IsVoid<const volatile void>: true_type {};


template<typename> struct IsNullPointer                       : false_type{};
template<> struct IsNullPointer<std::nullptr_t>               : true_type {};
template<> struct IsNullPointer<const std::nullptr_t>         : true_type {};
template<> struct IsNullPointer<volatile std::nullptr_t>      : true_type {};
template<> struct IsNullPointer<const volatile std::nullptr_t>: true_type {};

template<typename> struct IsIntegral   : false_type{};
template<> struct IsIntegral<bool>     : true_type {};
template<> struct IsIntegral<char>     : true_type {};
template<> struct IsIntegral<char16_t> : true_type {};
template<> struct IsIntegral<char32_t> : true_type {};
template<> struct IsIntegral<wchar_t>  : true_type {};
template<> struct IsIntegral<short>    : true_type {};
template<> struct IsIntegral<int>      : true_type {};
template<> struct IsIntegral<long>     : true_type {};
template<> struct IsIntegral<long long>: true_type {};

template<typename> struct IsFloatingPoint     : false_type{};
template<> struct IsFloatingPoint<float>      : true_type {};
template<> struct IsFloatingPoint<double>     : true_type {};
template<> struct IsFloatingPoint<long double>: true_type {};

template<typename> struct IsArray                 : false_type{};
template<typename T> struct IsArray<T[]>          : true_type {};
template<typename T, usize N> struct IsArray<T[N]>: true_type {};

template<typename> struct IsPointer                     : false_type{};
template<typename T> struct IsPointer<T*>               : true_type {};
template<typename T> struct IsPointer<T* const>         : true_type {};
template<typename T> struct IsPointer<T* volatile>      : true_type {};
template<typename T> struct IsPointer<T* const volatile>: true_type {};

template<typename> struct IsLvalueReference      : false_type{};
template<typename T> struct IsLvalueReference<T&>: true_type {};

template<typename> struct IsRvalueReference       : false_type{};
template<typename T> struct IsRvalueReference<T&&>: true_type {};

template<typename> struct IsConst           : false_type{};
template<typename T> struct IsConst<const T>: true_type {};

template<typename> struct IsVolatile              : false_type{};
template<typename T> struct IsVolatile<volatile T>: true_type {};

template<typename> struct IsBoundedArray                 : false_type{};
template<typename T, usize N> struct IsBoundedArray<T[N]>: true_type {};

template<typename, typename> struct IsSame : false_type{};
template<typename T> struct IsSame<T, T>   : true_type {};

template<typename...> struct Conjunction                           : true_type {};
template<typename B1> struct Conjunction<B1>                       : B1 {};
template<typename B1, typename... Bn> struct Conjunction<B1, Bn...>: Conditional<bool(B1::value), Conjunction<Bn...>, B1>::type {};

template<typename...> struct Disjunction                           : false_type {};
template<typename B1> struct Disjunction<B1>                       : B1 {};
template<typename B1, typename... Bn> struct Disjunction<B1, Bn...>: Conditional<bool(B1::value), B1, Disjunction<Bn...>>::type {};

template<bool, typename T = void> struct EnableIf {}; 
template<typename T> struct EnableIf<true, T> { 
    using type = T; 
};

template<typename T> inline constexpr bool IsVoidVal            = IsVoid<T>::value           ;
template<typename T> inline constexpr bool IsNullPointerVal     = IsNullPointer<T>::value    ;
template<typename T> inline constexpr bool IsIntegralVal        = IsIntegral<T>::value       ;
template<typename T> inline constexpr bool IsFloatingPointVal   = IsFloatingPoint<T>::value  ;
template<typename T> inline constexpr bool IsArrayVal           = IsArray<T>::value          ;
template<typename T> inline constexpr bool IsPointerVal         = IsPointer<T>::value        ;
template<typename T> inline constexpr bool IsLvalueReferenceVal = IsLvalueReference<T>::value;
template<typename T> inline constexpr bool IsRvalueReferenceVal = IsRvalueReference<T>::value;
template<typename T> inline constexpr bool IsConstVal           = IsConst<T>::value          ;
template<typename T> inline constexpr bool IsVolatileVal        = IsVolatile<T>::value       ;
template<typename T> inline constexpr bool IsBoundedArrayVal    = IsBoundedArray<T>::value   ;
template<typename T, typename U> inline constexpr bool IsSameVal= IsSame<T, U>::value        ;

template<typename T> inline constexpr bool ConjunctionType      = Conjunction<T>::type;
template<typename T> inline constexpr bool DisjunctionType      = Disjunction<T>::type;

template<typename T>                using RemoveReferenceType   = typename RemoveReference<T>::type;
template<bool T, typename U = void> using EnableIfType          = typename EnableIf<T, U>::type    ;

} // namespace idk