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
#include "../utilities/loop.hpp"

namespace idk {
template<usize N>
class __idk_nodiscard FibonacciGenerator {
public:
    __idk_nodiscard
    static __idk_constexpr usize 
    generate() noexcept {
        if __idk_constexpr(N < 2)
            return N;
        
        f80 val = 1;

        Loop<N>([&](auto) mutable {
            val *= phi;
        });

        val /= sqrt5;

        return static_cast<usize>(val + 0.5); // outside of usize range will produce ub, so using 
                                              // c++23 __idk_constexpr ::round probably better idea.
                                              // it's newer standard, so major stl implementations probably have
                                              // not implemented it yet(?).
    }
};

__idk_nodiscard
__idk_constexpr usize
generate_fibonacci(const usize& nth) noexcept {
    if(nth == 0 || nth == 1)
        return nth;
 
    return generate_fibonacci(nth - 2) + generate_fibonacci(nth - 1);
}

__idk_nodiscard
__idk_constexpr usize
generate_fibonacci(usize&& nth) noexcept {
    return generate_fibonacci(nth);
}
} // namespace idk