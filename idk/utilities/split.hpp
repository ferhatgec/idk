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

#include "../containers/vector.hpp"
#include "../types/stringview.hpp"

#define Str StringView<CharType>

namespace idk {
template<typename CharType>
Vec<Str>
split(Str& str, char delim = ' ') noexcept {
    if(str.is_empty())
        return {};
    
    Vec<Str> vec;
    Str temp;

    for(char& ch: str) {
        if(ch != delim)
            temp = temp + Str(ch);
        else {
            vec.push_back(temp);
            temp.clear();
        }
    }

    if(!temp.is_empty())
        vec.push_back(temp);
    
    return vec;
}

template<typename CharType>
Vec<Str>
split(Str& str, Vec<CharType> delims) noexcept {
    if(delims.is_empty() || str.is_empty())
        return { str };
    
    Vec<Str> vec;
    Str temp;

    for(char& ch: str) {
        if(delims.contains(ch))
            temp = temp + Str(ch);
        else {
            vec.push_back(temp);
            temp.clear();
        }
    }

    if(!temp.is_empty())
        vec.push_back(temp);
    
    return vec;
}

template<typename CharType>
Vec<Str>
split(Str& str, Str delim) noexcept {
    if(str.is_empty() || delim.is_empty())
        return { str };
    
    Vec<Str> vec;
    Str temp;
    
    usize start { 0 }, 
          end   { 0 }, 
          len   { delim.length() };

    while((end = str.find(delim, start)) != -1) {
        temp  = str.substr(start, end - start);
        start = end + len;
        vec.push_back(temp);
    }
    
    vec.push_back(str.substr(start, str.length() - start));

    return vec;
}

template<typename Value>
Vec<Value>
split(Vec<Value>& val, Value delim) noexcept {
    Vec<Value> vec;

    for(auto& _val: val)
        if(_val != delim)
            vec.push_back(_val);

    return vec;
}

template<typename Value>
Vec<Value>
split(Vec<Value>& val, Vec<Value> delim) noexcept {
    Vec<Value> vec;

    for(auto& _val: val)
        if(!delim.contains(_val))
            vec.push_back(_val);

    return vec;
}
} // namespace idk

#undef Str