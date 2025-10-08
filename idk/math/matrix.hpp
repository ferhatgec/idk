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
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "../containers/vector.hpp"
#include "../types/predefined.hpp"
#include "../utilities/type_traits.hpp"

#define __idk_is_arithmetic(type_name)                                         \
  idk::EnableIfType<                                                           \
      idk::IntegralConstant<bool, (idk::IsFloatingPointVal<type_name> ||       \
                                   idk::IsIntegralVal<type_name>)>::value,     \
      bool>

namespace idk {
template <typename _Type = long double, __idk_is_arithmetic(_Type) = true>
class Matrix {
  struct ElementWrapper {
  public:
    bool deleted{false};
    _Type data;

    ElementWrapper() : data(static_cast<_Type>(0)) {}
    ElementWrapper(const _Type &_data) : data(_data) {}
    ElementWrapper(_Type &&_data) : data(idk::move(_data)) {}

    ~ElementWrapper() = default;

    [[nodiscard]]
    friend bool operator==(const ElementWrapper &left,
                           const ElementWrapper &right) noexcept {
      return (left.data == right.data) && (left.deleted == right.deleted);
    }

    [[nodiscard]]
    friend bool operator!=(const ElementWrapper &left,
                           const ElementWrapper &right) noexcept {
      return !operator==(left, right);
    }
  };

  struct PositionWrapper {
  public:
    usize row{0}, column{0};

    PositionWrapper() = default;
    PositionWrapper(usize _row, usize _column) noexcept
        : row(_row), column(_column) {}

    PositionWrapper(std::initializer_list<usize> list) noexcept {
      if (list.size() >= 2) {
        this->row = *list.begin();
        this->column = *(list.begin() + 1);
      }
    }

    [[nodiscard]]
    PositionWrapper operator()(usize row = 0, usize column = 0) noexcept {
      return PositionWrapper(row, column);
    }

    ~PositionWrapper() = default;
  };

  mutable Vec<ElementWrapper> _matrix;
  usize _row, _column;

public:
  Matrix(usize row, usize column,
         _Type value = static_cast<_Type>(0)) noexcept {
    this->_matrix.reserve_with_given_value(row * column, ElementWrapper(value));
    this->_row = row;
    this->_column = column;
  }

  Matrix(std::initializer_list<Vec<ElementWrapper>> val) noexcept {
    isize n = 0, w = 0;

    for (const Vec<ElementWrapper> &elem : val) {
      w = elem.size();
      this->_matrix.push_back(elem);
      ++n;
    }

    this->_row = n;
    this->_column = w;
  }

  Matrix(const Matrix<_Type> &val) { *this = val; }

  Matrix(Matrix<_Type> &&val) { *this = idk::move(val); }

  Matrix() = default;
  ~Matrix() = default;

  [[nodiscard]]
  const _Type trace() noexcept {
    if (this->_column != this->_row)
      return 0;

    _Type sum = 0;

    for (isize i = 0; i < this->_column; ++i)
      sum += this->at(i, i);

    return sum;
  }

  [[nodiscard]]
  Matrix<_Type> copy() const noexcept {
    Matrix<_Type> temp_matrix(this->_row, this->_column);

    for (isize i = 0; i < this->_row; ++i)
      for (isize j = 0; j < this->_column; ++j)
        temp_matrix.at(i, j) = this->at(i, j);

    return temp_matrix;
  }

  [[nodiscard]]
  Matrix<_Type> transpose() const noexcept {
    Matrix<_Type> temp_matrix(this->_row, this->_column);

    for (isize i = 0; i < this->_row; ++i)
      for (isize j = 0; j < this->_column; ++j)
        temp_matrix.at(j, i) = this->at(i, j);

    return temp_matrix;
  }

