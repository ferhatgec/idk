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

#ifndef _windows
#   include <cstring>
#   include <cwchar>
#endif

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
        this->_p = new CharType[1];

        if constexpr(idk::IsSameVal<CharType, wchar_t>) {
            this->_p[0] = L'\0';
        } else 
            this->_p[0] = '\0';
    }
    
    ~StringView() {
        if(!this->is_empty())
            delete[] this->_p;
    }

    StringView(CharType* val) {
        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p   = new CharType[this->length_char_p(val) + 1];
        this->_len = this->length_char_p(val);

        for(usize n = 0; n < this->_len; ++n)
            this->_p[n] = val[n];

        this->_p[this->_len] = '\0';
    }

    StringView(CharType ch) {
        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p = new CharType[2];
        
        this->_p[0] = ch;
        this->_p[1] = '\0';

        this->_len = 1;
    }

    StringView(const CharType* val) {
        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p   = new CharType[this->length_char_p(const_cast<CharType*>(val)) + 1];
        this->_len = this->length_char_p(const_cast<CharType*>(val));

        for(usize n = 0; n < this->_len; ++n)
            this->_p[n] = val[n];

        this->_p[this->_len] = '\0';
    }

    StringView(StringView const& val) {
        if(!this->is_empty())
            delete[] this->_p;
        
        this->_p   = new CharType[val._len + 1];
        this->_len = val._len;

        for(usize n = 0; n < val._len; ++n)
            this->_p[n] = val._p[n];

        this->_p[this->_len] = '\0';
    }

