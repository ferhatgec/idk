// idk libraries
// -------------
// disclaimer: don't forget that, idk libraries are not focused on replacing
// standard library. (for some standard classes are directly being replaced by
// compiler, like initializer_list will need compiler dependent codes)
// so, this is not *directly* an alternative to stl, some class- and functions
// may have different naming different outputs or attributes etc.
//
// MIT License
//
// Copyright (c) 2023-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "../utilities/limits.hpp"
#include "../utilities/type_traits.hpp"
#include "catalan.hpp"
#include "combination.hpp"
#include "derangement.hpp"
#include "factorial.hpp"
#include "fibonacci.hpp"
#include "gcd.hpp"
#include "lcm.hpp"
#include "mean.hpp"
#include "mersenne.hpp"
#include "permutation.hpp"
#include "prime.hpp"

namespace idk {
template <idk::FloatingPoint Float>
[[nodiscard]]
static constexpr bool nearly_equals(
    const Float &a, const Float &b,
    const Float &epsilon = idk::NumericLimits<Float>::epsilon()) noexcept {
  return a + epsilon >= b && a - epsilon <= b;
}
} // namespace idk