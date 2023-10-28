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
#include <cmath>

namespace idk {
__idk_nodiscard
f80
generate_am(const Vec<f80>& vec) noexcept {
    if(vec.is_empty())
        return 0;

    f80 sum { 0 };

    for(auto& val: const_cast<Vec<f80>&>(vec))
        sum += val;

    return (static_cast<f80>(sum) / static_cast<f80>(vec.size()));
}

__idk_nodiscard
f80
generate_am(const Vec<isize>& vec) noexcept {
    if(vec.is_empty())
        return 0;
    
    isize sum { 0 };

    for(auto& val: const_cast<Vec<isize>&>(vec))
        sum += val;

    return (static_cast<f80>(sum) / static_cast<f80>(vec.size()));
}

__idk_nodiscard
f80
generate_am(Vec<f80>&& vec) noexcept {
    return generate_am(vec);
}

__idk_nodiscard
f80
generate_am(Vec<isize>&& vec) noexcept {
    return generate_am(vec);
}

__idk_nodiscard
f80
generate_gm(const Vec<f80>& vec) noexcept {
    if(vec.is_empty())
        return 0;
    
    f80 sum { 1 };

    for(auto& val: const_cast<Vec<f80>&>(vec))
        sum *= val;

    return std::pow(sum, static_cast<f80>(1) / static_cast<f80>(vec.size()));
}

__idk_nodiscard
f80
generate_gm(const Vec<isize>& vec) noexcept {
    if(vec.is_empty())
        return 0;

    isize sum { 1 };

    for(auto& val: const_cast<Vec<isize>&>(vec))
        sum *= val;

    return std::pow(static_cast<f80>(sum), static_cast<f80>(1) / static_cast<f80>(vec.size()));
}

__idk_nodiscard
f80
generate_gm(Vec<f80>&& vec) noexcept {
    return generate_gm(vec);
}

__idk_nodiscard
f80
generate_gm(Vec<isize>&& vec) noexcept {
    return generate_gm(vec);
}

__idk_nodiscard
f80
generate_hm(const Vec<f80>& vec) noexcept {
    f80 sum { 0 };

    for(auto& val: const_cast<Vec<f80>&>(vec)) {
        if(val == 0)
            return 0;

        sum += (static_cast<f80>(1) / val);
    }

    if(sum == 0)
        return 0;
    
    return (static_cast<f80>(vec.size()) / sum);
}

__idk_nodiscard
f80
generate_hm(const Vec<isize>& vec) noexcept {
    f80 sum { 0 };

    for(auto& val: const_cast<Vec<isize>&>(vec)) {
        if(val == 0)
            return 0;

        sum += (static_cast<f80>(1) / static_cast<f80>(val));
    }

    if(sum == 0)
        return 0;
    
    return (static_cast<f80>(vec.size()) / sum);
}

__idk_nodiscard
f80
generate_hm(Vec<f80>&& vec) noexcept {
    return generate_hm(vec);
}

__idk_nodiscard
f80
generate_hm(Vec<isize>&& vec) noexcept {
    return generate_hm(vec);
}

__idk_nodiscard
f80
generate_gem(const Vec<f80>& vec, f80 p) noexcept {
    if(vec.is_empty())
        return 0;

    if(p == -1) // harmonic mean
        return generate_hm(vec);
    else if(p == 0) // geometric mean
        return generate_gm(vec);
    else if(p == 1) // arithmetic mean
        return generate_am(vec);

    f80 sum { 0 };

    for(auto& val: const_cast<Vec<f80>&>(vec))
        sum += std::pow(val, p);

    sum = (static_cast<f80>(1) / static_cast<f80>(vec.size())) * sum;

    return std::pow(sum, static_cast<f80>(1) / p);
}

__idk_nodiscard
f80
generate_gem(const Vec<isize>& vec, f80 p) noexcept {
    if(vec.is_empty())
        return 0;

    if(p == -1) // harmonic mean
        return generate_hm(vec);
    else if(p == 0) // geometric mean
        return generate_gm(vec);
    else if(p == 1) // arithmetic mean
        return generate_am(vec);

    f80 sum { 0 };

    for(auto& val: const_cast<Vec<isize>&>(vec))
        sum += std::pow(val, p);

    sum = (static_cast<f80>(1) / static_cast<f80>(vec.size())) * sum;

    return std::pow(sum, static_cast<f80>(1) / p);
}

__idk_nodiscard
f80
generate_gem(Vec<f80>&& vec, f80 p) noexcept {
    return generate_gem(vec, p);
}

__idk_nodiscard
f80
generate_gem(Vec<isize>&& vec, f80 p) noexcept {
    return generate_gem(vec, p);
}

class __idk_nodiscard ArithmeticMeanGenerator {
public:
    __idk_nodiscard
    static f80 
    generate(const Vec<f80>& vec) noexcept {
        return generate_am(vec);
    }

    __idk_nodiscard
    static f80 
    generate(const Vec<isize>& vec) noexcept {
        return generate_am(vec);
    }

    __idk_nodiscard
    static f80
    generate(Vec<f80>&& vec) noexcept {
        return generate_am(idk::move(vec));
    }
    
    __idk_nodiscard
    static f80
    generate(Vec<isize>&& vec) noexcept {
        return generate_am(idk::move(vec));
    }
};

class __idk_nodiscard GeometricMeanGenerator {
public:
    __idk_nodiscard
    static f80 
    generate(const Vec<f80>& vec) noexcept {
        return generate_gm(vec);
    }

    __idk_nodiscard
    static f80 
    generate(const Vec<isize>& vec) noexcept {
        return generate_gm(vec);
    }

    __idk_nodiscard
    static f80
    generate(Vec<f80>&& vec) noexcept {
        return generate_gm(idk::move(vec));
    }

    __idk_nodiscard
    static f80
    generate(Vec<isize>&& vec) noexcept {
        return generate_gm(idk::move(vec));
    }
};

class __idk_nodiscard HarmonicMeanGenerator {
public:
    __idk_nodiscard
    static f80
    generate(const Vec<f80>& vec) noexcept {
        return generate_hm(vec);
    }

    __idk_nodiscard
    static f80
    generate(const Vec<isize>& vec) noexcept {
        return generate_hm(vec);
    }

    __idk_nodiscard
    static f80
    generate(Vec<f80>&& vec) noexcept {
        return generate_hm(idk::move(vec));
    }

    __idk_nodiscard
    static f80
    generate(Vec<isize>&& vec) noexcept {
        return generate_hm(idk::move(vec));
    }
};

class __idk_nodiscard GeneralizedMeanGenerator {
public:
    __idk_nodiscard
    static f80
    generate(const Vec<f80>& vec, f80 p) noexcept {
        return generate_gem(vec, p);
    }

    __idk_nodiscard
    static f80
    generate(const Vec<isize>& vec, f80 p) noexcept {
        return generate_gem(vec, p);
    }

    __idk_nodiscard
    static f80
    generate(Vec<f80>&& vec, f80 p) noexcept {
        return generate_gem(idk::move(vec), p);
    }

    __idk_nodiscard
    static f80
    generate(Vec<isize>&& vec, f80 p) noexcept {
        return generate_gem(idk::move(vec), p);
    }
};
} // namespace idk