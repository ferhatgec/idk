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

namespace idk {
template<usize N>
class __idk_nodiscard FactorialGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        return N * FactorialGenerator<N - 1>::generate();
    }
};

#define DEF_FACTORIAL_GEN(num, val) template<> \
                                    class __idk_nodiscard FactorialGenerator<num> { \
                                    public: \
                                        __idk_nodiscard \
                                        static __idk_constexpr usize \
                                        generate() noexcept { \
                                            return val; \
                                        } \
                                    }; \

#define CASE_FACTORIAL_GEN(nth) case nth: { \
                                    return FactorialGenerator<nth>::generate(); \
                                } \

DEF_FACTORIAL_GEN(0, 1)
DEF_FACTORIAL_GEN(1, 1)
DEF_FACTORIAL_GEN(2, 2)
DEF_FACTORIAL_GEN(3, 6)
DEF_FACTORIAL_GEN(4, 24)
DEF_FACTORIAL_GEN(5, 120)
DEF_FACTORIAL_GEN(6, 720)
DEF_FACTORIAL_GEN(7, 5040)
DEF_FACTORIAL_GEN(8, 40320)
DEF_FACTORIAL_GEN(9, 362880)
DEF_FACTORIAL_GEN(10, 3628800)
DEF_FACTORIAL_GEN(11, 39916800)
DEF_FACTORIAL_GEN(12, 479001600)
DEF_FACTORIAL_GEN(13, 6227020800)
DEF_FACTORIAL_GEN(14, 87178291200)
DEF_FACTORIAL_GEN(15, 1307674368000)
DEF_FACTORIAL_GEN(16, 20922789888000)
DEF_FACTORIAL_GEN(17, 355687428096000)
DEF_FACTORIAL_GEN(18, 6402373705728000)
DEF_FACTORIAL_GEN(19, 121645100408832000)
DEF_FACTORIAL_GEN(20, 2432902008176640000) // maximum possible nth factorial for 64 bit systems, where n is integer 

__idk_nodiscard
__idk_constexpr usize
generate_factorial(const usize& nth) noexcept {
    switch(nth) {
        CASE_FACTORIAL_GEN(0)
        CASE_FACTORIAL_GEN(1)
        CASE_FACTORIAL_GEN(2)
        CASE_FACTORIAL_GEN(3)
        CASE_FACTORIAL_GEN(4)
        CASE_FACTORIAL_GEN(5)
        CASE_FACTORIAL_GEN(6)
        CASE_FACTORIAL_GEN(7)
        CASE_FACTORIAL_GEN(8)
        CASE_FACTORIAL_GEN(9)
        CASE_FACTORIAL_GEN(10)
        CASE_FACTORIAL_GEN(11)
        CASE_FACTORIAL_GEN(12)
        CASE_FACTORIAL_GEN(13)
        CASE_FACTORIAL_GEN(14)
        CASE_FACTORIAL_GEN(15)
        CASE_FACTORIAL_GEN(16)
        CASE_FACTORIAL_GEN(17)
        CASE_FACTORIAL_GEN(18)
        CASE_FACTORIAL_GEN(19)
        CASE_FACTORIAL_GEN(20)

        default: {
           break;
        }
    }
    
    return nth * generate_factorial(nth - 1); // that crap thing just here for nothing
}

__idk_nodiscard
__idk_constexpr usize
generate_factorial(usize&& nth) noexcept {
    return generate_factorial(nth);
}
} // namespace idk

#undef DEF_FACTORIAL_GEN
#undef CASE_FACTORIAL_GEN