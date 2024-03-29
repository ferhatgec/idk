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
// Copyright (c) 2023-2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "type_traits.hpp"
#include "semantics.hpp"
#include "../types/any.hpp"

namespace idk {
template<typename T, typename U>
class Pair {
public:
    Pair() : _first(T()), _second(U()) {}
    
    Pair(T&& first, U&& second) 
        : _first(idk::move(first)), _second(idk::move(second)) {}

    Pair(std::initializer_list<idk::Any>&& list) {
      if(list.size() >= 2) {
        this->_first = (list.begin())->cast_to_directly<T>();
        this->_second = (list.begin() + 1)->cast_to_directly<U>();
      }
    }

    Pair(const T& first, const U& second) 
        : _first(const_cast<T&>(first)), _second(const_cast<U&>(second)) {}

    ~Pair() = default;
    
    T&
    first() noexcept {
        return this->_first;
    }

    U&
    second() noexcept {
        return this->_second;
    }

    Pair<T, U>&
    operator=(const Pair<T, U>& other) noexcept {
        if(&other == this)
            return *this;

        this->_first  = other._first;
        this->_second = other._second;
        
        return *this;
    }

/*
    Pair<T, U>&
    operator=(Pair<T, U>&& other) noexcept {
        if(&other == this)
            return *this;

        this->_first  = other._first;
        this->_second = other._second;
        
        return *this;
    }
*/

    template<typename Tn, typename Un>
    friend bool 
    operator==(const Pair<T, U>& left, const Pair<Tn, Un>& right) noexcept {
        if(!idk::IsSameVal<T, Tn> || !idk::IsSameVal<U, Un>)
            return false;

        return (left._first == right._first) && (left._second == right._second);
    }

    template<typename Tn, typename Un>
    friend bool 
    operator!=(const Pair<T, U>& left, const Pair<Tn, Un>& right) noexcept {
        return !operator==(left, right);
    }

#ifdef __idk_experimental
    friend std::ostream&
    operator<<(std::ostream& ostr, const idk::Pair<T, U>& right) {
        ostr << "( ";
        
        if constexpr(idk::IsPrintable<T>::value) {
            ostr << right._first; 
        } else {
            ostr << '_';
        }
        
        ostr << ", ";

        if constexpr(idk::IsPrintable<U>::value) {
            ostr << right._second;
        } else {
            ostr << '_';
        }

        ostr << " )";

        return ostr;
    }

    friend std::wostream&
    operator<<(std::wostream& ostr, const idk::Pair<T, U>& right) {
        ostr << L"( ";
        
        if constexpr(idk::IsPrintable<T>::value) {
            ostr << right._first; 
        } else {
            ostr << L'_';
        }
        
        ostr << L", ";

        if constexpr(idk::IsPrintable<U>::value) {
            ostr << right._second;
        } else {
            ostr << L'_';
        }

        ostr << L" )";

        return ostr;
    }

    friend std::ostream&
    operator<<(std::ostream& ostr, idk::Pair<T, U>&& right) {
        return operator<<(ostr, right);
    }

    friend std::wostream&
    operator<<(std::wostream& ostr, idk::Pair<T, U>&& right) {
        return operator<<(ostr, right);
    }
#endif // __idk_experimental

    T _first;
    U _second;
};

template<typename T, typename U>
Pair<T, U> 
MakePair(T&& first, U&& second) noexcept {
    return Pair<T, U>(first, second);
}

template<typename T, typename U>
Pair<T, U> 
MakePair(const T& first, const U& second) noexcept {
    return Pair<T, U>(first, second);
}
} // namespace idk