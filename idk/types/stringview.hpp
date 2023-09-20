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

#include "predefined.hpp"
#include "valueor.hpp"
#include "../utilities/type_traits.hpp"
#include <utility>
#include <iostream>

namespace idk {
template<typename CharType>
class StringView {
public:
    enum class Error {
        Out_Of_Range,
        StringViewEmpty
    };
    
    StringView () : _len(0) {
        if constexpr(idk::IsSameVal<CharType, wchar_t>) {
            this->_p = (wchar_t*)L"";
        } else 
            this->_p = (char*)"";
    }
    
    ~StringView() = default;

    StringView(CharType* val) : _p(val) {
        this->length_string_view();
    }

    StringView(CharType ch) {
        CharType* val = new CharType[1];
        val[0] = ch;
        val[1] = '\0';
        this->_p = val;
        this->_len = 1;
    }

    StringView(const CharType* val) : _p(const_cast<CharType*>(val)) {
        this->length_string_view();
    }

    StringView(StringView const& val) {
        this->_p   = val._p;
        this->_len = val._len;   
    }

    StringView(const CharType* val, usize len)
        : _p(const_cast<CharType*>(val)), _len(len) {}

    // TODO: apply arithmetic value to idk::stringview 
    template<typename Num,
             typename = typename std::enable_if<std::is_arithmetic<Num>::value, Num>::type>
    StringView(Num const&& val) {
        
    }

    [[nodiscard]]
    constexpr usize 
    length() const noexcept {
        return this->_len;
    }

    [[nodiscard]]
    constexpr usize
    size() const noexcept {
        return this->_len;
    }

    void
    trim_spaces_left() noexcept {
        if(this->is_empty())
            return;

        while(!this->is_empty() && ::isspace(*this->_p)) {
            ++this->_p;
            --this->_len;
        }
    }

    void
    trim_spaces_right() noexcept {
        if(this->is_empty())
            return;

        for(usize n = this->_len - 1; n > 0; --n) {
            if(this->_p[n] == ' ')
                this->pop_back();
            else
                break;
        }
    }

    void
    trim_spaces() noexcept {
        if(this->is_empty())
            return;

        if(::isspace(this->front()))
            this->trim_spaces_left();

        if(this->is_empty() || !::isspace(this->back()))
            return;

        this->trim_spaces_right();
    }

    [[nodiscard]]
    constexpr bool 
    is_empty() const noexcept {
        return this->_len == 0;
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, StringView<CharType>&& val) noexcept {
        if(!val.is_empty())
            ostr << std::move(val._p);
        return ostr;
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, StringView<CharType>& val) noexcept {
        if(!val.is_empty())
            ostr << val._p;
        return ostr;
    }

    friend std::wostream& 
    operator<<(std::wostream& ostr, StringView<CharType>&& val) noexcept {
        if(!val.is_empty())
            ostr << std::move(val._p);
        return ostr;
    }

    friend std::wostream& 
    operator<<(std::wostream& ostr, StringView<CharType>& val) noexcept {
        if(!val.is_empty())
            ostr << val._p;
        return ostr;
    }
    
    StringView<CharType>& 
    operator=(const StringView<CharType>& other) noexcept {
        if(&other == this)
            return *this;

        this->_p  = other._p;
        this->_len = other._len;

        return *this;
    }

    StringView<CharType>& 
    operator=(StringView<CharType>&& other) noexcept {
        if(other == *this)
            return *this;

        this->_p   = std::move(other._p);
        this->_len = std::move(other._len);
        
        return *this;    
    }

    StringView<CharType>&
    operator=(CharType* other) noexcept {
        if(other == this->_p)
            return *this;

        this->_p = other;
        this->length_string_view();
        return *this;    
    }

    template<typename _CharType2>
    friend bool 
    operator==(const StringView<CharType>& left, const StringView<_CharType2>& right) noexcept {
        if(!idk::IsSameVal<CharType, _CharType2> || left.length() != right.length())
            return false;
        
        if constexpr(idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<CharType>>>, wchar_t> 
                && idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<_CharType2>>>, wchar_t>) 
            return wcscmp(left._p, right._p) == 0; 
        else
            return std::strcmp(left._p, right._p) == 0;
    }

    template<typename _CharType2>
    friend bool 
    operator==(const StringView<CharType>& left, const _CharType2* right) noexcept {
        if(!idk::IsSameVal<CharType, _CharType2> || left.length() != length_char_p(const_cast<_CharType2*>(right)))
            return false;
        
        if constexpr(idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<CharType>>>, wchar_t> 
                && idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<_CharType2>>>, wchar_t>) 
            return wcscmp(left._p, right) == 0; 
        else
            return std::strcmp(left._p, right) == 0;
    }

    template<typename _CharType2>
    friend bool 
    operator!=(const StringView<CharType>& left, const StringView<_CharType2>& right) noexcept {
        return !operator==(left, right);
    }

    template<typename _CharType2>
    friend bool 
    operator!=(const StringView<CharType>& left, const _CharType2* right) noexcept {
        return !operator==(left, right);
    }

    friend 
    StringView<CharType>
    operator+(StringView<CharType> left, const StringView<CharType>& right) {
        if(right.is_empty())
            return left;
        
        const auto len = left.length() + right.length() + 1;
        CharType* val = new CharType[len];
        
        if constexpr(idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<CharType>>>, wchar_t>) {
            val[0] = L'\0';
            ::wcscat_s(val, len, left.data());
            ::wcscat_s(val, len, right.data());
        } else {
            val[0] = '\0';
            ::strcat_s(val, len, left.data());
            ::strcat_s(val, len, right.data());
        }
    
        return StringView<CharType>(val);     
    }

