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
#include "../types/valueor.hpp"
#include "../utilities/semantics.hpp"
#include "iterator.hpp"
#include "node.hpp"

namespace idk {
template<typename Type>
class List {
    PNNode<Type>* _head,
                * _tail;

    usize         _size { 0 };

    Type          _empty;
public:
    enum class Error {
        Out_Of_Range,
    };

    List() : _head(nullptr), _tail(nullptr) {}

    List(std::initializer_list<Type> vals) : _head(nullptr), _tail(nullptr) {
        for(const Type& val: vals)
            this->push_back(val);
    }

    ~List() {
        while(this->_head != nullptr) {
            PNNode<Type>* _temp = this->_head;
            this->_head = this->_head->_next;
            delete _temp;
        }
    }

    void
    push_back(Type&& val) noexcept {
        PNNode<Type>* _node = new PNNode<Type>(idk::move(val));

        if(this->_head == nullptr) {
            this->_head = _node;
            this->_tail = _node;
        } else {
            _node->_prev       = this->_tail;
            this->_tail->_next = _node;
            this->_tail        = _node;
        }

        ++this->_size;
    }

    void
    push_back(const Type& val) noexcept {
        PNNode<Type>* _node = new PNNode<Type>(val);

        if(this->_head == nullptr) {
            this->_head = _node;
            this->_tail = _node;
        } else {
            _node->_prev        = this->_tail;
            this->_tail->_next = _node;
            this->_tail        = _node;
        }

        ++this->_size;
    }

    void
    push_front(Type&& val) noexcept {
        PNNode<Type>* _node = new PNNode<Type>(idk::move(val));

        if(this->_head == nullptr) {
            this->_head = _node;
            this->_tail = _node;
        } else {
            _node->_next       = this->_head;
            this->_head->_prev = _node;
            this->_head        = _node;
        }

        ++this->_size;
    }

    void
    push_front(const Type& val) noexcept {
        PNNode<Type>* _node = new PNNode<Type>(val);

        if(this->_head == nullptr) {
            this->_head = _node;
            this->_tail = _node;
        } else {
            _node->_next       = this->_head;
            this->_head->_prev = _node;
            this->_head        = _node;
        }

        ++this->_size;
    }

    void
    pop_back() noexcept {
        if(this->_tail == nullptr) 
            return;

        if(this->_tail == this->_head) {
            delete this->_tail;
            this->_head = nullptr;
            this->_tail = nullptr;
        } else {
            PNNode<Type>* _temp = this->_tail;
            this->_tail         = this->_tail->_prev;
            this->_tail->_next  = nullptr;
            delete _temp;
        }

        --this->_size;
    }

    void
    pop_front() noexcept {
        if(this->_head == nullptr)
            return;

        if(this->_tail == this->_head) {
            delete this->_head;
            this->_head = nullptr;
            this->_tail = nullptr;
        } else {
            PNNode<Type>* _temp = this->_head;
            this->_head         = this->_head->_next;
            this->_head->_prev  = nullptr;
        }

        --this->size;
    }

    ValueOr<Type, Error>
    operator[](const usize&& n) noexcept {
        return this->at(idk::move(n));
    }

    ValueOr<Type, Error>
    at(const usize&& n) noexcept {
        Type _val = this->at_without_check(idk::move(n));
        
        if(_val == this->_empty)
            return Unexpected<Error>(Error::Out_Of_Range);

        return Expected<Type>(_val);
    }

    Type
    at_without_check(const usize&& n) {
        if(n >= this->_size)
            return this->_empty;

        PNNode<Type>* _curr = this->_head;

        for(usize i = 0; i < n; ++i)
            _curr = _curr->_next;

        return _curr->_data;
    }

    PNIterator<Type>
    begin() noexcept {
        return PNIterator<Type>(this->_head);
    }

    PNIterator<Type>
    end() noexcept {
        return PNIterator<Type>();
    }

    [[nodiscard]]
    usize
    size() const noexcept {
        return this->_size;
    } 

    [[nodiscard]]
    usize
    max_size() const noexcept {
        return this->size();
    }

    [[nodiscard]]
    bool
    is_empty() const noexcept {
        return this->_size == 0;
    }
};
} // namespace idk