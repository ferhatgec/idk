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
// there's no current support for Unix-like systems, so it's TODO.

#pragma once 

#include "../types/stringview.hpp"
#include "../types/predefined.hpp"
#include "../utilities/semantics.hpp"

#ifdef _windows
    using StandardType = wchar_t;
    using _StringView  = idk::StringView<wchar_t>;
#   define DotChar     L'.'
#   define DirSepChar  L'\\'
#   define EmptyStr    L""
#   define QuoteStr    L"\""
#   pragma comment(lib, "shlwapi.lib")
#   include <Shlwapi.h>
#else
    using StandardType = char;
    using _StringView  = idk::StringViewChar;
#   define DotChar     '.'
#   define DirSepChar  '/'
#   define EmptyStr    ""
#   define QuoteStr    "\""
#   include <unistd.h>
#   include <sys/stat.h>
#endif

namespace idk {
class Path {
    _StringView _path; // maybe using Vec<_StringView> in the future would be great idea. 
                       // but you'll need to convert it to _StringView every as_str() call, it's probably bad.; isn't it?
public:
    enum class Type {
        File,
        Directory,
        Symlink,
        NotFound
    };

    Path(const Path& path) : _path(path._path) {}
    Path(Path&& path) : _path(idk::move(path._path)) {}

    Path(const _StringView& path) : _path(path) {}
    Path(_StringView&& path) : _path(idk::move(path)) {}
    
    Path(const StandardType* path) : _path(path) {}

    Path() {
        this->_path = _StringView(EmptyStr);
    }
    
    ~Path() = default;

    void 
    clear() noexcept {
        this->_path.clear();
    }

    [[nodiscard]]
    bool 
    exists() const noexcept {
#ifdef _windows
    return PathFileExistsW(this->_path.data());
#else
    return access(this->_path.data(), F_OK) == 0;
#endif
    }

    [[nodiscard]]
    bool 
    is_empty() const noexcept {
        return this->_path.is_empty();
    }

    [[nodiscard]]
    bool 
    is_file() const noexcept {
        return this->as_type() == Type::File;
    }

    [[nodiscard]]
    bool
    is_symlink() const noexcept {
        return this->as_type() == Type::Symlink;
    }

    [[nodiscard]]
    bool 
    is_directory() const noexcept {
        return this->as_type() == Type::Directory;
    }

    [[nodiscard]]
    Type
    as_type() const noexcept {
        if(!this->exists())
            return Type::NotFound;
        
#ifdef _windows
    auto attr = GetFileAttributesW(this->_path.data());

    if((attr & FILE_ATTRIBUTE_NORMAL) 
        || (attr & FILE_ATTRIBUTE_READONLY) 
        || (attr & FILE_ATTRIBUTE_TEMPORARY) 
        || (attr & FILE_ATTRIBUTE_SPARSE_FILE)
        || (attr & FILE_ATTRIBUTE_OFFLINE))
        return Type::File;

    if(attr & FILE_ATTRIBUTE_REPARSE_POINT)
        return Type::Symlink;

    return Type::Directory;
#else
    struct stat _buffer;

    if(stat(this->_path.data(), &_buffer) != 0)
        return Type::NotFound;

    if(S_ISDIR(_buffer.st_mode))
        return Type::Directory;

    if(S_ISLNK(_buffer.st_mode))
        return Type::Symlink;

    return Type::File;
#endif
    }

    [[nodiscard]]
    Path 
    extension() noexcept {
        _StringView str;

        if(this->_path.is_empty())
            return Path(str);
        
        for(usize n = this->_path.length() - 1; n > 0; --n)
            if(this->_path[n].try_get_value() == DotChar) {
                str = this->_path.substr(n, this->_path.length() - n);
                break;
            }

        return Path(str);
    }

    [[nodiscard]]
    Path 
    file_name() noexcept {
        _StringView str;

        if(this->_path.is_empty())
            return Path(str);

        usize n = this->_path.length() - 1, 
              i = 0;

        for(; n > 0; --n)
            if(this->_path[n].try_get_value() != DirSepChar)
                ++i;
            else
                break;

        if(i == (this->_path.length() - 1))
            str = this->_path;
        else
            str = this->_path.substr(n + 1, i);

        return Path(str);
    }

    [[nodiscard]]
    usize 
    file_size() noexcept {
        if(this->_path.is_empty())
            return 0;

#ifdef _windows
    WIN32_FILE_ATTRIBUTE_DATA _file_info;

    if(GetFileAttributesExW(this->_path.data(), GetFileExInfoStandard, &_file_info))
        return (static_cast<usize>(_file_info.nFileSizeHigh) << 32) | _file_info.nFileSizeLow;

    return (usize)0;
#else
#endif
    }