    friend 
    StringView<CharType>
    operator+(StringView<CharType> left, CharType* right) {
        return operator+(left, StringView<CharType>(right));  
    }

    CharType*
    begin() noexcept {
        return this->_p;
    }

    CharType*
    end() noexcept {
        if(this->is_empty())
            return this->_p;
        return this->_p + (this->_len);
    }
    
    ValueOr<CharType, Error>
    operator[](usize&& n) const noexcept {
        return this->at(std::move(n));
    }

    ValueOr<CharType, Error>
    operator[](const usize& n) const noexcept {
        return this->at(n);
    }

    ValueOr<CharType, Error>
    at(usize&& n) const noexcept {
        return this->at(n);
    }

    ValueOr<CharType, Error>
    at(const usize& n) const noexcept {
        if(n < this->length())
            return Expected(this->_p[n]);
        
        if(this->is_empty())
            return Unexpected(Error::StringViewEmpty);
        
        return Unexpected(Error::Out_Of_Range);
    }

    CharType
    at_without_check(const usize&& n) {
        return this->_p[n];
    }

    CharType
    at_without_check(const usize& n) {
        return this->_p[n];
    }

    CharType&
    front() noexcept {
        if(this->is_empty())
            return _empty_char;

        return this->_p[0];
    }

    CharType&
    back() noexcept {
        if(this->is_empty())
            return _empty_char;

        return this->_p[this->_len - 1];
    }

    ValueOr<CharType, Error>
    front_no_reference() noexcept {
        if(this->is_empty())
            return Unexpected<Error>(Error::StringViewEmpty);

        return Expected<CharType>(this->_p[0]);
    }

    ValueOr<CharType, Error>
    back_no_reference() noexcept {
        if(this->is_empty())
            return Unexpected<Error>(Error::StringViewEmpty);

        return Expected<CharType>(this->_p[this->_len - 1]);
    }

    constexpr CharType*
    data() const noexcept {
        return const_cast<CharType*>(this->_p);
    }

    constexpr usize
    copy_n(CharType* dest, usize pos = 0, usize count = 0) const {
        if(const auto val = this->_len;
            (pos + count) > val || this->is_empty())
            return 0;
        else
            if constexpr(idk::IsSameVal<typename std::decay_t<typename std::remove_pointer_t<typename std::remove_const_t<CharType>>>, wchar_t>)
                ::wcsncpy_s(dest, count + 1, this->_p + pos, count);
            else
                ::strncpy_s(dest, count + 1, this->_p + pos, count);

        return count;
    }

    StringView<CharType>
    substr(usize pos = 0, usize count = 0) const {
        StringView<CharType> copy;
        if(this->is_empty())
            return copy;

        CharType* temp = new CharType[count + 1]; // [count + 1];
        
        this->copy_n(temp, pos, count);
        copy.operator=(temp);
        copy._len = copy.length_char_p(copy._p);
        
        return copy;
    }

    constexpr bool
    starts_with(CharType ch) noexcept {
        if(this->is_empty())
            return static_cast<u16>(ch) == 0;

        return this->front() == ch; 
    }

    constexpr bool
    starts_with(CharType* val) noexcept {
        if(this->is_empty())
            return this->length_char_p(val) == 0;

        const auto len = this->length_char_p(val);
        
        for(usize n = 0; n < len; ++n)
            if(this->_p[n] != val[n])
                return false;

        return true;
    }

    constexpr bool
    ends_with(CharType ch) noexcept {
        if(this->is_empty())
            return static_cast<u16>(ch) == 0;

        return this->back() == ch; 
    }

    constexpr bool
    ends_with(CharType* val) noexcept {
        if(this->is_empty())
            return this->length_char_p(val) == 0;

        const auto len = this->_len - this->length_char_p(val);
        
        for(usize n = this->_len; n > len; --n)
            if(this->_p[n] != val[n])
                return false;

        return true;
    }

    constexpr bool
    contains(CharType ch) noexcept {
        if(this->is_empty())
            return static_cast<u16>(ch) == 0;

        for(CharType& _ch: *this)
            if(ch == _ch)
                return true;

        return false;
    }

    constexpr bool
    contains(CharType* val) noexcept {
        if(this->is_empty())
            return this->length_char_p(val) == 0;

        return strstr(this->_p, val) != NULL;
    }

    constexpr void 
    clear() noexcept {
        if(!this->is_empty())
            *this = StringView<CharType>();
    }

    void
    push_back(const CharType& ch) noexcept {
        *this = *this + StringView<CharType>(ch);
    }

    void
    push_back(CharType&& ch) noexcept {
        this->push_back(ch);
    }

    void
    push_front(const CharType& ch) noexcept {
        *this = StringView<CharType>(ch) + *this;
    }

    void
    push_front(CharType&& ch) noexcept {
        this->push_front(ch);
    }

    void
    pop_back() noexcept {
        if(!this->is_empty()) {
            CharType* val = new CharType[--this->_len];
            
            for(usize n = 0; n < this->_len; ++n)
                val[n] = this->_p[n];
                
            val[this->_len] = '\0';
            std::swap(val, this->_p);
        }
    }
private:
    void
    length_string_view() noexcept {
        for(this->_len = 0; this->_p[this->_len]; ++this->_len)
            ;
    }

    [[nodiscard]]
    static usize 
    length_char_p(CharType* p) noexcept { // same as strlen() with noexcept specifier.
        if(p == nullptr)
            return 0;
            
        usize len { 0 };

        for(len = 0; p[len]; ++len)
            ;

        return len;
    }
    
    CharType* _p        ;
    usize    _len { 0 } ;
    CharType _empty_char;
};

using StringViewChar = StringView<char>;
} // namespace idk

