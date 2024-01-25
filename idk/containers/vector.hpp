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

#include "../types/predefined.hpp"
#include "../types/valueor.hpp"
#include "../utilities/type_traits.hpp"
#include "../utilities/semantics.hpp"
#include <iostream>

// FIXME: do not allocate memory every assign, which is bad.
// just overwrite if current capacity is enough to hold them.
// if not, then allocate.

namespace idk {
template<typename Type>
class Vector {
public:
    enum class Error {
        Out_Of_Range,
    };

    Vector(Type*& val) : _p(val) {
        if(val != nullptr) {
            this->_capacity = val->capacity;
            this->_size = val->size;
        } else
            this->_capacity = this->_size = 0;
    }

    Vector(Vector<Type>& val) : _size(val._size), _capacity(val._capacity) {
        if(!this->is_empty())
            delete[] this->_p;

        this->_p        = new Type[val._capacity];

        for(usize n = 0; n < val._size; ++n)
            this->_p[n] = val._p[n];
    }
    
    Vector(Vector<Type>&& val) : _size(idk::move(val._size)), _capacity(idk::move(val._capacity)) {
        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p        = new Type[val._capacity];

        for(usize n = 0; n < val._size; ++n)
            this->_p[n] = idk::move(val._p[n]);
    }
    
    Vector(const usize& n) {
        if(!this->is_empty())
            delete[] this->_p;
        
        if(n > this->_capacity) {
            this->_capacity = n;
            this->_size     = n;
        } else {
            this->_size     = n;
        }

        this->_p = new Type[this->_size];
    }

    Vector(usize&& n, Type&& val) {
        this->reserve_if_needed_with_given_value(idk::move(n), val);
    }

    Vector(usize&& n, Type& val) {
        this->reserve_if_needed_with_given_value(idk::move(n), val);
    }

    Vector(usize&& n, Type const& val) {
        this->reserve_if_needed_with_given_value(idk::move(n), const_cast<Type&>(val));
    }

    Vector(std::initializer_list<Type> vals) {
        for(const Type& val: vals)
            this->push_back(val);
    }

    Vector() {
        this->_p        = nullptr;
        this->_capacity = this->_size = 0;
    }

    ~Vector() {
        if(!this->is_empty())
            delete[] this->_p;
    }

    ValueOr<Type, Error> 
    operator[](usize&& n) noexcept {
        return this->at(idk::move(n));
    }

    ValueOr<Type, Error> 
    operator[](usize& n) noexcept {
        return this->at(n);
    }

    Vector<Type>&
    operator=(const Vector<Type>& other) noexcept {
        if(&other == this)
            return *this;

        if(!this->is_empty())
            delete[] this->_p;

        this->_p        = new Type[other._capacity];
        
        for(usize n = 0; n < other._size; ++n)
            this->_p[n] = other._p[n];

        this->_size     = other._size;
        this->_capacity = other._capacity;

        return *this;
    }

    Vector<Type>&
    operator=(Vector<Type>&& other) noexcept {
        if(&other == this)
            return *this;

        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p        = new Type[other._capacity];
        
        for(usize n = 0; n < other._size; ++n)
            this->_p[n] = idk::move(other._p[n]);

        this->_size     = idk::move(other._size);
        this->_capacity = idk::move(other._capacity);

        return *this;
    }

    template<typename _Type2>
    friend bool 
    operator==(const Vector<Type>& left, const Vector<_Type2>& right) noexcept {
        if(!idk::IsSameVal<Type, _Type2> || left.size() != right.size())
            return false;
        
        for(usize n = 0; n < left.size(); ++n)
            if(left._p[n] != right._p[n])
                return false;

        return true;
    }

    template<typename _Type2>
    friend bool 
    operator==(const Vector<Type>& left, const _Type2* right) noexcept {
        if(!right)
            return false;
        
        if(!idk::IsSameVal<Type, _Type2> || left.size() != (sizeof(right) / sizeof(right[0])))
            return false;
        
        for(usize n = 0; n < left.size(); ++n)
            if(left._p[n] != right._p[n])
                return false;

        return true;
    }

    template<typename _Type2>
    friend bool 
    operator!=(const Vector<Type>& left, const Vector<_Type2>& right) noexcept {
        return !operator==(left, right);
    }

