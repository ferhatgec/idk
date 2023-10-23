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
#include "../utilities/semantics.hpp"
#include <iostream>

namespace idk {
class ColorBase {
public:
    enum StyleCodes: const u8 {
        Standard,
        Bold,
        Dim,
        Italic,
        Underline,
        Blink
    };

    enum ColorCodes: const u8 {
        FgBlack = StyleCodes::Blink + 1,
        FgRed,
        FgGreen,
        FgYellow,
        FgBlue,
        FgMagenta,
        FgCyan,
        FgWhite,
        FgBrightBlack,
        FgBrightRed,
        FgBrightGreen,
        FgBrightYellow,
        FgBrightBlue,
        FgBrightMagenta,
        FgBrightCyan,
        FgBrightWhite,
        FgDefault,

        BgBlack,
        BgRed,
        BgGreen,
        BgYellow,
        BgBlue,
        BgMagenta,
        BgCyan,
        BgWhite,
        BgBrightBlack,
        BgBrightRed,
        BgBrightGreen,
        BgBrightYellow,
        BgBrightBlue,
        BgBrightMagenta,
        BgBrightCyan,
        BgBrightWhite,
        BgDefault
    };

    static __idk_constexpr char const* _vals[40] {
        /* Standard */ "0", /* Bold */ "1", /* Dim */ "2", /* Italic */ "3", /* Underline */ "4", /* Blink */ "5",
        /* FgBlack */ "40", /* FgRed */ "41", /* FgGreen */ "42", /* FgYellow */ "43", /* FgBlue */ "44", /* FgMagenta */ "45", /* FgCyan */ "46", /* FgWhite */ "47",
        /* FgBrightBlack */ "100", /* FgBrightRed */ "101", /* FgBrightGreen */ "102", /* FgBrightYellow */ "103", /* FgBrightBlue */ "104", /* FgBrightMagenta */ "105", /* FgBrightCyan */ "106", /* FgBrightWhite */ "107", /* FgDefault */ "49",
        /* BgBlack */ "30", /* BgRed */ "31", /* BgGreen */ "32", /* BgYellow */ "33", /* BgBlue */ "34", /* BgMagenta */ "35", /* BgCyan */ "36", /* BgWhite */ "37",
        /* BgBrightBlack */ "90", /* BgBrightRed */ "91", /* BgBrightGreen */ "92", /* BgBrightYellow */ "93", /* BgBrightBlue */ "94", /* BgBrightMagenta */ "95", /* BgBrightCyan */ "96", /* BgBrightWhite */ "97", /* BgDefault */ "39"
    };

    template<typename Val>
    static void 
    out(std::ostream& ostr, 
                    Val&& data, 
                    StyleCodes code = StyleCodes::Standard,
                    ColorCodes fgcode = ColorCodes::FgDefault,
                    ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        if((code > 5) || (fgcode > 39) || (bgcode > 39)) return;
        
        ostr << "\x1b[" << _vals[code] << ";" << _vals[bgcode] << "m"
             << "\x1b[" << _vals[code] << ";" << _vals[fgcode] << "m" 
             << idk::move(data);
    }

    template<typename Val>
    static void 
    out(std::ostream& ostr, 
                    const Val& data, 
                    StyleCodes code = StyleCodes::Standard,
                    ColorCodes fgcode = ColorCodes::FgDefault,
                    ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        if((code > 5) || (fgcode > 39) || (bgcode > 39)) return;
        
        ostr << "\x1b[" << _vals[code] << ";" << _vals[bgcode] << "m"
             << "\x1b[" << _vals[code] << ";" << _vals[fgcode] << "m" 
             << data;
    }

    template<typename Val>
    static void 
    cout(Val&& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::cout, data, code, fgcode, bgcode);
    }

    template<typename Val>
    static void 
    cout(const Val& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::cout, data, code, fgcode, bgcode);
    }

    template<typename Val>
    static void 
    cerr(Val&& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::cerr, data, code, fgcode, bgcode);
    }

    template<typename Val>
    static void 
    cerr(const Val& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::cerr, data, code, fgcode, bgcode);
    }

    template<typename Val>
    static void 
    clog(Val&& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::clog, data, code, fgcode, bgcode);
    }

    template<typename Val>
    static void 
    clog(const Val& data, 
                      StyleCodes code = StyleCodes::Standard,
                      ColorCodes fgcode = ColorCodes::FgDefault,
                      ColorCodes bgcode = ColorCodes::BgDefault) noexcept {
        out(std::clog, data, code, fgcode, bgcode);
    }
    
    template<typename Val>
    static void 
    reset(Val&& data) noexcept {
        out(std::cout, data, StyleCodes::Standard, ColorCodes::FgDefault, ColorCodes::BgDefault);
    }

    template<typename Val>
    static void 
    reset(const Val& data) noexcept {
        out(std::cout, data, StyleCodes::Standard, ColorCodes::FgDefault, ColorCodes::BgDefault);
    }

    static void 
    reset() noexcept {
        out(std::clog, "", StyleCodes::Standard, ColorCodes::FgDefault, ColorCodes::BgDefault);
    }
};

using Style = ColorBase::StyleCodes;
using Color = ColorBase::ColorCodes;
} // namespace idk