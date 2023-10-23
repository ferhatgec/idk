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
#include "../types/stringview.hpp"

namespace idk {
class SourceLocation {
    idk::u64 _line, 
             _column;
    idk::StringViewChar _file_name,
                        _function_name;
public:
    SourceLocation(idk::u64 line, 
                   idk::u64 column,
                   idk::StringViewChar file_name,
                   idk::StringViewChar function_name) 
                   : _line(line),
                     _column(column),
                     _file_name(file_name),
                     _function_name(function_name) {}
        
    SourceLocation(const SourceLocation& location) : 
            _line(location.line()),
            _column(location.column()),
            _file_name(location.file_name()),
            _function_name(location.function_name()) {};
        

    __idk_nodiscard
    static idk::SourceLocation 
    current(
        const idk::u64 line = __builtin_LINE(),
#ifdef __clang__
        const idk::u64 column = __builtin_COLUMN(),
#else
        const idk::u64 column = 0,
#endif
        const idk::StringViewChar file_name = idk::StringViewChar(__builtin_FILE()),
        const idk::StringViewChar function_name = idk::StringViewChar(__builtin_FUNCTION())) 
    noexcept {
        return idk::SourceLocation(line, column, file_name, function_name);
    }

    __idk_nodiscard
    idk::StringViewChar 
    file_name() const noexcept {
        return this->_file_name;
    }

    __idk_nodiscard
    idk::StringViewChar 
    function_name() const noexcept {
        return this->_function_name;
    }

    __idk_nodiscard
    __idk_constexpr idk::u64 
    line() const noexcept {
        return this->_line;
    }

    __idk_nodiscard
    __idk_constexpr idk::u64 
    column() const noexcept {
        return this->_column;
    }
};
} // namespace idk