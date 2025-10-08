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
// Copyright (c) 2023-2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "../types/predefined.hpp"
#include "../types/valueor.hpp"
#include "../utilities/semantics.hpp"
#include "../utilities/type_traits.hpp"
#include <iostream>

namespace idk {
template <typename Type> class Vector {
public:
  enum class Error {
    Out_Of_Range,
  };

  Vector(Type *val) {
    if (val != nullptr) {
      Type *ptr = val;

      while (ptr != nullptr) {
        this->push_back(*(ptr));
        ptr++;
      }
    } else {
      this->_capacity = this->_size = 0;
    }
  }

  Vector(const Vector<Type> &val)
      : _p(nullptr), _size(val._size), _capacity(val._capacity) {
    if (this->_capacity > 0) {
      this->_p = new Type[this->_capacity];

      for (usize n = 0; n < this->_size; ++n) {
        this->_p[n] = val._p[n];
      }
    }
  }

  Vector(Vector<Type> &&val) noexcept
      : _p(val._p), _size(val._size), _capacity(val._capacity) {
    val._p = nullptr;
    val._size = 0;
    val._capacity = 0;
  }

  Vector(usize n) {
    this->_capacity = n;
    this->_size = 0;
    this->_p = new Type[this->_capacity];
  }

  Vector(usize n, const Type &val) {
    this->reserve_if_needed_with_given_value(n, val);
  }

  Vector(std::initializer_list<Type> vals) {
    for (const Type &val : vals)
      this->push_back(val);
  }

  Vector() {
    this->_p = new Type[_capacity_constant];
    this->_capacity = _capacity_constant;
    this->_size = 0;
  }

  ~Vector() {
    if (!this->is_empty()) {
      delete[] this->_p;
      this->_p = nullptr;
    }
  }

  ValueOr<Type, Error> operator[](usize n) noexcept { return this->at(n); }

  Vector<Type> &operator=(const Vector<Type> &other) {
    if (this == &other)
      return *this;

    if (this->_p) {
      delete[] this->_p;
      this->_p = nullptr;
    }

    this->_size = other._size;
    this->_capacity = other._capacity;

    if (this->_capacity > 0) {
      this->_p = new Type[_capacity];

      for (usize n = 0; n < this->_size; ++n) {
        this->_p[n] = other._p[n];
      }
    }
    return *this;
  }

  Vector<Type> &operator=(Vector<Type> &&other) noexcept {
    if (this == &other)
      return *this;

    if (this->_p) {
      delete[] this->_p;
      this->_p = nullptr;
    }

    this->_p = other._p;
    this->_size = other._size;
    this->_capacity = other._capacity;

    other._p = nullptr;
    other._size = 0;
    other._capacity = 0;
    return *this;
  }

  template <typename _Type2>
  friend bool operator==(const Vector<Type> &left,
                         const Vector<_Type2> &right) noexcept {
    if (!idk::IsSameVal<Type, _Type2> || left.size() != right.size())
      return false;

    for (usize n = 0; n < left.size(); ++n)
      if (left._p[n] != right._p[n])
        return false;

    return true;
  }

  template <typename _Type2>
  friend bool operator==(const Vector<Type> &left,
                         const _Type2 *right) noexcept {
    if (!right)
      return false;

    if (!idk::IsSameVal<Type, _Type2> ||
        left.size() != (sizeof(right) / sizeof(right[0])))
      return false;

    for (usize n = 0; n < left.size(); ++n)
      if (left._p[n] != right._p[n])
        return false;

    return true;
  }

  template <typename _Type2>
  friend bool operator!=(const Vector<Type> &left,
                         const Vector<_Type2> &right) noexcept {
    return !operator==(left, right);
  }

  template <typename _Type2>
  friend bool operator!=(const Vector<Type> &left,
                         const _Type2 *right) noexcept {
    return !operator==(left, right);
  }

  Type &front() {
    if (!this->is_empty())
      return this->_p[0];

    return this->_nullp;
  }

  Type &back() {
    if (!this->is_empty())
      return this->_p[this->_size - 1];

    return this->_nullp;
  }

  ValueOr<Type, Error> front_no_reference() noexcept {
    if (!this->is_empty())
      return Expected<Type>(this->at_without_check(0));

    return Unexpected<Error>(Error::Out_Of_Range);
  }

  ValueOr<Type, Error> back_no_reference() noexcept {
    if (!this->is_empty())
      return Expected<Type>(this->at_without_check(this->_size - 1));

    return Unexpected<Error>(Error::Out_Of_Range);
  }

  Type at_without_check(usize n) const { return this->_p[n]; }

  Type &at_without_check_reference(usize n) const { return this->_p[n]; }

  Type *begin() const { return this->_p; }

  Type *end() const {
    if (this->is_empty())
      return this->_p;

    return this->_p + (this->_size);
  }

  ValueOr<Type, Error> at(usize n) const noexcept {
    if (n < this->_size)
      return Expected<Type>(this->at_without_check(n));

    return Unexpected<Error>(Error::Out_Of_Range);
  }

  [[nodiscard]]
  bool is_empty() const noexcept {
    return this->_size == 0;
  }

  void push_back(Type &&val) noexcept {
    this->reserve_if_needed(this->_size + _capacity_constant + 1);
    this->_p[this->_size++] = idk::move(val);
  }

  void push_back(const Type &val) noexcept {
    this->reserve_if_needed(this->_size + _capacity_constant + 1);
    this->_p[this->_size++] = val;
  }

  void push_back(Vector<Type> &&val) noexcept {
    this->reserve_if_needed(this->_size + val._size + 1);

    for (Type &&elem : idk::move(val))
      this->_p[this->_size++] = idk::move(elem);
  }

  void push_back(const Vector<Type> &val) noexcept {
    this->reserve_if_needed(this->_size + _capacity_constant + val._size + 1);

    for (Type &elem : const_cast<Vector<Type> &>(val))
      this->_p[this->_size++] = elem;
  }

  void push_front(const Type &val) noexcept {
    this->reserve_if_needed(this->_size + _capacity_constant);
    ++this->_size;
    for (usize i = this->_size; i > 0; --i) {
      this->_p[i] = this->_p[i - 1];
    }
    this->_p[0] = val;
  }

  void pop_back() noexcept {
    if (this->is_empty())
      return;

    --this->_size; // better than reallocating and copying everything imo,
                   // when push_back() used later, current element will be
                   // overwritten.
  }

  void reserve_if_needed(usize val) noexcept {
    if (val > this->_capacity || this->is_empty()) {
      this->reserve(val);
    }
  }

  void reserve_if_needed_with_given_value(usize val,
                                          const Type &value) noexcept {
    if (val > this->_capacity || this->is_empty()) {
      this->reserve_with_given_value(val, value);
    }
  }

  void reserve(usize val) noexcept {
    Type *temp = new Type[val];

    for (usize n = 0; (n < val) && (n < this->_size); ++n)
      temp[n] = this->_p[n];

    if (!this->is_empty()) {
      delete[] this->_p;
      this->_p = nullptr;
    }

    this->_capacity = val;
    this->_p = temp;
  }

  void reserve_with_given_value(usize val, const Type &value) noexcept {
    Type *temp = new Type[val];

    for (usize n = 0; n < val; ++n)
      temp[n] = value;

    if (!this->is_empty()) {
      delete[] this->_p;
      this->_p = nullptr;
    }

    this->_capacity = val;
    this->_size = this->_capacity;
    this->_p = temp;
  }

  [[nodiscard]]
  usize size() const noexcept {
    return this->_size;
  }

  [[nodiscard]]
  usize capacity() const noexcept {
    return this->_capacity;
  }

  friend std::ostream &operator<<(std::ostream &ostr, const Vector<Type> &arr) {
    ostr << '[';

    for (usize n = 0; n < arr.size(); ++n)
      if (n + 1 == arr.size())
        ostr << arr.data()[n]; // Val must overload operator<< if not known type
      else
        ostr << arr.data()[n] << ", ";

    ostr << ']';
    return ostr;
  }

  constexpr Type *data() const noexcept { return const_cast<Type *>(this->_p); }

  [[nodiscard]]
  bool contains(Type &val) noexcept {
    for (auto &elem : *this)
      if (elem == val)
        return true;

    return false;
  }

  [[nodiscard]]
  bool contains(Type &&val) noexcept {
    return this->contains(val);
  }

  void clear() noexcept {
    while (!this->is_empty())
      this->pop_back();
  }

  [[nodiscard]]
  bool change_val_at_index(usize index, const Type &replace) noexcept {
    if (this->is_empty() || index >= this->size())
      return false;

    this->_p[index] = replace;
    return true;
  }

  [[nodiscard]]
  bool change_val_at_index(usize index, Type &&replace) noexcept {
    if (this->is_empty() || index >= this->size())
      return false;

    this->_p[index] = idk::move(replace);
    return true;
  }

  [[nodiscard]]
  isize find(const Type &val) noexcept {
    for (usize n = 0; n < this->_size; ++n)
      if (this->_p[n] == val)
        return n;

    return -1;
  }

  [[nodiscard]]
  isize find(Type &&val) noexcept {
    return this->find(val);
  }

private:
  static inline constexpr u16 _capacity_constant = 8;

  Type *_p = nullptr;

  usize _capacity{_capacity_constant}, _size{0};

  Type _nullp;
};

template <typename Type> using Vec = Vector<Type>;
} // namespace idk