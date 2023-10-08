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
#include "../containers/vector.hpp"
#include "../types/stringview.hpp"
#include "../utilities/pair.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
// key value storage
class Argument {
    Pair<StringViewChar, StringViewChar>
        arg;

    StringViewChar init;
public:
    Argument(StringViewChar&& key, StringViewChar&& value) noexcept {
        this->arg = MakePair<StringViewChar, StringViewChar>(key, value);
    }

    Argument() noexcept {
        this->arg = MakePair<StringViewChar, StringViewChar>(this->init, this->init);
    }

    Argument(StringViewChar&& key) noexcept {
        this->arg = MakePair<StringViewChar, StringViewChar>(key, this->init);
    }

    ~Argument() = default;

    [[nodiscard]]
    bool
    has_key() noexcept {
        return !this->arg.first().is_empty();
    }

    [[nodiscard]]
    bool
    has_value() noexcept {
        return !this->arg.second().is_empty();
    }

    [[nodiscard]]
    StringViewChar&
    key() noexcept {
        return this->arg.first();
    }

    [[nodiscard]]
    StringViewChar&
    value() noexcept {
        return this->arg.second();
    }

    friend std::ostream&
    operator<<(std::ostream& ostr, Argument& arg) {
        if(arg.has_value())
            ostr << '[' << arg.key() << ", " << arg.value() << ']';
        else
            ostr << arg.key();
        
        return ostr;
    }

    friend std::ostream&
    operator<<(std::ostream& ostr, Argument&& arg) {
        if(arg.has_value())
            ostr << '[' << arg.key() << ", " << arg.value() << ']';
        else
            ostr << arg.key();
        
        return ostr;
    }
};

class Arguments {
    usize         _argc;
    Vec<Argument> _args;
public:
    enum class Error {
        Out_Of_Range
    };

    explicit Arguments(int argc, char** argv) noexcept : _argc(argc) {
        for(usize n = 0; n < argc; ++n) {
            this->_args.push_back(parse(StringViewChar(argv[n])));
        }
    }

    explicit Arguments(char** argv) noexcept {
        char** ptr = argv;

        while(*ptr != nullptr) {
            this->_args.push_back(parse(StringViewChar(*ptr)));
            ++ptr;
            ++this->_argc;
        }
    }

    explicit Arguments(Vec<StringViewChar>& argv) noexcept {
        for(auto& arg: argv) {
            this->_args.push_back(parse(StringViewChar(arg)));
            ++this->_argc;
        }
    }

    Arguments() {}

    ~Arguments() = default;

    [[nodiscard]]
    static Argument
    parse(StringViewChar&& arg) noexcept {
        if(arg.is_empty())
            return Argument(idk::move(arg));

        for(usize i = 0; i < arg.length(); ++i)
            if((arg[i].try_get_value() == '=') 
                || arg[i].try_get_value() == ':')
                return Argument(arg.substr(0, i), arg.substr(i + 1, arg.length() - i - 1));

        return Argument(idk::move(arg));
    }


    // finds key
    [[nodiscard]]
    bool
    find(StringViewChar&& arg) noexcept {
        for(auto& val: this->_args)
            if(val.key() == arg)
                return true;

        return false;
    }

    // finds key
    [[nodiscard]]
    bool
    find(Vec<StringViewChar>&& args) noexcept {
        for(auto& val: this->_args) {
            if(!val.has_key())
                continue;
            
            for(auto& arg: args) {
                if(arg.is_empty())
                    continue;

                // first, we are comparing the last characters; -just because commonly '-' and '--' used for passing flags, 
                // so first character would same- if not same, skipping it. both have constant time operations.
                if((val.key().length() == arg.length()) && val.key().back() == arg.back())
                    if(val.key() == arg)
                        return true;
            }
        }

        return false;
    }

    [[nodiscard]]
    Argument*
    begin() noexcept {
        return this->_args.begin();
    }

    [[nodiscard]]
    Argument*
    end() noexcept {
        return this->_args.end();
    }

    ValueOr<Argument, Error>
    operator[](usize&& n) noexcept {
        return this->at(idk::move(n));
    }

    ValueOr<Argument, Error>
    at(usize&& n) noexcept {
        if(n >= this->_args.size())
            return Unexpected<Error>(Error::Out_Of_Range);

        return Expected<Argument>(this->_args.at_without_check(idk::move(n)));
    }
};
} // namespace idk