  [[nodiscard]]
  Matrix<_Type> adjoint() const noexcept {
    Matrix<_Type> temp_matrix(this->_row, this->_column);

    for (isize i = 0; i < this->_row; ++i)
      for (isize j = 0; j < this->_column; ++j)
        temp_matrix.at(i, j) = this->cofactor(i, j);

    return temp_matrix.transpose();
  }

  [[nodiscard]]
  Matrix<_Type> inverse() const noexcept {
    if (this->determinant() == 0)
      return {};

    return this->adjoint() / this->determinant();
  }

  [[nodiscard]]
  _Type &at(usize row, usize column) const {
    if (auto _index = row * this->_column + column;
        _index < this->_matrix.size())
      return this->_matrix.at_without_check_reference(_index).data;

    throw std::runtime_error("Matrix::at(row, column) out of bounds exception");
  }

  [[nodiscard]]
  _Type minor(usize ith_row, usize jth_column) const noexcept {
    Matrix<_Type> new_matrix(this->_row - 1, this->_column - 1),
        temp_matrix(this->_row, this->_column);

    temp_matrix._row = this->_row;
    temp_matrix._column = this->_column;
    temp_matrix._matrix = this->_matrix;

    isize row{0}, column{0}, row_skip{0}, column_skip{0}, index{0};

    for (isize i = 0; i < this->_row; ++i) {
      for (isize j = 0; j < this->_column; ++j) {
        if (i == ith_row || j == jth_column) {
          temp_matrix._at_raw(i, j).deleted = true;
          continue;
        }

        new_matrix._matrix.at_without_check_reference(index) =
            temp_matrix._at_raw(i, j);
        ++index;
      }
    }

    return new_matrix.determinant();
  }

  [[nodiscard]]
  _Type cofactor(usize ith_row, usize jth_column) const noexcept {
    if ((ith_row + jth_column) % 2 == 0)
      return this->minor(ith_row, jth_column);

    return -1 * this->minor(ith_row, jth_column);
  }

  [[nodiscard]]
  _Type determinant() const noexcept {
    if (this->_column != this->_row)
      return 0; // pseudo determinant can be used there but later.

    if (this->is_lower_triangular() || this->is_upper_triangular()) {
      _Type sum{static_cast<_Type>(1)};

      for (isize i = 0; i < this->_row; ++i)
        sum *= this->at(i, i);

      return sum;
    }

    switch (this->_column) {
    case 0: {
      return 0;
    }

    case 1: {
      return this->at(0, 0);
    }

    case 2: {
      return (this->at(1, 1) * this->at(0, 0)) -
             (this->at(1, 0) * this->at(0, 1));
    }

    case 3: {
      return ((this->at(0, 0) * this->at(1, 1) * this->at(2, 2)) +
              (this->at(1, 0) * this->at(2, 1) * this->at(0, 2)) +
              (this->at(2, 0) * this->at(0, 1) * this->at(1, 2))) -
             ((this->at(2, 0) * this->at(1, 1) * this->at(0, 2)) +
              (this->at(0, 0) * this->at(2, 1) * this->at(1, 2)) +
              (this->at(1, 0) * this->at(0, 1) * this->at(2, 2)));
    }

    default: {
      _Type sum{static_cast<_Type>(0)};

      // i think there's no significant computation speed difference between
      // selecting row / column which has much more zero elements and a specific
      // row / column.
      for (isize i = 0; i < this->_column; ++i)
        sum += this->at(0, i) * this->cofactor(0, i);

      return sum;
    }
    }
  }

  [[nodiscard]]
  bool is_empty() const noexcept {
    return (this->_column == this->_row == 0);
  }

  [[nodiscard]]
  bool is_square() const noexcept {
    return (this->_column == this->_row);
  }

  [[nodiscard]]
  bool is_identity() const noexcept {
    if (!this->is_square())
      return false;

    for (isize i = 0; i < this->_row; ++i)
      for (isize j = 0; j < this->_column; ++j)
        if (((i == j) && (this->at(i, j) != 1)) ||
            ((i != j) && (this->at(i, j) != 0)))
          return false;

    return true;
  }

