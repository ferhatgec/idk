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

#include "../utilities/type_traits.hpp"
#include "node.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename T>
class Queue {
    T        _keep;
    usize    _elems { 0 };
    Node<T>* _first,
           * _rear;
public:
    Queue() : _first(nullptr), _rear(nullptr) {}
    
    ~Queue() {
        while(!this->is_empty())
            this->pop();
    }

    void
    push(const T& val) noexcept {
        ++this->_elems;
        Node<T>* _new = new Node<T>(val);

        if(this->is_empty()) {
            this->_first = _new;
            this->_rear  = _new;
            return;
        }

        this->_rear->_next = _new;
        this->_rear        = _new;
    }

    void
    push(T&& val) noexcept {
        ++this->_elems;
        Node<T>* _new = new Node<T>(val);
        
        if(this->is_empty()) {
            this->_first = _new;
            this->_rear  = _new;
            return;
        }

        this->_rear->_next = _new;
        this->_rear        = _new;
    }

    void
    pop() noexcept {
        if(!this->is_empty()) {
            --this->_elems;
            Node<T>* _temp = this->_first;
            this->_first   = this->_first->_next;
            delete _temp;
        }
    }

    T&
    top() noexcept {
        if(!this->is_empty())
            return this->_first->_data;
        
        return this->_keep;
    }

    __idk_nodiscard
    usize
    size() const noexcept {
        return this->_elems;
    }

    __idk_nodiscard
    usize
    max_size() const noexcept {
        return this->size();
    }

    __idk_nodiscard
    bool
    is_empty() const noexcept {
        return this->_first == nullptr;
    }
    
    Queue<T>&
    operator=(const Queue<T>& other) noexcept {
        if(&other == this)
            return *this;

        Node<T>* _temp = this->_first,
               * _temp2= this->_rear;

        this->_elems   = other._elems;
        this->_first   = other._top;
        this->_rear    = other._rear;
        
        delete _temp, _temp2;

        return *this;
    }

    Queue<T>&
    operator=(Queue<T>&& other) noexcept {
        if(other == this)
            return *this;

        Node<T>* _temp = this->_first,
               * _temp2= this->_rear;

        this->_elems   = idk::move(other._elems);
        this->_first   = idk::move(other._top);
        this->_rear    = idk::move(other._rear);
        
        delete _temp, _temp2;
        
        return *this;
    }

    template<typename _T, typename _U>
    friend bool
    operator==(const Queue<_T>& left, const Queue<_U>& right) noexcept {
        if(!idk::IsSameVal<_T, _U> || left._elems != right._elems)
            return false;

        return (left._first == right._first) && (left._rear == right._rear);
    }

    template<typename _T, typename _U>
    friend bool
    operator!=(const Queue<_T>& left, const Queue<_U>& right) noexcept {
        return !operator==(left, right);
    }
};
} // namespace idk