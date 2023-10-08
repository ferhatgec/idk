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
class Stack {
    T        _keep;
    usize    _elems { 0 };
    Node<T>* _top;
public:
    Stack() : _top(nullptr) {}
    
    ~Stack() {
        while(!this->is_empty())
            this->pop();
    }

    void
    push(const T& val) noexcept {
        Node<T>* _new  = new Node<T>(val);
        _new->_next = this->_top;
        this->_top  = _new;
        ++this->_elems;
    }

    void
    push(T&& val) noexcept {
        Node<T>* _new  = new Node<T>(val);
        _new->_next = this->_top;
        this->_top  = _new;
        ++this->_elems;
    }

    void
    pop() noexcept {
        if(!this->is_empty()) {
            Node<T>* _temp = this->_top;
            this->_top  = _top->_next;
            delete _temp;
            --this->_elems;
        }
        
        return;
    }

    T&
    top() noexcept {
        if(!this->is_empty()) {
            return this->_top->_data;
        }

        return this->_keep;
    }

    [[nodiscard]]
    bool
    is_empty() const noexcept {
        return this->_top == nullptr;
    }

    [[nodiscard]]
    usize
    size() const noexcept {
        return this->_elems;
    }

    [[nodiscard]]
    usize
    max_size() const noexcept {
        return this->size();
    }

    Stack<T>&
    operator=(const Stack<T>& other) noexcept {
        if(&other == this)
            return *this;

        Node<T>* _temp = this->_top;
        this->_elems= other._elems;
        this->_top  = other._top;
        delete _temp;

        return *this;
    }

    Stack<T>&
    operator=(Stack<T>&& other) noexcept {
        if(other == this)
            return *this;

        Node<T>* _temp = this->_top;
        this->_elems= idk::move(other._elems);
        this->_top  = idk::move(other._top);
        delete _temp;
        
        return *this;
    }

    template<typename _T, typename _U>
    friend bool
    operator==(const Stack<_T>& left, const Stack<_U>& right) noexcept {
        if(!idk::IsSameVal<_T, _U> || left._elems != right._elems)
            return false;

        return left._top == right._top;
    }

    template<typename _T, typename _U>
    friend bool
    operator!=(const Stack<_T>& left, const Stack<_U>& right) noexcept {
        return !operator==(left, right);
    }
};
} // namespace idk