  [[nodiscard]]
  bool is_lower_triangular() const noexcept {
    if (!this->is_square())
      return false;

    for (isize i = 1; i < this->_row; ++i)
      for (isize j = 0; j < i; ++j)
        if (this->at(j, i) != 0)
          return false;

    return true;
  }

  [[nodiscard]]
  bool is_upper_triangular() const noexcept {
    if (!this->is_square())
      return false;

    for (isize i = this->_row - 1; i > 0; --i)
      for (isize j = 0; j < i; ++j)
        if (this->at(i, j) != 0)
          return false;

    return true;
  }

  [[nodiscard]]
  bool is_diagonal() const noexcept {
    if (!this->is_square())
      return false;

    for (isize i = 0; i < this->_row; ++i)
      for (isize j = 0; j < this->_column; ++j) {
        if (i == j)
          continue;

        if (this->at(i, j) != 0)
          return false;
      }

    return true;
  }

  [[nodiscard]]
  bool is_scalar() const noexcept {
    if (!this->is_square() || !this->is_diagonal())
      return false;

    const _Type &first_element = this->at(0, 0);

    for (isize i = 1; i < this->_row; ++i)
      if (this->at(i, i) != first_element)
        return false;

    return true;
  }

  [[nodiscard]]
  bool is_symmetric() const noexcept {
    if (!this->is_square())
      return false;

    return this->transpose()._matrix == this->_matrix;
  }

  [[nodiscard]]
  bool is_skew_symmetric() const noexcept {
    if (!this->is_square())
      return false;

    return this->transpose()._matrix == (-1 * this->_matrix);
  }

  [[nodiscard]]
  bool is_idempotent() const noexcept {
    if (!this->is_square())
      return false;

    return (this->copy() * this->copy()) == *this;
  }

  [[nodiscard]]
  bool is_involutory() const noexcept {
    if (!this->is_square())
      return false;

    return (this->copy() * this->copy()).is_identity();
  }

  [[nodiscard]]
  bool is_orthogonal() const noexcept {
    if (!this->is_square() || (this->determinant() == 0))
      return false;

    return this->inverse()._matrix == this->transpose()._matrix;
  }

  [[nodiscard]]
  bool is_singular() const noexcept {
    return this->determinant() == 0;
  }

  [[nodiscard]]
  bool is_nonsingular() const noexcept {
    return this->determinant() != 0;
  }

  [[nodiscard]]
  bool is_vector() const noexcept {
    return (this->is_empty()) || ((this->_row == 1) && (this->_column > 0)) ||
           ((this->_column == 1) && (this->_row > 0));
  }

  [[nodiscard]]
  _Type distance(const Matrix<_Type> &w) const noexcept {
    if (!this->is_vector() || !w.is_vector() ||
        (this->dimension() != w.dimension()))
      return 0;

    _Type sum{static_cast<_Type>(0)};

    for (isize i = 0; i < this->_matrix.size(); ++i)
      sum += powl(this->_matrix.at_without_check_reference(i).data -
                      w._matrix.at_without_check_reference(i).data,
                  2);

    if (sum < 0)
      return 0;

    return static_cast<_Type>(sqrtl(sum));
  }

  [[nodiscard]]
  _Type magnitude() const noexcept {
    if (!this->is_vector())
      return 0;

    return this->distance(Matrix<_Type>(this->_row, this->_column));
  }

  [[nodiscard]]
  _Type length() const noexcept {
    return this->magnitude();
  }

  [[nodiscard]]
  usize dimension() const noexcept {
    return this->_row * this->_column;
  }

