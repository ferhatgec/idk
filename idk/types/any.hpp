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

#include "valueor.hpp"
#include <typeinfo>

namespace idk {
class Any {
public:
    enum class Error {
        BadCast
    };

    Any() noexcept : _data(nullptr), _type_info(nullptr) {}
    
    template<typename Type>
    Any(const Type& val) noexcept : _data(new holder<Type>(val)), _type_info(&typeid(Type)) {}
    
    Any(const Any& val) noexcept : _type_info(val._type_info) {
        if(val._data)
            this->_data = val._data->clone();
        else 
            this->_data = nullptr;
    }

    Any(Any&& val) noexcept : _data(std::move(val._data)), _type_info(val._type_info) {
        val._data      = nullptr;
        val._type_info = nullptr;
    }

    ~Any() {
        delete this->_data;
    }
    
    template<typename Type>
    Any& operator=(Type&& other) noexcept {
        if(this == &other)
            return *this;
        
        delete this->_data;
        
        this->_data      = std::move(other._data);
        this->_type_info = other._type_info;
        other._data = nullptr;
        other._type_info = nullptr;
        
        return *this;
    }

    template<typename Type>
    Any& 
    operator=(const Type& other) noexcept {
        if(this == &other)
            return *this;
        
        delete this->_data;
        
        this->_data      = new holder<Type>(other);
        this->_type_info = &typeid(Type);
        
        return *this;
    }

    [[nodiscard]]
    bool 
    operator==(const Any& right) const noexcept {
        return (this->_data == right._data) && (this->_type_info == right._type_info);
    }
    
    [[nodiscard]]
    bool 
    is_empty() const noexcept {
        return this->_data == nullptr;
    }

    void
    reset() noexcept {
        delete this->_data;
        
        this->_data      = nullptr;
        this->_type_info = nullptr;
    }

    [[nodiscard]]
    const std::type_info&
    get_type() const noexcept {
        return *this->_type_info;
    }

    template<typename Type>
    idk::ValueOr<Type, Error> 
    cast_to() {
        if(this->is_empty() || *this->_type_info != typeid(Type))
            return Unexpected<Error>(Error::BadCast);

        return Expected<Type>(static_cast<holder<Type>*>(this->_data)->_val);
    }
private:
    class holder_base {
public:
        virtual
        ~holder_base() = default;

        virtual
        holder_base* clone() const = 0;
    };

    template<typename Type>
    class holder : public holder_base {
public:
        holder(const Type& val) : _val(val) {}
        
        holder_base* 
        clone() const noexcept override {
            return new holder<Type>(this->_val);
        }

        Type _val;
    };

    holder_base* _data;
    const std::type_info* _type_info;
};
} // namespace idk