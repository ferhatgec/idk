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
#include "mean.hpp"
#include <cmath>

#define __idk_is_arithmetic template<typename Type, idk::EnableIfType<idk::IntegralConstant<bool, \
                                                                        (idk::IsFloatingPointVal<Type> || idk::IsIntegralVal<Type>)>::value, bool> = true>

namespace idk {
__idk_is_arithmetic
__idk_nodiscard
f80
generate_population_variance(const Vec<Type>& vec) noexcept {
    if(vec.is_empty())
        return 0;

    f80 sum { 0 }, mean { idk::ArithmeticMeanGenerator::generate(vec) };

    for(auto& val: const_cast<Vec<Type>&>(vec))
        sum += (val - mean) * (val - mean);

    return (sum / static_cast<f80>(vec.size()));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_sample_variance(const Vec<Type>& vec) noexcept {
    if(vec.is_empty())
        return 0;

    f80 sum { 0 }, mean { idk::ArithmeticMeanGenerator::generate(vec) };

    for(auto& val: const_cast<Vec<Type>&>(vec))
        sum += (val - mean) * (val - mean);

    return (sum / (static_cast<f80>(vec.size() - 1_f80)));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_population_standard_deviation(const Vec<Type>& vec) noexcept {
    return std::sqrtl(generate_population_variance(vec));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_sample_standard_deviation(const Vec<Type>& vec) noexcept {
    return std::sqrtl(generate_sample_variance(vec));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_population_standard_deviation(Vec<Type>&& vec) noexcept {
    return std::sqrtl(generate_population_variance(idk::move(vec)));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_sample_standard_deviation(Vec<Type>&& vec) noexcept {
    return std::sqrtl(generate_sample_variance(idk::move(vec)));
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_population_variance(Vec<Type>&& vec) noexcept {
    return generate_population_variance(vec);
}

__idk_is_arithmetic
__idk_nodiscard
f80
generate_sample_variance(Vec<Type>&& vec) noexcept {
    return generate_sample_variance(vec);
}

class __idk_nodiscard PopulationVarianceGenerator {
public:
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(const Vec<Type>& vec) noexcept {
        return generate_population_variance(vec);
    }
    
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(Vec<Type>&& vec) noexcept {
        return generate_population_variance(idk::move(vec));
    }
};

class __idk_nodiscard SampleVarianceGenerator {
public:
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(const Vec<Type>& vec) noexcept {
        return generate_sample_variance(vec);
    }
    
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(Vec<Type>&& vec) noexcept {
        return generate_sample_variance(idk::move(vec));
    }
};

class __idk_nodiscard PopulationStandardDeviationGenerator {
public:
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(const Vec<Type>& vec) noexcept {
        return generate_population_standard_deviation(vec);
    }
    
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(Vec<Type>&& vec) noexcept {
        return generate_population_standard_deviation(idk::move(vec));
    }
};

class __idk_nodiscard SampleStandardDeviationGenerator {
public:
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(const Vec<Type>& vec) noexcept {
        return generate_sample_standard_deviation(vec);
    }
    
    __idk_is_arithmetic
    __idk_nodiscard
    static f80 
    generate(Vec<Type>&& vec) noexcept {
        return generate_sample_standard_deviation(idk::move(vec));
    }
};
} // namespace idk

#undef __idk_is_arithmetic