  [[nodiscard]]
  _Type dot(const Matrix<_Type> &w) const noexcept {
    if (!this->is_vector() || !w.is_vector() ||
        (this->dimension() != w.dimension()))
      return 0;

    _Type sum{static_cast<_Type>(0)};

    for (isize i = 0; i < this->_matrix.size(); ++i)
      sum += this->_matrix.at_without_check_reference(i).data *
             w._matrix.at_without_check_reference(i).data;

    return sum;
  }

  [[nodiscard]]
  Matrix<_Type> cross(const Matrix<_Type> &w) noexcept {
    if (!this->is_vector() || !w.is_vector() ||
        (this->dimension() != w.dimension()) || (this->dimension() != 3) ||
        (w.dimension() != 3))
      return {};

    const _Type ax = this->_matrix.at_without_check_reference(0).data,
                ay = this->_matrix.at_without_check_reference(1).data,
                az = this->_matrix.at_without_check_reference(2).data,

                bx = w._matrix.at_without_check_reference(0).data,
                by = w._matrix.at_without_check_reference(1).data,
                bz = w._matrix.at_without_check_reference(2).data;

    // one column, 3 rows
    if (this->_row > 1)
      return {{(ay * bz) - (az * by)},
              {(az * bx) - (ax * bz)},
              {(ax * by) - (ay * bx)}};

    // one row, 3 columns
    return {
        {(ay * bz) - (az * by), (az * bx) - (ax * bz), (ax * by) - (ay * bx)}};
  }

  [[nodiscard]]
  Matrix<_Type> unit() const noexcept {
    if (!this->is_vector())
      return this->copy();

    auto length_of_vector = this->length();

    if (length_of_vector == 0)
      return this->copy();

    Matrix<_Type> temp_vector = this->copy();

    for (auto &element : temp_vector._matrix)
      element.data /= length_of_vector;

    return temp_vector;
  }

  // gives angle between two vectors in radians
  [[nodiscard]]
  _Type angle(const Matrix<_Type> &w) const noexcept {
    if (!this->is_vector() || !w.is_vector() ||
        (this->dimension() != w.dimension()))
      return 0;

    const _Type length_mul = (this->length() * w.length());

    if (length_mul == 0)
      return 0;

    return acosl(this->dot(w) / length_mul);
  }

  // gives angle between two vectors in terms of degrees
  [[nodiscard]]
  _Type angle_degrees(const Matrix<_Type> &w) const noexcept {
    return angle(w) * (180 / pi);
  }

  friend std::ostream &operator<<(std::ostream &ostr,
                                  const Matrix<_Type> &val) noexcept {
    if (!val.is_empty()) {
      for (isize i = 0; i < val._row; ++i) {
        ostr << "[ ";

        for (isize j = 0; j < val._column; ++j)
          ostr << val.at(i, j) << ' ';

        ostr << ']';

        if (i + 1 != val._row)
          ostr << '\n';
      }
    }

    return ostr;
  }

  friend std::wostream &operator<<(std::wostream &ostr,
                                   const Matrix<_Type> &val) noexcept {
    if (!val.is_empty()) {
      for (isize i = 0; i < val._row; ++i) {
        ostr << "[ ";

        for (isize j = 0; j < val._column; ++j)
          ostr << val.at(i, j) << ' ';

        ostr << ']';

        if (i + 1 != val._row)
          ostr << '\n';
      }
    }

    return ostr;
  }

  Matrix<_Type> &operator=(const Matrix<_Type> &other) noexcept {
    if (this == &other)
      return *this;

    this->_column = other._column;
    this->_row = other._row;
    this->_matrix = other._matrix;

    return *this;
  }

  Matrix<_Type> &operator=(Matrix<_Type> &&other) noexcept {
    if (this == &other)
      return *this;

    this->_column = other._column;
    this->_row = other._row;
    this->_matrix = other._matrix;

    other._column = other._row = 0;
    other._matrix = {};

    return *this;
  }