    [[nodiscard]]
    Path 
    to_posix_path() noexcept {
        _StringView str = this->_path;
#ifdef _windows
        for(auto& ch: str)
            if(ch == DirSepChar)
                ch = L'/';
#else
        for(auto& ch: str)
            if(ch == DirSepChar)
                ch = '/';
#endif
        return Path(str);
    }

    [[nodiscard]]
    Path 
    to_win_path() noexcept {
        _StringView str = this->_path;
#ifdef _windows
        for(auto& ch: str)
            if(ch == DirSepChar)
                ch = L'\\';
#else
        for(auto& ch: str)
            if(ch == DirSepChar)
                ch = '\\';
#endif
        return Path(str);
    }

    [[nodiscard]]
    Path 
    to_inverse_path() noexcept {
#ifdef _windows
        return this->to_posix_path();
#else
        return this->to_win_path();
#endif
    }

    [[nodiscard]]
    Path
    remove_file_name() noexcept {
        _StringView str = this->_path;

        if(this->_path.is_empty())
            return Path(str);

        usize n = str.length() - 1;

        for(; n > 0; --n)
            if(str[n].try_get_value() == DirSepChar)
                break;

        if(n == 0)
            return Path(EmptyStr);
        
        str = str.substr(0, n + 1);

        return Path(str);
    }

    [[nodiscard]]
    Path
    remove_extension() noexcept {
        _StringView str;

        if(this->_path.is_empty())
            return Path(str);
        
        for(usize n = this->_path.length() - 1; n > 0; --n)
            if(this->_path[n].try_get_value() == DotChar) {
                str = this->_path.substr(0, n);
                break;
            }

        return Path(str);
    }

    [[nodiscard]]
    Path
    replace_file_name(const Path& str_path) noexcept {
        if(this->_path.is_empty())
            return Path(str_path);
        
        return Path(this->remove_file_name().as_str() + str_path.as_str());
    }

    [[nodiscard]]
    Path
    replace_file_name(Path&& str_path) noexcept {
        return this->replace_file_name(str_path);
    }

    [[nodiscard]]
    Path
    replace_extension(const Path& str_ext) noexcept {
        if(this->_path.is_empty())
            return Path(str_ext);
        
        return Path(this->remove_extension().as_str() + str_ext.as_str());
    }

    [[nodiscard]]
    Path
    replace_extension(Path&& str_ext) noexcept {
        return this->replace_extension(str_ext);
    }

    // TODO: fully windows support.
    [[nodiscard]]
    Path
    append(const Path& str_path) noexcept {
        _StringView str = this->_path;

        if(str.is_empty())
            str = str_path.as_str();
        else if(str_path.is_empty()) { // "x" + "" = "x/"
#ifndef _windows 
    if(!str.ends_with('/'))
        str = str + "/";
#endif
        }
#ifndef _windows
        else if(str_path.as_str().starts_with('/')) { // "x/y" + "/z" = "/z" 
            str = str_path.as_str();
        }
#endif
        else {
#ifdef _windows
#else // "/x/" + "y" = "/x/y/"
    if(!str.ends_with('/'))
        str = str + "/";

    str = str + str_path.as_str();

    if(!str.ends_with('/'))
        str = str + "/";
#endif
        }

        return Path(str);
    }

    [[nodiscard]]
    Path
    append(Path&& str_path) noexcept {
        return this->append(str_path);
    }

    Path&
    operator/=(const Path& str_path) noexcept {
        this->_path = this->append(str_path)._path;
        return *this;
    }

    Path&
    operator/=(Path&& str_path) noexcept {
        this->_path = this->append(str_path)._path;
        return *this;
    }

#ifndef _windows
    friend std::ostream&
    operator<<(std::ostream& ostr, const Path& path) {
        ostr << QuoteStr << path.as_str() << QuoteStr;
        return ostr;
    }

    friend std::ostream&
    operator<<(std::ostream& ostr, const Path&& path) {
        return operator<<(ostr, path);
    }
#endif

    friend std::wostream&
    operator<<(std::wostream& ostr, const Path& path) noexcept {
        ostr << QuoteStr << path.as_str() << QuoteStr;
        return ostr;
    }

    friend std::wostream&
    operator<<(std::wostream& ostr, const Path&& path) noexcept {
        return operator<<(ostr, path);
    }

    friend bool
    operator==(const Path& left, const Path& right) noexcept {
        return left._path == right._path;
    }

    friend bool
    operator!=(const Path& left, const Path& right) noexcept {
        return !operator==(left, right);
    }

    [[nodiscard]]
    _StringView
    as_str() const noexcept {
        return this->_path;
    }
};
} // namespace idk