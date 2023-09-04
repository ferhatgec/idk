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
#include <float.h>
#include <type_traits>
#include <climits>
#include <cmath>

#define IS_SAME_WITH(_Type, _NL_Type) if constexpr(std::is_same_v<_Type, _NL_Type>) 

namespace idk {
enum FloatRoundStyle : const i8 {
    RoundIndeterminate = -1,
    RoundTowardZero,
    RoundToNearest,
    RoundTowardInfinity,
    RoundTowardNegInfinity
};

enum FloatDenormStyle : const i8 { // deprecated in c++23
    DenormIndeterminate = -1,
    DenormAbsent,
    DenormPresent
};

template<typename Type>
class NumericLimits {
public:

    [[nodiscard]]
    static constexpr Type 
    min_val() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(char, Type)
            return CHAR_MIN;
        else IS_SAME_WITH(signed char, Type)
            return SCHAR_MIN;
        else IS_SAME_WITH(unsigned char, Type)
            return 0;
        // char8_t
        else IS_SAME_WITH(char16_t, Type)
            return 0;
        else IS_SAME_WITH(char32_t, Type)
            return 0;
        else IS_SAME_WITH(short, Type)
            return SHRT_MIN;
        else IS_SAME_WITH(unsigned short, Type)
            return 0;
        else IS_SAME_WITH(int, Type)
            return INT_MIN;
        else IS_SAME_WITH(unsigned int, Type)
            return 0;
        else IS_SAME_WITH(long, Type)
            return LONG_MIN;
        else IS_SAME_WITH(unsigned long, Type)
            return 0;
        else IS_SAME_WITH(long long, Type)
            return LLONG_MIN;
        else IS_SAME_WITH(unsigned long long, Type)
            return 0;
        else IS_SAME_WITH(float, Type)
            return FLT_MIN;
        else IS_SAME_WITH(double, Type)
            return DBL_MIN;
        
        return LDBL_MIN;
    }

    [[nodiscard]]
    static constexpr Type 
    max_val() noexcept {
        IS_SAME_WITH(bool, Type)
            return true;
        else IS_SAME_WITH(char, Type)
            return CHAR_MAX;
        else IS_SAME_WITH(signed char, Type)
            return SCHAR_MAX;
        else IS_SAME_WITH(unsigned char, Type)
            return UCHAR_MAX;
        // char8_t
        else IS_SAME_WITH(char16_t, Type)
            return UINT_LEAST16_MAX;
        else IS_SAME_WITH(char32_t, Type)
            return UINT_LEAST32_MAX;
        else IS_SAME_WITH(short, Type)
            return SHRT_MAX;
        else IS_SAME_WITH(unsigned short, Type)
            return USHRT_MAX;
        else IS_SAME_WITH(int, Type)
            return INT_MAX;
        else IS_SAME_WITH(unsigned int, Type)
            return UINT_MAX;
        else IS_SAME_WITH(long, Type)
            return LONG_MAX;
        else IS_SAME_WITH(unsigned long, Type)
            return ULONG_MAX;
        else IS_SAME_WITH(long long, Type)
            return LLONG_MAX;
        else IS_SAME_WITH(unsigned long long, Type)
            return ULLONG_MAX;
        else IS_SAME_WITH(float, Type)
            return FLT_MAX;
        else IS_SAME_WITH(double, Type)
            return DBL_MAX;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MAX;

        return Type();
    }

    [[nodiscard]]
    static constexpr Type
    lowest_val() noexcept {
        IS_SAME_WITH(float, Type)
            return -FLT_MAX;
        else IS_SAME_WITH(double, Type) 
            return -DBL_MAX;
        else IS_SAME_WITH(long double, Type)
            return -LDBL_MAX;

        return min_val();
    }

    [[nodiscard]]
    static constexpr Type
    min() noexcept {
        return min_val();
    }

    [[nodiscard]]
    static constexpr Type
    max() noexcept {
        return max_val();
    }

    [[nodiscard]]
    static constexpr Type
    lowest() noexcept {
        return lowest_val();
    }

    [[nodiscard]]
    static constexpr Type
    epsilon() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return FLT_EPSILON;
        else IS_SAME_WITH(double, Type)
            return DBL_EPSILON;
        else IS_SAME_WITH(long double, Type)
            return LDBL_EPSILON;
        
