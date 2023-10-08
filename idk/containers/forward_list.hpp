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
#include "iterator.hpp"
#include "../types/valueor.hpp"
#include "../types/predefined.hpp"
#include "../utilities/type_traits.hpp"
#include "../utilities/semantics.hpp"
#include <algorithm>

namespace idk {
template<typename Type> 
class ForwardList {
    Node<Type>* _head;
    usize       _size { 0 };
    Type        _empty;
public:
    enum class Error {
        Out_Of_Range,
        ListEmpty
    };

    ForwardList() : _head(nullptr) {}

    ForwardList(std::initializer_list<Type> vals) {
        std::reverse(const_cast<Type*>(vals.begin()), const_cast<Type*>(vals.end()));

        for(const Type& val: vals)
            this->push_front(val);
    }

    ~ForwardList() {
        this->clear();
    }

    void
    push_front(const Type& val) noexcept {
        ++this->_size;
        Node<Type>* _temp = new Node<Type>(val);
        _temp->_next = this->_head;
        this->_head = _temp; 
    }

    void
    push_front(Type&& val) noexcept {
        ++this->_size;
        Node<Type>* _temp = new Node<Type>(idk::move(val));
        _temp->_next = this->_head;
        this->_head = _temp; 
    }

    void
    pop_front() noexcept {
        if(!this->is_empty()) {
            --this->_size;
            Node<Type>* _temp = this->_head;
            this->_head = this->_head->_next;
            
            delete _temp;
        }
    }

    [[nodiscard]]
    bool
    is_empty() const noexcept {
        return this->_head == nullptr;
    }

    void
    clear() noexcept {
        for(usize n = 1; n < this->_size; ++n)
            this->pop_front();
    }

    ValueOr<Type, Error>
    operator[](const usize&& n) noexcept {
        return this->at(idk::move(n));
    }

    ValueOr<Type, Error>
    at(usize&& n) noexcept {
        Type _val = this->at_without_check(idk::move(n));
        
        if(_val == this->_empty)
            return Unexpected<Error>(Error::Out_Of_Range);

        return Expected<Type>(_val);
    }

    ValueOr<Type, Error>
    at(const usize& n) noexcept {
        Type _val = this->at_without_check(n);
        
        if(_val == this->_empty)
            return Unexpected<Error>(Error::Out_Of_Range);

        return Expected<Type>(_val);
    }

    Type
    at_without_check(usize&& n) {
        if(n >= this->_size)
            return this->_empty;
            
        Node<Type>* _curr = this->_head;
        
        for(usize i = 0; i < n; ++i)
            _curr = _curr->_next;
        
        return _curr->_data;
    }

    Type
    at_without_check(const usize& n) {
        if(n >= this->_size)
            return this->_empty;
            
        Node<Type>* _curr = this->_head;
        
        for(usize i = 0; i < n; ++i)
            _curr = _curr->_next;
        
        return _curr->_data;
    }

    Iterator<Type>
    begin() noexcept {
        return Iterator(this->_head);
    }

    Iterator<Type>
    end() noexcept {
        return Iterator<Type>();
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
    Type& 
    front() const noexcept {
        if(this->is_empty())
            return this->_empty;

        return this->_head->_data;
    }

    ValueOr<Type, Error>
    front_no_reference() const noexcept {
        if(this->is_empty())
            return Unexpected<Error>(Error::ListEmpty);

        return Expected<Type>(this->_head->_data);
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, ForwardList<Type>& list) {
        ostr << '[';
        
        for(usize n = 0; n < list.size(); ++n)
            if(n + 1 == list.size())
                ostr << list.at_without_check(n);
            else
                ostr << list.at_without_check(n) << ", ";

        ostr << ']';
        return ostr;
    }

    template<typename _T, typename _U>
    friend bool
    operator==(const ForwardList<_T>& left, const ForwardList<_U>& right) noexcept {
        if(!idk::IsSameVal<_T, _U> || left._size != right._size)
            return false;

        return left._head == right._head;
    }

    template<typename _T, typename _U>
    friend bool
    operator!=(const ForwardList<_T>& left, const ForwardList<_U>& right) noexcept {
        return !operator==(left, right);
    }
};
} // namespace idk