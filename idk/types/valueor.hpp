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

#include <utility>

namespace idk {
template<typename _Type, typename _ValueOr>
class ValueOr;

template<typename _Type>
class Expected {
public:
    Expected(_Type&& value) : val(value) {
        this->has_val = true;
    }
    
    Expected(_Type& value) : val(value) {
        this->has_val = true;
    }
    
    Expected() = default;

    [[nodiscard]]
    bool 
    has_value() const noexcept {
        return this->has_val;
    }

    [[nodiscard]]
    _Type 
    get_value() noexcept {
        return this->val;
    }

    ~Expected() = default;
private:
    _Type val;
    bool has_val { false };
};

template<typename _ValueOr>
class Unexpected {
public:
    Unexpected(_ValueOr&& value_or) : val_or(value_or) {
        this->has_val_or = true;
    }

    Unexpected(_ValueOr& value_or) : val_or(value_or) {
        this->has_val_or = true;
    }

    Unexpected() = default;

    [[nodiscard]]
    bool 
    has_value() const noexcept {
        return this->has_value_or;
    }

    [[nodiscard]]
    _ValueOr 
    get_value() noexcept {
        return this->val_or;
    }

    void 
    change_with(_ValueOr& value_or) noexcept {
        this->val_or = value_or;
        if(!has_val_or) this->has_val_or = true;
    }
    
    ~Unexpected() = default;
private:
    _ValueOr val_or;
    bool has_val_or { false };
};

template<typename _Type, typename _ValueOr>
class ValueOr {
public:
    ValueOr(Expected<_Type>&& expected) : _expected(expected) {}
    ValueOr(Expected<_Type>& expected) : _expected(expected) {}
    ValueOr(Unexpected<_ValueOr>&& unexpected) : _unexpected(unexpected) {}
    ValueOr(Unexpected<_ValueOr>& unexpected) : _unexpected(unexpected) {}

    [[nodiscard]]
    _Type 
    value_or(_ValueOr&& unexpected) noexcept {
        if(this->_expected.has_value())
            return _expected.get_value();
        
        std::cerr << "unexpected\n";
        std::exit(1); // noreturn
        // this->_unexpected.change_with(std::move(unexpected));
        // return this->_unexpected;
    }

    [[nodiscard]]
    _Type 
    try_get_value() noexcept {
        if(this->_expected.has_value())
            return _expected.get_value();
        
        std::cerr << "unexpected\n";
        std::exit(1); // noreturn
        // this->_unexpected.change_with(std::move(unexpected));
        // return this->_unexpected;
    }

    [[nodiscard]]
    bool 
    has_value() const noexcept {
        return _expected.has_value();
    }
    
    Expected<_Type> _expected;
    Unexpected<_ValueOr> _unexpected;
};
} // namespace idk