  friend Matrix<_Type> operator+(const Matrix<_Type> &left,
                                 const Matrix<_Type> &right) {
    if ((left._column != right._column) || (left._row != right._row))
      return {};

    Matrix<_Type> copy_left(left._row, left._column);

    for (isize i = 0; i < left._row; ++i)
      for (isize j = 0; j < left._column; ++j)
        copy_left.at(i, j) = left.at(i, j) + right.at(i, j);

    return copy_left;
  }

  friend Matrix<_Type> operator-(const Matrix<_Type> &left,
                                 const Matrix<_Type> &right) {
    if ((left._column != right._column) || (left._row != right._row))
      return {};

    Matrix<_Type> copy_left(left._row, left._column);

    for (isize i = 0; i < left._row; ++i)
      for (isize j = 0; j < left._column; ++j)
        copy_left.at(i, j) = left.at(i, j) - right.at(i, j);

    return copy_left;
  }

  friend Matrix<_Type> operator/(const Matrix<_Type> &left,
                                 const _Type &value) {
    if (value == 0)
      return {};

    Matrix<_Type> copy_left(left._row, left._column);

    copy_left = left;

    for (isize i = 0; i < left._row; ++i)
      for (isize j = 0; j < left._column; ++j)
        copy_left.at(i, j) /= value;

    return copy_left;
  }

  friend Matrix<_Type> operator*(const Matrix<_Type> &left,
                                 const _Type &value) {
    Matrix<_Type> copy_left(left._row, left._column);

    copy_left = left;

    for (isize i = 0; i < left._row; ++i)
      for (isize j = 0; j < left._column; ++j)
        copy_left.at(i, j) *= value;

    return copy_left;
  }

  friend Matrix<_Type> operator*(const Matrix<_Type> &left,
                                 const Matrix<_Type> &right) {
    if (left._column != right._row)
      return {};

    if (left.is_identity())
      return right.copy();

    if (right.is_identity())
      return left.copy();

    // left._row * right._column
    if ((ceill(log2l(left._row)) == floorl(log2l(left._row))) &&
        ((left._row == right._row) &&
         (left._column == right._column))) { // both square matrices and 2^n x
                                             // 2^n, no padding is required.
      return left._strassen(left, right);
    } else {
      usize dim = static_cast<usize>(powl(
          2, ceill(log2l(std::max(std::max(left._row, right._row),
                                  std::max(left._column, right._column))))));

      Matrix<_Type> left_temp_matrix(dim, dim), right_temp_matrix(dim, dim);

      // padding with zeroes
      for (isize i = 0; i < left._row; ++i)
        for (isize j = 0; j < left._column; ++j)
          left_temp_matrix.at(i, j) = left.at(i, j);

      for (isize i = 0; i < right._row; ++i)
        for (isize j = 0; j < right._column; ++j)
          right_temp_matrix.at(i, j) = right.at(i, j);

      left_temp_matrix =
          left_temp_matrix._strassen(left_temp_matrix, right_temp_matrix);

      Matrix<_Type> temp_matrix(left._row, right._column);

      // unpadding the result matrix from zeroes
      for (isize i = 0; i < temp_matrix._row; ++i)
        for (isize j = 0; j < temp_matrix._column; ++j)
          temp_matrix.at(i, j) = left_temp_matrix.at(i, j);

      return temp_matrix;
    }
  }

  friend Matrix<_Type> operator*(const _Type &value,
                                 const Matrix<_Type> &right) {
    return operator*(right, value);
  }

  friend Matrix<_Type> operator*(_Type &&value, const Matrix<_Type> &right) {
    return operator*(right, idk::move(value));
  }

  template <typename _Type2>
  friend bool operator==(const Matrix<_Type> &left,
                         const Matrix<_Type2> &right) noexcept {
    if (!idk::IsSameVal<_Type, _Type2> || (left._column != right._column) ||
        (left._row != right._row))
      return false;

    for (isize i = 0; i < (left._row * left._column); ++i)
      if (left._matrix.at_without_check_reference(i) !=
          right._matrix.at_without_check_reference(i))
        return false;

    return true;
  }