    template<typename _Type2>
    friend bool 
    operator!=(const Vector<Type>& left, const _Type2* right) noexcept {
        return !operator==(left, right);
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
            return this->_p[this->_size - 1];

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
    at_without_check(usize&& n) {
        return this->_p[n];
    }
    
    Type
    at_without_check(const usize& n) {
        return this->_p[n];
    }

    Type&
    at_without_check_reference(usize&& n) {
        return this->_p[n];
    }

    Type&
    at_without_check_reference(const usize& n) {
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
    at(usize&& n) noexcept {
        return this->at(n);
    }

    ValueOr<Type, Error>
    at(usize& n) noexcept {
        if(n < this->_size)
            return Expected<Type>(this->at_without_check(idk::move(n)));

        return Unexpected<Error>(Error::Out_Of_Range);
    }

    __idk_nodiscard
    bool 
    is_empty() const noexcept {
        return this->_size == 0;
    }

    void 
    push_back(Type&& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant + 1);
        this->_p[this->_size++] = idk::move(val);
    }

    void 
    push_back(const Type& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant + 1);
        this->_p[this->_size++] = val;
    }

    void 
    push_back(Vector<Type>&& val) noexcept {
        this->reserve_if_needed(this->_size + val._size + 1);

        for(Type& elem: idk::move(val))
            this->_p[this->_size++] = idk::move(elem);
    }

    void 
    push_back(const Vector<Type>& val) noexcept {
        this->reserve_if_needed(this->_size + _capacity_constant + val._size + 1);

        for(Type& elem: const_cast<Vector<Type>&>(val))
            this->_p[this->_size++] = elem;
    }

    void 
    push_front(const Type& val) noexcept {
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
            this->reserve(idk::move(val));
        }
    }

    void 
    reserve_if_needed_with_given_value(usize&& val, Type& value) noexcept {
        if(this->is_empty() || (this->_capacity == this->_size)) {
            this->reserve_with_given_value(idk::move(val), value);
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
        this->_p        = temp;
    }

    void 
    reserve_with_given_value(usize&& val, Type& value) noexcept {
        Type* temp = new Type[val];

        for(usize n = 0; n < val; ++n)
            temp[n] = value;

        if(!this->is_empty())
            delete[] this->_p;

        this->_capacity = val;
        this->_size    = this->_capacity;
        this->_p       = temp;
    }

    void 
    reserve_with_given_value(usize&& val, Type&& value) noexcept {
        reserve_with_given_value(idk::move(val), value);
    }

    __idk_nodiscard
    usize 
    size() const noexcept {
        return this->_size;
    }

    __idk_nodiscard
    usize 
    capacity() const noexcept {
        return this->_capacity;
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, const Vector<Type>& arr) {
        ostr << '[';
        
        for(usize n = 0; n < arr.size(); ++n)
            if(n + 1 == arr.size())
                ostr << arr.data()[n]; // Val must overload operator<< if not known type
            else
                ostr << arr.data()[n] << ", ";

        ostr << ']';
        return ostr;
    }

    __idk_constexpr Type*
    data() const noexcept {
        return const_cast<Type*>(this->_p);
    }

    __idk_nodiscard
    bool
    contains(Type& val) noexcept {
        for(auto& elem: *this)
            if(elem == val)
                return true;

        return false;
    }

    __idk_nodiscard
    bool
    contains(Type&& val) noexcept {
        return this->contains(val);
    }

    void
    clear() noexcept {
        while(!this->is_empty())
            this->pop_back();
    }

    __idk_nodiscard
    bool 
    change_val_at_index(const usize& index, const Type& replace) noexcept {
        if(this->is_empty() || index >= this->size())
            return false;

        usize i = 0;

        while(i != index) {
            ++i;
        }

        this->_p[i] = replace;
        
        return true;
    }

    __idk_nodiscard
    bool 
    change_val_at_index(usize&& index, Type&& replace) noexcept {
        if(this->is_empty() || index >= this->size())
            return false;

        usize i = 0;

        while(i != index) {
            ++i;
        }

        this->_p[i] = idk::move(replace);
        
        return true;
    }

    __idk_nodiscard
    isize
    find(const Type& val) noexcept {
        for(usize n = 0; n < this->_size; ++n)
            if(this->_p[n] == val)
                return n;

        return -1;
    }

    __idk_nodiscard
    isize
    find(Type&& val) noexcept {
        return this->find(val);
    }
private:
    static inline __idk_constexpr u16 _capacity_constant = 128;

    Type* _p;

    usize _capacity { _capacity_constant },
          _size { 0 }; 

    Type  _nullp;
};

template<typename Type>
using Vec = Vector<Type>;
} // namespace idk