/*
    StringView(const CharType* val, usize len) {
        if(!this->is_empty())
            delete[] this->_p;

        this->_p   = const_cast<CharType*>(val);
        this->_len = len;
    }
*/

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

        usize n = 0;

        for(n = 0; n < this->_len; ++n)
            if(!::isspace(this->_p[n]))
                break;
            
        CharType* _val = new CharType[this->_len - n + 1];

        for(usize j = 0; j < this->_len - n; ++j)
            _val[j] = this->_p[n + j];
        
        _val[this->_len - n] = '\0';

        delete[] this->_p;

        this->_p   = _val;
        this->_len = this->_len - n;
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

        if(!this->is_empty())
            delete[] this->_p;

        this->_p = new CharType[other._len + 1];

        for(usize n = 0; n < other._len; ++n)
            this->_p[n] = other._p[n];

        this->_len = other._len;

        this->_p[this->_len] = '\0';

        return *this;
    }

    StringView<CharType>& 
    operator=(StringView<CharType>&& other) noexcept {
        if(other == *this)
            return *this;

        if(!this->is_empty())
            delete[] this->_p;

        this->_p = new CharType[other._len + 1];

        for(usize n = 0; n < other._len; ++n)
            this->_p[n] = std::move(other._p[n]);

        this->_len = std::move(other._len);
        this->_p[this->_len] = '\0';

        return *this;    
    }

    StringView<CharType>&
    operator=(CharType* other) noexcept {
        if(other == this->_p)
            return *this;
        
        if(!this->is_empty())
            delete[] this->_p;

        this->_p = new CharType[this->length_char_p(other) + 1];

        for(usize n = 0; n < this->length_char_p(other); ++n)
            this->_p[n] = other[n];

        this->_len = this->length_char_p(other);
        this->_p[this->_len] = '\0';

        return *this;    
    }

    template<typename _CharType2>
    friend bool 
    operator==(const StringView<CharType>& left, const StringView<_CharType2>& right) noexcept {
        if(!idk::IsSameVal<CharType, _CharType2> || left.length() != right.length())
            return false;
        
        for(usize n = 0; n < left.length(); ++n)
            if(left._p[n] != right._p[n])
                return false;

        return true;
    }

    template<typename _CharType2>
    friend bool 
    operator==(const StringView<CharType>& left, const _CharType2* right) noexcept {
        if(!idk::IsSameVal<CharType, _CharType2> || left.length() != length_char_p(const_cast<_CharType2*>(right)))
            return false;
        
        for(usize n = 0; n < left.length(); ++n)
            if(left._p[n] != right[n])
                return false;

        return true;
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
        
        usize n;

        for(n = 0; n < left.length(); ++n)
            val[n] = left._p[n];


        for(n = 0; n < right.length(); ++n)
            val[left.length() + n] = right._p[n];

        val[len - 1] = '\0';
        
        StringView<CharType> _val(val);


        delete[] val;

        return _val;
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

    constexpr isize
    copy_n(CharType* dest, usize pos = 0, usize count = 0) const {
        if(const auto val = this->_len;
            (pos + count) > val || this->is_empty())
            return -1;
        else {
            for(usize n = 0; n < count; ++n)
                dest[n] = this->_p[pos + n];

            dest[count] = '\0';
        }

        return count;
    }

    StringView<CharType>
    substr(usize pos = 0, usize count = 0) const {
        if(this->is_empty())
            return StringView<CharType>();

        CharType* temp = new CharType[count + 1];
        
        this->copy_n(temp, pos, count);
        
        StringView<CharType> _val(temp);
    
        delete[] temp;

        return _val;
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

        const auto len = this->_len - this->length_char_p(val) - 1;
        
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
            this->_p[--this->_len] = '\0';
        }
    }

    [[nodiscard]]
    isize
    find(const CharType& ch, usize from = 0) noexcept {
        for(usize n = from; n < this->_len; ++n)
            if(this->_p[n] == ch)
                return n;

        return -1;
    }

    [[nodiscard]]
    isize
    find(CharType&& ch, usize from = 0) noexcept {
        return this->find(ch, from);
    }

    [[nodiscard]]
    isize
    find(StringView<CharType>& str, usize from = 0) noexcept {
        if(str._len < 10 && this->_len < 100) { 
            // constants may be changed later with more efficient ones(?).
            // naive algorithm used in there. 
            for(usize i = from; i <= this->_len - str._len; ++i) {
                usize j;

                for(j = 0; j < str._len; ++j)
                    if(this->_p[i + j] != str[j].try_get_value())
                        break;
                
                if(j == str._len)
                    return i;
            }
        } else
            return this->str_kmp(str, from);

        return -1;
    }

    [[nodiscard]]
    isize
    find(StringView<CharType>&& str) noexcept {
        return this->find(str);
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

    void
    str_lps(StringView<CharType>& pattern, usize* lps_arr) noexcept {
        usize len { 0 };

        lps_arr[0] = 0;

        usize i = 1;

        while(i < pattern._len) {
            if(pattern._p[i] == pattern._p[len]) {
                ++len;
                lps_arr[i] = len;
                ++i;
                
                continue;
            }

            if(len != 0)
                len = lps_arr[len - 1];
            else {
                lps_arr[i] = 0;
                ++i;
            }
        }
    } 
    
    [[nodiscard]]
    isize
    str_kmp(StringView<CharType>& pattern, usize index = 0) noexcept {
        usize lps_arr[pattern._len];

        str_lps(pattern, lps_arr);

        usize i { 0 },
              j { 0 };

        while(i < this->_len) {
            if(pattern._p[j] == this->_p[i]) {
                ++i;
                ++j;
            }

            if(j == pattern._len) {
                if(index > (i - j)) {
                    j = lps_arr[j - 1];
                } else {
                    return i - j;
                }
            }

            if(i < this->_len && pattern._p[j] != this->_p[i]) {
                if(j != 0) {
                    j = lps_arr[j - 1];
                } else {
                    ++i;
                }
            }
        }

        return -1;
    }

    CharType* _p        ;
    usize    _len { 0 } ;
    CharType _empty_char;
};

using StringViewChar = StringView<char>;
} // namespace idk

