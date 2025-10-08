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

#include "../containers/vector.hpp"
#include "../types/predefined.hpp"
#include <cmath>

namespace idk {
[[nodiscard]]
f80 generate_am(const Vec<f80> &vec) noexcept {
  if (vec.is_empty())
    return 0;

  f80 sum{0};

  for (auto &val : const_cast<Vec<f80> &>(vec))
    sum += val;

  return (static_cast<f80>(sum) / static_cast<f80>(vec.size()));
}

[[nodiscard]]
f80 generate_am(const Vec<isize> &vec) noexcept {
  if (vec.is_empty())
    return 0;

  isize sum{0};

  for (auto &val : const_cast<Vec<isize> &>(vec))
    sum += val;

  return (static_cast<f80>(sum) / static_cast<f80>(vec.size()));
}

[[nodiscard]]
f80 generate_gm(const Vec<f80> &vec) noexcept {
  if (vec.is_empty())
    return 0;

  f80 sum{1};

  for (auto &val : const_cast<Vec<f80> &>(vec))
    sum *= val;

  return std::pow(sum, static_cast<f80>(1) / static_cast<f80>(vec.size()));
}

[[nodiscard]]
f80 generate_gm(const Vec<isize> &vec) noexcept {
  if (vec.is_empty())
    return 0;

  isize sum{1};

  for (auto &val : const_cast<Vec<isize> &>(vec))
    sum *= val;

  return std::pow(static_cast<f80>(sum),
                  static_cast<f80>(1) / static_cast<f80>(vec.size()));
}

[[nodiscard]]
f80 generate_hm(const Vec<f80> &vec) noexcept {
  f80 sum{0};

  for (auto &val : const_cast<Vec<f80> &>(vec)) {
    if (val == 0)
      return 0;

    sum += (static_cast<f80>(1) / val);
  }

  if (sum == 0)
    return 0;

  return (static_cast<f80>(vec.size()) / sum);
}

[[nodiscard]]
f80 generate_hm(const Vec<isize> &vec) noexcept {
  f80 sum{0};

  for (auto &val : const_cast<Vec<isize> &>(vec)) {
    if (val == 0)
      return 0;

    sum += (static_cast<f80>(1) / static_cast<f80>(val));
  }

  if (sum == 0)
    return 0;

  return (static_cast<f80>(vec.size()) / sum);
}

[[nodiscard]]
f80 generate_gem(const Vec<f80> &vec, f80 p) noexcept {
  if (vec.is_empty())
    return 0;

  if (p == -1) // harmonic mean
    return generate_hm(vec);
  else if (p == 0) // geometric mean
    return generate_gm(vec);
  else if (p == 1) // arithmetic mean
    return generate_am(vec);

  f80 sum{0};

  for (auto &val : const_cast<Vec<f80> &>(vec))
    sum += std::pow(val, p);

  sum = (static_cast<f80>(1) / static_cast<f80>(vec.size())) * sum;

  return std::pow(sum, static_cast<f80>(1) / p);
}

[[nodiscard]]
f80 generate_gem(const Vec<isize> &vec, f80 p) noexcept {
  if (vec.is_empty())
    return 0;

  if (p == -1) // harmonic mean
    return generate_hm(vec);
  else if (p == 0) // geometric mean
    return generate_gm(vec);
  else if (p == 1) // arithmetic mean
    return generate_am(vec);

  f80 sum{0};

  for (auto &val : const_cast<Vec<isize> &>(vec))
    sum += std::pow(val, p);

  sum = (static_cast<f80>(1) / static_cast<f80>(vec.size())) * sum;

  return std::pow(sum, static_cast<f80>(1) / p);
}

class [[nodiscard]] ArithmeticMeanGenerator {
public:
  [[nodiscard]]
  static f80 generate(const Vec<f80> &vec) noexcept {
    return generate_am(vec);
  }

  [[nodiscard]]
  static f80 generate(const Vec<isize> &vec) noexcept {
    return generate_am(vec);
  }
};

class [[nodiscard]] GeometricMeanGenerator {
public:
  [[nodiscard]]
  static f80 generate(const Vec<f80> &vec) noexcept {
    return generate_gm(vec);
  }

  [[nodiscard]]
  static f80 generate(const Vec<isize> &vec) noexcept {
    return generate_gm(vec);
  }
};

class [[nodiscard]] HarmonicMeanGenerator {
public:
  [[nodiscard]]
  static f80 generate(const Vec<f80> &vec) noexcept {
    return generate_hm(vec);
  }

  [[nodiscard]]
  static f80 generate(const Vec<isize> &vec) noexcept {
    return generate_hm(vec);
  }
};

class [[nodiscard]] GeneralizedMeanGenerator {
public:
  [[nodiscard]]
  static f80 generate(const Vec<f80> &vec, f80 p) noexcept {
    return generate_gem(vec, p);
  }

  [[nodiscard]]
  static f80 generate(const Vec<isize> &vec, f80 p) noexcept {
    return generate_gem(vec, p);
  }
};
} // namespace idk