  template <typename _Type2>
  friend bool operator!=(const Matrix<_Type> &left,
                         const Matrix<_Type2> &right) noexcept {
    return !operator==(left, right);
  }

  [[nodiscard]]
  _Type &operator[](const PositionWrapper &pos) const noexcept {
    return this->at(pos.row, pos.column);
  }

private:
  [[nodiscard]]
  ElementWrapper &_at_raw(usize row, usize column) const {
    if (auto _index = row * this->_column + column;
        _index < this->_matrix.size())
      return this->_matrix.at_without_check_reference(_index);

    throw std::runtime_error(
        "Matrix::_at_raw(row, column) out of bounds exception.");
  }

  [[nodiscard]]
  Matrix<_Type> _strassen(const Matrix<_Type> &left,
                          const Matrix<_Type> &right) const {
    if (left._row == 1)
      return Matrix<_Type>({{left.at(0, 0) * right.at(0, 0)}});

    Matrix<_Type> A11(left._row / 2, left._row / 2),
        A12(left._row / 2, left._row / 2), A21(left._row / 2, left._row / 2),
        A22(left._row / 2, left._row / 2),

        B11(left._row / 2, left._row / 2), B12(left._row / 2, left._row / 2),
        B21(left._row / 2, left._row / 2), B22(left._row / 2, left._row / 2),

        M1(left._row / 2, left._row / 2), M2(left._row / 2, left._row / 2),
        M3(left._row / 2, left._row / 2), M4(left._row / 2, left._row / 2),
        M5(left._row / 2, left._row / 2), M6(left._row / 2, left._row / 2),
        M7(left._row / 2, left._row / 2);

    for (isize i = 0; i < (left._row / 2); ++i) {
      for (isize j = 0; j < (left._row / 2); ++j) {
        A11.at(i, j) = left.at(i, j);
        A12.at(i, j) = left.at(i, j + (left._row / 2));
        A21.at(i, j) = left.at(i + (left._row / 2), j);
        A22.at(i, j) = left.at(i + (left._row / 2), j + (left._row / 2));

        B11.at(i, j) = right.at(i, j);
        B12.at(i, j) = right.at(i, j + (left._row / 2));
        B21.at(i, j) = right.at(i + (left._row / 2), j);
        B22.at(i, j) = right.at(i + (left._row / 2), j + (left._row / 2));
      }
    }

    M1 = (A11 + A22) * (B11 + B22);
    M2 = (A21 + A22) * B11;
    M3 = A11 * (B12 - B22);
    M4 = A22 * (B21 - B11);
    M5 = (A11 + A12) * B22;
    M6 = (A21 - A11) * (B11 + B12);
    M7 = (A12 - A22) * (B21 + B22);

    A11 = (M1 + M4) - M5 +
          M7; // we use A11 as C11 to reduce variable initialization
    A12 = M3 + M5;
    A21 = M2 + M4;
    A22 = (M1 - M2) + (M3 + M6);

    Matrix<_Type> result(left._row, left._row);

    for (isize i = 0; i < A11._row; ++i)
      for (isize j = 0; j < A11._column; ++j)
        result.at(i, j) = A11.at(i, j);

    for (isize i = 0; i < A12._row; ++i)
      for (isize j = 0; j < A12._column; ++j)
        result.at(i, j + A11._column) = A12.at(i, j);

    for (isize i = 0; i < A21._row; ++i)
      for (isize j = 0; j < A21._column; ++j)
        result.at(i + A12._row, j) = A21.at(i, j);

    for (isize i = 0; i < A22._row; ++i)
      for (isize j = 0; j < A22._column; ++j)
        result.at(i + A21._row, j + A21._column) = A22.at(i, j);

    return result;
  }
};
} // namespace idk

#undef __idk_is_arithmetic