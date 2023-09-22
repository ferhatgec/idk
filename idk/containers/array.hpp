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
#include "../types/valueor.hpp"
#include <utility>
#include <initializer_list>
#include <iostream>

namespace idk {
template<typename Val, usize N>
class Arr {
public:
    enum class Error {
        Out_Of_Range,
        ArrayEmpty
    };

    Arr(std::initializer_list<Val>&& val) {
        usize n = 0;
        for(Val _val: std::move(val)) {
            this->_arr[n++] = _val;
        }
    }

    Val&
    front() noexcept {
        if(this->is_empty())
            return this->_emptyarr;
        
        return this->_arr[0];
    }

    Val&
    back() noexcept {
        if(this->is_empty())
            return this->_emptyarr;
        
        return this->_arr[N - 1];
    }

    ValueOr<Val, Error>
    front_no_reference() noexcept {
        if(this->is_empty())
            return Unexpected<Error>(Error::ArrayEmpty);

        return Expected<typename std::remove_reference<Val&>::type>(this->front());
    }

    ValueOr<Val, Error>
    back_no_reference() noexcept {
        if(this->is_empty())
            return Unexpected<Error>(Error::ArrayEmpty);

        return Expected<typename std::remove_reference<Val&>::type>(this->back());
    }

    constexpr Val*
    begin() noexcept {
        return _arr;
    }

    Val*
    end() noexcept {
        if(this->is_empty())
            return _arr;

        return _arr + N;
    }

    void
    fill(const Val& val) {
        for(Val& _val: this->_arr)
            _val = val;
    }
    
    [[nodiscard]]
    constexpr bool 
    is_empty() const noexcept {
        return N == 0;
    }

    [[nodiscard]]
    constexpr usize 
    size() const noexcept {
        return N;
    }

    [[nodiscard]]
    constexpr usize 
    max_size() const noexcept {
        return this->size();
    }

    ValueOr<Val, Error>
    operator[](const usize&& n) noexcept {
        return this->at(std::move(n));
    }

    ValueOr<Val, Error>
    operator[](const usize& n) noexcept {
        return this->at(std::move(n));
    }

    ValueOr<Val, Error>
    at(const usize&& n) noexcept {
        if(n < this->size())
            return Expected(this->_arr[n]);

        return Unexpected(Error::Out_Of_Range);
    }

    template<typename _Val, usize _N>
    friend std::ostream&
    operator<<(std::ostream& ostr, const Arr<_Val, _N>& arr) {
        ostr << '[';
        
        for(usize n = 0; n < arr.size(); ++n)
            if(n + 1 == arr.size())
                ostr << arr.data()[n]; // Val must overload operator<< if not known type
            else
                ostr << arr.data()[n] << ", ";

        ostr << ']';
        return ostr;
    }

    template<typename _Val, typename _Val2,
            usize _N, usize _N2>
    friend bool 
    operator==(const Arr<_Val, _N>& left, const Arr<_Val2, _N2>& right) noexcept {
        if constexpr(!std::is_same_v<_Val, _Val2> || (_N != _N2)) 
            return false;

        for(usize n = 0; n < left.size(); ++n)
            if(left.data()[n] != right.data()[n])
                return false;

        return true;
    }

    template<typename _Val, typename _Val2,
            usize _N, usize _N2>
    friend bool 
    operator!=(const Arr<_Val, _N>& left, const Arr<_Val2, _N2>& right) noexcept {
        return !this->operator==(left, right);
    }

    constexpr Val*
    data() const noexcept {
        return const_cast<Val*>(this->_arr);
    }

    [[nodiscard]]
    bool 
    change_val_at_index(const usize& index, const Val& replace) noexcept {
        if(this->is_empty() || index >= this->size())
            return false;

        usize i = 0;

        while(i != index) {
            ++i;
        }

        this->_arr[i] = replace;
        
        return true;
    }

    [[nodiscard]]
    bool 
    change_val_at_index(usize&& index, Val&& replace) noexcept {
        if(this->is_empty() || index >= this->size())
            return false;

        usize i = 0;

        while(i != index) {
            ++i;
        }

        this->_arr[i] = std::move(replace);
        
        return true;
    }

    [[nodiscard]]
    bool
    contains(Val&& val) noexcept {
        return this->contains(val);
    }

    [[nodiscard]]
    bool
    contains(const Val& val) noexcept {
        for(auto& _val: *this)
            if(_val == val)
                return true;

        return false;
    }

    [[nodiscard]]
    isize
    find(const Val& val) noexcept {
        for(usize n = 0; n < N; ++n)
            if(this->_arr[n] == val)
                return n;

        return -1;
    }

    [[nodiscard]]
    isize
    find(Val&& val) noexcept {
        return this->find(val);
    }
private:
    Val _arr[N];
    Val _emptyarr;
};
}