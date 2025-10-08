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
#include "../sort/quicksort.hpp"
#include "../types/predefined.hpp"

namespace idk {
class [[nodiscard]] MeanAbsoluteError {
public:
  [[nodiscard]]
  static const f80 generate(const idk::Vec<f80> &x,
                            const idk::Vec<f80> &y) noexcept {
    if ((x.size() != y.size()) || (x.is_empty()))
      return 0;

    f80 sum{0_f80};

    for (isize i = 0; i < x.size(); ++i) {
      sum += fabsl(y.at_without_check_reference(i) -
                   x.at_without_check_reference(i));
    }

    return (sum / static_cast<f80>(x.size()));
  }
};

class [[nodiscard]] MeanSquaredError {
public:
  [[nodiscard]]
  static const f80 generate(const idk::Vec<f80> &y,
                            const idk::Vec<f80> &y_predict) noexcept {
    if ((y.size() != y_predict.size()) || (y.is_empty()))
      return 0;

    f80 sum{0_f80};

    for (isize i = 0; i < y.size(); ++i) {
      const f80 _temp_val = y.at_without_check_reference(i) -
                            y_predict.at_without_check_reference(i);
      sum += (_temp_val * _temp_val);
    }

    return (sum / static_cast<f80>(y.size()));
  }
};

class [[nodiscard]] MedianAbsoluteDeviation {
public:
  [[nodiscard]]
  static const f80 generate(const idk::Vec<f80> &x,
                            bool is_sorted = false) noexcept {
    if (!is_sorted) {
      QuickSort<f80> _sort_init(x);
      _sort_init.sort();
      return MedianAbsoluteDeviation::generate(_sort_init._vec, true);
    }

    f80 current_median{0_f80};

    if ((x.size() % 2 == 0) && ((x.size() / 2) + 1) < x.size())
      current_median = (x.at_without_check_reference(x.size() / 2) +
                        x.at_without_check_reference((x.size() / 2) + 1)) /
                       2_f80;
    else if ((x.size() % 2) == 1)
      current_median = (x.at_without_check_reference(floorl(x.size() / 2)));
    else
      return 0_f80;

    for (isize i = 0; i < x.size(); ++i)
      x.at_without_check_reference(i) =
          fabsl(x.at_without_check_reference(i) - current_median);

    if ((x.size() % 2 == 0) && ((x.size() / 2) + 1) < x.size())
      current_median = (x.at_without_check_reference(x.size() / 2) +
                        x.at_without_check_reference((x.size() / 2) + 1)) /
                       2_f80;
    else if ((x.size() % 2) == 1)
      current_median = (x.at_without_check_reference(floorl(x.size() / 2)));
    else
      return 0_f80;

    return current_median;
  }
};

class [[nodiscard]] RootMeanSquaredLogError {
public:
  [[nodiscard]]
  static const f80 generate(const idk::Vec<f80> &y,
                            const idk::Vec<f80> &y_predict) noexcept {
    if ((y.size() != y_predict.size()) || (y.is_empty()))
      return 0;

    f80 sum{0_f80};

    for (isize i = 0; i < y.size(); ++i) {
      const f80 _temp_val = logl(y.at_without_check_reference(i) + 1) -
                            logl(y_predict.at_without_check_reference(i) + 1);
      sum += _temp_val * _temp_val;
    }

    sum /= static_cast<f80>(y.size());

    if (sum < 0)
      return 0;

    return sqrtl(sum);
  }
};

class [[nodiscard]] MeanAbsolutePercentageError {
public:
  [[nodiscard]]
  static const f80 generate(const idk::Vec<f80> &actual,
                            const idk::Vec<f80> &forecast) noexcept {
    if ((actual.size() != forecast.size()) || (actual.is_empty()))
      return 0;

    f80 sum{0_f80};

    for (isize i = 0; i < actual.size(); ++i)
      sum += fabsl(1 - (forecast.at_without_check_reference(i) /
                        actual.at_without_check_reference(i)));

    return sum / static_cast<f80>(actual.size());
  }
};

[[nodiscard]]
const f80 mean_absolute_error(const idk::Vec<f80> &x,
                              const idk::Vec<f80> &y) noexcept {
  return MeanAbsoluteError::generate(x, y);
}

[[nodiscard]]
const f80 mean_squared_error(const idk::Vec<f80> &y,
                             const idk::Vec<f80> &y_predict) noexcept {
  return MeanSquaredError::generate(y, y_predict);
}

[[nodiscard]]
const f80 median_absolute_deviation(const idk::Vec<f80> &x) noexcept {
  return MedianAbsoluteDeviation::generate(x);
}

[[nodiscard]]
const f80 root_mean_squared_log_error(const idk::Vec<f80> &y,
                                      const idk::Vec<f80> &y_predict) noexcept {
  return RootMeanSquaredLogError::generate(y, y_predict);
}

[[nodiscard]]
const f80
mean_absolute_percentage_error(const idk::Vec<f80> &actual,
                               const idk::Vec<f80> &forecast) noexcept {
  return MeanAbsolutePercentageError::generate(actual, forecast);
}
} // namespace idk