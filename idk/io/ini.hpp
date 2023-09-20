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

#include "../types/stringview.hpp"
#include "../containers/vector.hpp"
#include "../utilities/pair.hpp"
#include <fstream>

namespace idk {
class INIBlock {
public:
    StringViewChar block_name = "undefined";
    Vec<Pair<StringViewChar, StringViewChar>> matched_datas;

    INIBlock () = default;
    ~INIBlock() = default;

    StringViewChar
    get_value(const StringViewChar& str) noexcept {
        for(auto& val: matched_datas)
            if(val.first() == str)
                return val.second();

        return StringViewChar();
    }

    [[nodiscard]]
    bool
    contains(const StringViewChar& str) noexcept {
        for(auto& node: this->matched_datas)
            if(node.first() == str)
                return true;

        return false;
    }

    [[nodiscard]]
    isize
    find(const StringViewChar& str) noexcept {
        for(usize n = 0; n < this->matched_datas.size(); ++n)
            if(this->matched_datas[n].try_get_value().first() == str)
                return n;
        
        return -1;
    }
};

class INI {
    StringViewChar raw_file_data = "";
public:
    Vec<INIBlock> nodes;

    INI () = default;
    ~INI() = default;

    void
    clear() noexcept {
        this->nodes.clear();
        this->raw_file_data.clear();
    }

    void
    reparse_file(const StringViewChar& file) noexcept {
        this->clear();
        this->parse_file(file);
    }

    void
    reparse_file(StringViewChar&& file) noexcept {
        this->clear();
        this->parse_file(std::move(file));
    }

    [[nodiscard]]
    StringViewChar
    generate() noexcept {
        StringViewChar generate = "";

        for(auto& node: this->nodes) {
            generate = generate + "[" + node.block_name + "]\n";

            for(auto& node_key: node.matched_datas) {
                auto val = node.get_value(node_key.first());

                if(!val.is_empty())
                    generate = generate + node_key.first() + " = " + val + "\n";

            }

            generate.push_back('\n');
        }

        return generate;
    }

    void
    change_key(const StringViewChar& block,
               const StringViewChar& key,
               const StringViewChar& replace) noexcept {
        for(auto& node: this->nodes)
            if(auto index = node.find(key); 
                node.block_name == block
                && index >= 0)
                node.matched_datas.change_val_at_index(index, MakePair(key, replace));
    }

    [[nodiscard]]
    StringViewChar
    get_value(const StringViewChar& block, const StringViewChar& key) noexcept {
        for(auto& node: this->nodes)
            if(auto index = node.find(key); 
                node.block_name == block
                && index >= 0)
                return node.matched_datas[index].try_get_value().second();

        return StringViewChar();
    }

    void
    parse_file(const StringViewChar& file) noexcept {
        bool is_block = false;

        {
            std::ifstream file_stream(file.data());
        
            char ch;

            while(file_stream.peek() != EOF) {
                file_stream.get(ch);
                this->raw_file_data.push_back(ch);
            }

            file_stream.close();
        }

        for(auto& line: this->split(this->raw_file_data, '\n')) {
            line.trim_spaces_left();

            if(!line.is_empty()) {
                if(line.starts_with(';'))
                    continue;
                
                switch(line.front()) {
                    case '[': {
                        for(usize n = 1; n < line.length(); ++n)
                            if(auto ch = line[n].try_get_value(); ch != ']')
                                this->_temp.push_back(ch);

                        this->_temp.trim_spaces();
                        INIBlock y;
                        y.block_name = this->_temp;

                        this->nodes.push_back(y);
                        this->_temp.clear();

                        break;
                    }

                    case '\n': 
                        break;

                    default: {
                        usize n;

                        for(n = 0; n < line.length(); ++n)
                            if(line[n].try_get_value() == '=')
                                break;
                            else
                                this->_temp.push_back(line[n].try_get_value());

                        this->_temp.trim_spaces();

                        ++n;

                        if(n < line.length() && line[n].try_get_value() == ' ')
                            ++n;
                        
                        for(; n < line.length(); ++n)
                            this->_value.push_back(line[n].try_get_value());

                        this->nodes.back().matched_datas.push_back(
                            MakePair<StringViewChar, StringViewChar>(this->_temp, this->_value));
                        
                        this->_temp.clear();
                        this->_value.clear();

                        break;
                    }
                }
            }
        }
    }

    void
    parse_file(StringViewChar&& file) noexcept {
        this->parse_file(file);
    }
private:
    StringViewChar _temp, _value;

    Vec<StringViewChar>
    split(const StringViewChar& str, char delim = ' ') noexcept {
        Vec<StringViewChar> vec;
        char* context = nullptr;
        char* token = strtok_s(str.data(), &delim, &context); // FIXME: strtok_s from c++ stl has 4 arguments,
                                                             // instead, microsoft's implementation contains 3 arguments.

        while(token != nullptr) {
            vec.push_back(StringViewChar(token));
            token = strtok_s(nullptr, &delim, &context);
        }

        if(token != nullptr)
            vec.push_back(StringViewChar(token));

        return vec;
    }
};
} // namespace idk