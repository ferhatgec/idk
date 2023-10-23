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
#include "../utilities/split.hpp"
#include "../utilities/semantics.hpp"
#include <fstream>

namespace idk {
class WGSDBlock {
public:
    StringViewChar block_name = "undefined";
    Vec<Pair<StringViewChar, StringViewChar>> matched_datas;

    WGSDBlock () = default;
    ~WGSDBlock() = default;

    StringViewChar
    get_value(const StringViewChar& str) noexcept {
        for(auto& val: matched_datas)
            if(val.first() == str)
                return val.second();

        return StringViewChar();
    }

    __idk_nodiscard
    bool
    contains(const StringViewChar& str) noexcept {
        for(auto& node: this->matched_datas)
            if(node.first() == str)
                return true;

        return false;
    }

    __idk_nodiscard
    isize
    find(const StringViewChar& str) noexcept {
        for(usize n = 0; n < this->matched_datas.size(); ++n)
            if(this->matched_datas[n].try_get_value().first() == str)
                return n;
        
        return -1;
    }
};

class WGSD {
    StringViewChar raw_file_data = "";
public:
    Vec<WGSDBlock> nodes;

    WGSD () = default;
    ~WGSD() = default;

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
        this->parse_file(idk::move(file));
    }

    __idk_nodiscard
    StringViewChar
    generate() noexcept {
        StringViewChar generate = "";

        for(auto& node: this->nodes) {
            generate = generate + node.block_name + " =\n";

            for(auto& node_key: node.matched_datas) {
                auto val = node.get_value(node_key.first());

                if(!val.is_empty())
                    generate = generate + node_key.first() + ";" + val + ";\n";

            }

            generate = generate + "end; " + node.block_name + ";\n";
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
                (void)node.matched_datas.change_val_at_index(index, MakePair(key, replace));
    }

    __idk_nodiscard
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

        for(auto& line: idk::split(this->raw_file_data, '\n')) {
            line.trim_spaces();

            if(!line.is_empty()) {
                switch(line.front()) {
                    case '#':
                        break;
                    
                    default: {
                        if(!is_block) {
                            is_block = true;

                            auto x = idk::split(line);
                            
                            if(!x.is_empty() && x[1].try_get_value() == "=") {
                                WGSDBlock y;

                                y.block_name = x[0].try_get_value();

                                this->nodes.push_back(y);
                            }
                        } else {
                            auto x = idk::split(line, ';');

                            if(x.size() >= 2) {
                                if(x[0].try_get_value() == "end")
                                    is_block = false;
                                else {
                                    auto x0 = x[0].try_get_value(),
                                         x1 = x[1].try_get_value();

                                    x0.trim_spaces();
                                    x1.trim_spaces();

                                    this->nodes.back().matched_datas.push_back(MakePair<StringViewChar, StringViewChar>(x0, x1));
                                }
                            }
                        }

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
};
} // namespace idk