        return 0; // Type() maybe for non specialized ones
    }

    [[nodiscard]]
    static constexpr Type
    round_error() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return 0.5f;
        else IS_SAME_WITH(double, Type)
            return 0.5;
        else IS_SAME_WITH(long double, Type)
            return 0.5L;
        
        return 0;
    }

    [[nodiscard]]
    static constexpr Type
    denorm_min_val() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type) {
            if(idk::NumericLimits<Type>::is_iec559)
                return FLT_TRUE_MIN;
            return static_cast<float>(0);
        } else IS_SAME_WITH(double, Type) {
            if(idk::NumericLimits<Type>::is_iec559)
                return DBL_TRUE_MIN;

            return 0;
        } else IS_SAME_WITH(long double, Type) {
            if(idk::NumericLimits<Type>::is_iec559)
                return LDBL_TRUE_MIN;

            return 0L;
        }
        
        return 0;
    }

    [[nodiscard]]
    static constexpr Type
    infinity() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return HUGE_VALF;
        else IS_SAME_WITH(double, Type)
            return HUGE_VAL;
        else IS_SAME_WITH(long double, Type)
            return HUGE_VALL;
        
        return 0;
    }

    [[nodiscard]]
    static constexpr Type
    quiet_NaN() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return static_cast<float>(0);
        else IS_SAME_WITH(double, Type)
            return 0;
        else IS_SAME_WITH(long double, Type)
            return 0L;

        return 0;
    }

    [[nodiscard]]
    static constexpr Type
    signaling_NaN() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return static_cast<float>(0);
        else IS_SAME_WITH(double, Type)
            return 0;
        else IS_SAME_WITH(long double, Type)
            return 0L;

        return 0;
    }

    [[nodiscard]]
    static constexpr bool
    _is_signed() noexcept {
        IS_SAME_WITH(bool, Type)
            return false;
        else IS_SAME_WITH(char, Type)
            return true;
        else IS_SAME_WITH(signed char, Type)
            return true;
        else IS_SAME_WITH(unsigned char, Type)
            return false;
        else IS_SAME_WITH(wchar_t, Type)
            return false;
        // char8_t
        else IS_SAME_WITH(char16_t, Type)
            return false;
        else IS_SAME_WITH(char32_t, Type)
            return false;
        else IS_SAME_WITH(short, Type)
            return true;
        else IS_SAME_WITH(unsigned short, Type)
            return false;
        else IS_SAME_WITH(int, Type)
            return true;
        else IS_SAME_WITH(unsigned int, Type)
            return false;
        else IS_SAME_WITH(long, Type)
            return true;
        else IS_SAME_WITH(unsigned long, Type)
            return false;
        else IS_SAME_WITH(long long, Type)
            return true;
        else IS_SAME_WITH(unsigned long long, Type)
            return false;
        else IS_SAME_WITH(float, Type)
            return true;
        else IS_SAME_WITH(double, Type)
            return true;
        
        return true;
    }

    [[nodiscard]]
    static constexpr bool
    _is_modulo() noexcept {
        IS_SAME_WITH(char, Type)
            return CHAR_MIN == 0;
        else IS_SAME_WITH(signed char, Type) // ?
            return false;
        else IS_SAME_WITH(unsigned char, Type)
            return true;
        // char8_t
        else IS_SAME_WITH(char16_t, Type)
            return true;
        else IS_SAME_WITH(char32_t, Type)
            return true;
        else IS_SAME_WITH(wchar_t, Type)
            return true;
        else IS_SAME_WITH(short, Type)
            return true;
    }

    [[nodiscard]]
    static constexpr i32
    _digits() noexcept {
        IS_SAME_WITH(bool, Type)
            return 1;
        else IS_SAME_WITH(char, Type)
            return CHAR_BIT - idk::NumericLimits<char>::is_signed;
        else IS_SAME_WITH(signed char, Type)
            return CHAR_BIT - 1;
        else IS_SAME_WITH(unsigned char, Type)
            return CHAR_BIT;
        else IS_SAME_WITH(wchar_t, Type)
            return CHAR_BIT * sizeof(wchar_t) - idk::NumericLimits<wchar_t>::is_signed;
        // char8_t
        else IS_SAME_WITH(char16_t, Type)
            return CHAR_BIT * sizeof(char16_t);
        else IS_SAME_WITH(char32_t, Type)
            return CHAR_BIT * sizeof(char32_t);
        else IS_SAME_WITH(unsigned short, Type)
            return CHAR_BIT * sizeof(short);
        else IS_SAME_WITH(unsigned int, Type)
            return CHAR_BIT * sizeof(int);
        else IS_SAME_WITH(unsigned long, Type)
            return CHAR_BIT * sizeof(long);
        else IS_SAME_WITH(unsigned long long, Type)
            return CHAR_BIT * sizeof(long long);
        else IS_SAME_WITH(float, Type)
            return FLT_MANT_DIG;
        else IS_SAME_WITH(double, Type)
            return DBL_MANT_DIG;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MANT_DIG;
        
        return CHAR_BIT * sizeof(Type) - 1;
    }

    [[nodiscard]]
    static constexpr i32
    _digits10() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_DIG;
        else IS_SAME_WITH(double, Type)
            return DBL_DIG;
        else IS_SAME_WITH(long double, Type)
            return LDBL_DIG;

        return idk::NumericLimits<Type>::digits * std::log10(2);
    }

    [[nodiscard]]
    static constexpr i32
    _max_digits10() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_DECIMAL_DIG;
        else IS_SAME_WITH(double, Type)
            return DBL_DECIMAL_DIG;
        else IS_SAME_WITH(long double, Type)
            return LDBL_DECIMAL_DIG;

        return 0;
    }

    [[nodiscard]]
    static constexpr i32
    _radix() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_RADIX;
        else IS_SAME_WITH(double, Type)
            return FLT_RADIX;
        else IS_SAME_WITH(long double, Type)
            return FLT_RADIX;

        return 2;
    }

    [[nodiscard]]
    static constexpr i32
    _min_exponent() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_MIN_EXP;
        else IS_SAME_WITH(double, Type)
            return DBL_MIN_EXP;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MIN_EXP;

        return 0;
    }

    [[nodiscard]]
    static constexpr i32
    _min_exponent10() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_MIN_10_EXP;
        else IS_SAME_WITH(double, Type)
            return DBL_MIN_10_EXP;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MIN_10_EXP;

        return 0;
    }

    [[nodiscard]]
    static constexpr i32
    _max_exponent() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_MAX_EXP;
        else IS_SAME_WITH(double, Type)
            return DBL_MAX_EXP;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MAX_EXP;

        return 0;
    }

    [[nodiscard]]
    static constexpr i32
    _max_exponent10() noexcept {
        IS_SAME_WITH(float, Type)
            return FLT_MAX_10_EXP;
        else IS_SAME_WITH(double, Type)
            return DBL_MAX_10_EXP;
        else IS_SAME_WITH(long double, Type)
            return LDBL_MAX_10_EXP;

        return 0;
    }

    [[nodiscard]]
    static constexpr bool
    _traps() noexcept {
        IS_SAME_WITH(float, Type)
            return false;
        else IS_SAME_WITH(double, Type)
            return false;
        else IS_SAME_WITH(long double, Type)
            return false;
        else IS_SAME_WITH(bool, Type)
            return false;

        return true;
    }

    [[nodiscard]]
    static constexpr bool
    _tinyness_before() noexcept {
        return false;
    }

    [[nodiscard]]
    static constexpr i32
    _is_bounded() noexcept {
        return true;
    }

    [[nodiscard]]
    static constexpr i32
    _is_iec559() noexcept {
        IS_SAME_WITH(float, Type)
            return true;
        else IS_SAME_WITH(double, Type)
            return true;
        else IS_SAME_WITH(long double, Type)
            return true;

        return false;
    }

    [[nodiscard]]
    static constexpr idk::FloatRoundStyle
    _round_style() noexcept {
        IS_SAME_WITH(float, Type)
            return idk::FloatRoundStyle::RoundToNearest;
        else IS_SAME_WITH(double, Type)
            return idk::FloatRoundStyle::RoundToNearest;
        else IS_SAME_WITH(long double, Type)
            return idk::FloatRoundStyle::RoundToNearest;

        return idk::FloatRoundStyle::RoundTowardZero;
    }

    [[nodiscard]]
    static constexpr bool
    _has_denorm_loss() noexcept {
        return false;
    }

    [[nodiscard]]
    static constexpr idk::FloatDenormStyle
    _has_denorm() noexcept {
        IS_SAME_WITH(float, Type)
            return idk::FloatDenormStyle::DenormPresent;
        else IS_SAME_WITH(double, Type)
            return idk::FloatDenormStyle::DenormPresent;
        else IS_SAME_WITH(long double, Type)
            return idk::FloatDenormStyle::DenormPresent;

        return idk::FloatDenormStyle::DenormAbsent;
    }

    [[nodiscard]]
    static constexpr bool
    _has_signaling_NaN() noexcept {
        IS_SAME_WITH(float, Type)
            return true;
        else IS_SAME_WITH(double, Type)
            return true;
        else IS_SAME_WITH(long double, Type)
            return true;

        return false;
    }

    [[nodiscard]]
    static constexpr bool
    _has_quiet_NaN() noexcept {
        IS_SAME_WITH(float, Type)
            return true;
        else IS_SAME_WITH(double, Type)
            return true;
        else IS_SAME_WITH(long double, Type)
            return true;

        return false;
    }

    [[nodiscard]]
    static constexpr bool
    _has_infinity() noexcept {
        IS_SAME_WITH(float, Type)
            return true;
        else IS_SAME_WITH(double, Type)
            return true;
        else IS_SAME_WITH(long double, Type)
            return true;

        return false;
    }

    [[nodiscard]]
    static constexpr bool
    _is_exact() noexcept {
        IS_SAME_WITH(float, Type)
            return false;
        else IS_SAME_WITH(double, Type)
            return false;
        else IS_SAME_WITH(long double, Type)
            return false;

        return true;
    }

    [[nodiscard]]
    static constexpr bool
    _is_integer() noexcept {
        IS_SAME_WITH(float, Type)
            return false;
        else IS_SAME_WITH(double, Type)
            return false;
        else IS_SAME_WITH(long double, Type)
            return false;

        return true;
    }

    [[nodiscard]]
    static constexpr bool
    _is_specialized() noexcept {
        return true;
    }

    static constexpr Type is_specialized = idk::NumericLimits<Type>::_is_specialized();
    static constexpr Type is_signed      = idk::NumericLimits<Type>::_is_signed();
    static constexpr Type is_integer     = idk::NumericLimits<Type>::_is_integer();
    static constexpr Type is_exact       = idk::NumericLimits<Type>::_is_exact();
    static constexpr Type has_infinity   = idk::NumericLimits<Type>::_has_infinity();
    static constexpr Type has_quiet_NaN  = idk::NumericLimits<Type>::_has_quiet_NaN();
    static constexpr Type 
                       has_signaling_NaN = idk::NumericLimits<Type>::_has_signaling_NaN();
    static constexpr Type has_denorm     = idk::NumericLimits<Type>::_has_denorm();
    static constexpr Type has_denorm_loss= idk::NumericLimits<Type>::_has_denorm_loss();
    static constexpr idk::FloatRoundStyle
                          round_style    = idk::NumericLimits<Type>::_round_style();
    static constexpr Type is_iec559      = idk::NumericLimits<Type>::_is_iec559();
    static constexpr Type is_bounded     = idk::NumericLimits<Type>::_is_bounded();
    static constexpr Type is_modulo      = idk::NumericLimits<Type>::_is_modulo();
    static constexpr Type digits         = idk::NumericLimits<Type>::_digits();
    static constexpr Type digits10       = idk::NumericLimits<Type>::_digits10();
    static constexpr Type radix          = idk::NumericLimits<Type>::_radix();
    static constexpr Type min_exponent   = idk::NumericLimits<Type>::_min_exponent();
    static constexpr Type min_exponent10 = idk::NumericLimits<Type>::_min_exponent10();
    static constexpr Type max_exponent   = idk::NumericLimits<Type>::_max_exponent();
    static constexpr Type max_exponent10 = idk::NumericLimits<Type>::_max_exponent10();
    static constexpr bool traps          = idk::NumericLimits<Type>::_traps();
    static constexpr Type tinyness_before= idk::NumericLimits<Type>::_tinyness_before();
};
} // namespace idk

#undef IS_SAME_WITH
