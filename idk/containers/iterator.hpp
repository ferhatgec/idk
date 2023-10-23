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

#include "node.hpp"

namespace idk {
template<typename Container, typename Type>
class IteratorBase {
    Container* _curr;
public:
    IteratorBase() : _curr(nullptr) {}
    IteratorBase(Container* node) : _curr(node) {}

    Type&
    operator*() const {
        return this->_curr->_data;
    }

    IteratorBase&
    operator++() {
        if(this->_curr != nullptr)
            this->_curr = this->_curr->_next;

        return *this;
    }

    __idk_nodiscard
    bool 
    operator==(const IteratorBase& other) const noexcept {
        return this->_curr == other._curr;
    }

    __idk_nodiscard
    bool 
    operator!=(const IteratorBase& other) const noexcept {
        return !(*this == other);
    }
};
    
template<typename Type>
using PNIterator = IteratorBase<PNNode<Type>, Type>;

template<typename Type>
using Iterator   = IteratorBase<Node<Type>, Type>;
} // namespace idk