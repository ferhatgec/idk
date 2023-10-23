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
#include <cstdlib>

namespace idk {
enum Prerelease : const u16 {
    Alpha = 0,
    Beta  = 1,
    Rc    = 2,
    None  = 3
};

class Version {
public:
    usize _major { 1 },
          _minor { 0 },
          _patch { 0 };
    
    Prerelease _tag { Prerelease::None };
    
    usize      _prerelease_patch { 0 };

    Version(u16 major, u16 minor, u16 patch, Prerelease tag = Prerelease::None, u16 prerelease_patch = 0) 
        : _major(major), 
          _minor(minor),
          _patch(patch),
          _tag(tag),
          _prerelease_patch(prerelease_patch) {}

    Version () = default;
    ~Version() = default;
    
    void
    set_major(u16 major = 1) noexcept {
        this->_major = major;
    }

    void
    set_minor(u16 minor = 0) noexcept {
        this->_minor = minor;
    }

    void
    set_patch(u16 patch = 0) noexcept {
        this->_patch = patch;
    }

    void
    set_tag(Prerelease tag = Prerelease::None) noexcept {
        this->_tag = tag;
    }

    void
    set_prerelease_patch(u16 prerelease_patch = 0) noexcept {
        this->_prerelease_patch = prerelease_patch;
    }

    __idk_nodiscard
    u16
    major() const noexcept {
        return this->_major;
    }

    __idk_nodiscard
    u16
    minor() const noexcept {
        return this->_minor;
    }

    __idk_nodiscard
    u16
    patch() const noexcept {
        return this->_patch;
    }

    __idk_nodiscard
    Prerelease
    tag() const noexcept {
        return this->_tag;
    }

    __idk_nodiscard
    u16
    prerelease_patch() const noexcept {
        return this->_prerelease_patch;
    }

    __idk_nodiscard
    StringViewChar
    major_as_str() noexcept {
        return this->usize_to_str(this->_major);
    }

    __idk_nodiscard
    StringViewChar
    minor_as_str() noexcept {
        return this->usize_to_str(this->_minor);
    }

    __idk_nodiscard
    StringViewChar
    patch_as_str() noexcept {
        return this->usize_to_str(this->_patch);
    }

    __idk_nodiscard
    StringViewChar
    tag_as_str() noexcept {
        switch(this->_tag) {
            case Prerelease::Alpha: return "alpha";
            case Prerelease::Beta : return "beta";
            case Prerelease::Rc   : return "rc";
            default: return ""; 
        }
    }

    __idk_nodiscard
    StringViewChar
    prerelease_patch_as_str() noexcept {
        return this->usize_to_str(this->_prerelease_patch);
    }

    __idk_nodiscard
    StringViewChar
    as_str() const noexcept {
        StringViewChar str;

        usize_as_str(this->_major, str);
        str.push_back('.');
        usize_as_str(this->_minor, str);
        str.push_back('.');
        usize_as_str(this->_patch, str);
        
        if(this->_tag != Prerelease::None) {
            str.push_back('-');
            
            switch(this->_tag) {
                case Prerelease::Alpha: {
                    str = str + "alpha";
                    break;
                }

                case Prerelease::Beta: {
                    str = str + "beta";
                    break;
                }

                case Prerelease::Rc: {
                    str = str + "rc";
                    break;
                }

                default: break;
            }

            str.push_back('.');
            
            usize_as_str(this->_prerelease_patch, str);
        }

        return str;
    }

    StringViewChar
    build(const StringViewChar& pattern) noexcept {
        StringViewChar str;
        
        {
            StringViewChar temp;
            bool end = false;

            auto val = [&](unsigned char ch) {
                if(temp.is_empty()) {
                    str.push_back(ch);
                    return;
                }

                if(temp == "major")
                    usize_as_str(this->_major, str);
                else if(temp == "minor")
                    usize_as_str(this->_minor, str);
                else if(temp == "patch")
                    usize_as_str(this->_patch, str);
                else if(temp == "tag") {
                    switch(this->_tag) {
                        case Prerelease::Alpha: {
                            str = str + "alpha";
                            break;
                        }

                        case Prerelease::Beta: {
                            str = str + "beta";
                            break;
                        }

                        case Prerelease::Rc: {
                            str = str + "rc";
                            break;
                        }

                        default: break;
                    }
                } else if(temp == "prerelease_patch")
                    usize_as_str(this->_prerelease_patch, str);

                temp.clear();
                str.push_back(ch);
            };
            
            
            for(auto& ch: const_cast<StringViewChar&>(pattern))
                if(::ispunct(ch))
                    val(ch);
                else 
                    temp.push_back(ch);

            val(static_cast<unsigned char>(0));
        }

        return str;
    }

    StringViewChar
    build(StringViewChar&& pattern) noexcept {
        return this->build(pattern);
    }

    friend bool
    operator>(const Version& left, const Version& right) noexcept {
        if(left._major > right._major)
            return true;
        else if(left._major < right._major)
            return false;
        
        if(left._minor > right._minor)
            return true;
        else if(left._minor < right._minor)
            return false;

        if(left._patch > right._patch)
            return true;
        else if(left._patch < right._patch)
            return false;

        if(left._tag > right._tag)
            return true;
        else if(left._tag < right._tag)
            return false;

        if(left._prerelease_patch > right._prerelease_patch)
            return true;
        else if(left._prerelease_patch < right._prerelease_patch)
            return false;

        return false; // left = right
    }

    friend bool
    operator<(const Version& left, const Version& right) noexcept {
        return (left == right) ? false 
                               : !operator>(left, right);
    }

    friend bool
    operator>=(const Version& left, const Version& right) noexcept {
        return (left == right) || operator>(left, right);
    }

    friend bool
    operator<=(const Version& left, const Version& right) noexcept {
        return (left == right) || operator<(left, right);
    }

    friend bool
    operator==(const Version& left, const Version& right) noexcept {
        return ((left._major            == right._major) &&
                (left._minor            == right._minor) &&
                (left._patch            == right._patch) &&
                (left._tag              == right._tag  ) &&
                (left._prerelease_patch == right._prerelease_patch)); 
    }

    friend bool
    operator!=(const Version& left, const Version& right) noexcept {
        return !operator==(left, right);
    }
private:
    StringViewChar _str;

    static void
    usize_as_str(usize val, StringViewChar& str) noexcept {
        if(val >= 10)
            usize_as_str(val / 10, str);
         
        str.push_back('0' + (val % 10));
    }

    
    __idk_nodiscard
    StringViewChar
    usize_to_str(usize val) noexcept {
        _str.clear();
        usize_as_str(val, _str);

        return _str;
    }
};
} // namespace idk