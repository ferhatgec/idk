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

#include "../utilities/semantics.hpp"

namespace idk {
template<typename T>
struct Node {
    T     _data;
    Node* _next;
        
    Node(const T& val) : _data(val), _next(nullptr) {}
    Node(T&& val) : _data(idk::move(val)), _next(nullptr) {}
};

template<typename T>
class PNNode {
public:
    T       _data;
    PNNode* _prev, 
          * _next;

    PNNode(const T& val) : _data(val), _prev(nullptr), _next(nullptr) {}
    PNNode(T&& val) : _data(idk::move(val)), _prev(nullptr), _next(nullptr) {}
};
} // namespace idk