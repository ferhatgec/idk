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
#include "../containers/vector.hpp"

namespace idk {
class __idk_nodiscard MeanAbsoluteError {
public:
    __idk_nodiscard
    static const f80
    generate(idk::Vec<f80>& x, idk::Vec<f80>& y) noexcept {
        if(x.size() != y.size())
            return 0;

        f80 sum { 0_f80 };

        for(isize i = 0; i < x.size(); ++i) {
            sum += fabsl(y.at_without_check_reference(i) - x.at_without_check_reference(i));
        }

        return (sum / static_cast<f80>(x.size()));
    }

    __idk_nodiscard
    static const f80
    generate(idk::Vec<f80>&& x, idk::Vec<f80>&& y) noexcept {
        return MeanAbsoluteError::generate(x, y);
    }
};

__idk_nodiscard
const f80 mean_absolute_error(idk::Vec<f80>& x, idk::Vec<f80>& y) noexcept {
    return MeanAbsoluteError::generate(x, y);
}

__idk_nodiscard
const f80 mean_absolute_error(idk::Vec<f80>&& x, idk::Vec<f80>&& y) noexcept {
    return MeanAbsoluteError::generate(idk::move(x), idk::move(y));
}
} // namespace idk