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
#include <iostream>

namespace idk {
template<typename Type>
class Vec {
public:
    enum class Error {
        Out_Of_Range,
    };

    Vec(Type*& val) : p(val) {
        if(val != nullptr) {
            this->_capacity = val->capacity;
            this->_size = val->size;
        } else
            this->_capacity = this->_size = 0;
    }

    Vec(Vec<Type>& val) : _p(val._p), _size(val._size), _capacity(val._capacity) {

    }
    
    Vec(Vec<Type>&& val) {
        this = std::move(val);
    }
    
    Vec(usize&& n, Type&& val) {
        this->reserve_if_needed_with_given_value(std::move(n), val);
    }

    Vec(usize&& n, Type& val) {
        this->reserve_if_needed_with_given_value(std::move(n), val);
    }

    Vec(usize&& n, Type const& val) {
        this->reserve_if_needed_with_given_value(std::move(n), const_cast<Type&>(val));
    }

    Vec(std::initializer_list<Type> vals) {
        for(const Type& val: vals)
            this->push_back(val);
    }

    Vec() {
        this->_p = nullptr;
        this->_capacity = this->_size = 0;
    }

    ~Vec() {
        if(this->is_empty())
            delete[] this->_p;
    }

    ValueOr<Type, Error> 
    operator[](const usize&& n) noexcept {
        return this->at(std::move(n));
    }

    Type&
    front() {
        if(!this->is_empty())
            return this->_p[0];

        return this->_nullp;
    }

    Type&
    back() {
        if(!this->is_empty())
            return this->_p[0];

        return this->_nullp;
    }

    ValueOr<Type, Error>
    front_no_reference() noexcept {
        if(!this->is_empty())
            return Expected<Type>(this->at_without_check(0));

        return Unexpected<Error>(Error::Out_Of_Range);
    }

    ValueOr<Type, Error>
    back_no_reference() noexcept {
        if(!this->is_empty())
            return Expected<Type>(this->at_without_check(this->_size - 1));

        return Unexpected<Error>(Error::Out_Of_Range);
    }

    Type
    at_without_check(const usize&& n) {
        return this->_p[n];
    }

    Type*
    begin() {
        return this->_p;
    }

    Type*
    end() {
        if(this->is_empty())
            return this->_p;
        
        return this->_p + (this->_size);
    }

    ValueOr<Type, Error>
    at(const usize&& n) noexcept {
        if(n < this->_size)
            return Expected<Type>(this->at_without_check(std::move(n)));

        return Unexpected<Error>(Error::Out_Of_Range);
    }

    [[nodiscard]]
    bool 
    is_empty() const noexcept {
        return this->_size == 0;
    }

    void 
    push_back(Type&& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant);
        this->_p[this->_size++] = std::move(val);
    }

    void 
    push_back(Type const& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant);
        this->_p[this->_size++] = val;
    }

    void 
    push_front(Type const& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant);
        ++this->_size;
        this->_p[0] = val;        
    }

    void 
    pop_back() noexcept {
        if(this->is_empty())
            return;

        --this->_size; // better than reallocating and copying everything imo,
                       // when push_back() used later, current element will be overwritten.
    }

    void
    reserve_if_needed(usize&& val) noexcept {
        if(this->is_empty() || (this->_capacity == this->_size)) {
            this->reserve(std::move(val));
        }
    }

    void 
    reserve_if_needed_with_given_value(usize&& val, Type& value) noexcept {
        if(this->is_empty() || (this->_capacity == this->_size)) {
            this->reserve_with_given_value(std::move(val), value);
        }
    }

    void 
    reserve(usize&& val) noexcept {
        Type* temp = new Type[val];

        for(usize n = 0; (n < val) && (n < this->_size); ++n)
            temp[n] = this->_p[n];

        if(!this->is_empty())
            delete[] this->_p;

        this->_capacity = val;
        this->_p = temp;
    }

    void 
    reserve_with_given_value(usize&& val, Type& value) noexcept {
        Type* temp = new Type[val];

        for(usize n = 0; n < val; ++n)
            temp[n] = value;

        if(!this->is_empty())
            delete[] this->_p;

        this->_capacity = val;
        this->_size = this->_capacity;
        this->_p = temp;
    }

    [[nodiscard]]
    usize 
    size() const noexcept {
        return this->_size;
    }

    [[nodiscard]]
    usize 
    capacity() const noexcept {
        return this->_capacity;
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, const Vec<Type>& arr) {
        ostr << '[';
        
        for(usize n = 0; n < arr.size(); ++n)
            if(n + 1 == arr.size())
                ostr << arr.data()[n]; // Val must overload operator<< if not known type
            else
                ostr << arr.data()[n] << ", ";

        ostr << ']';
        return ostr;
    }

    constexpr Type*
    data() const noexcept {
        return const_cast<Type*>(this->_p);
    }
private:
    static constexpr u16 _capacity_constant = 128;

    Type* _p;

    usize _capacity { _capacity_constant },
          _size { 0 }; 

    Type  _nullp;
};
} // namespace idk