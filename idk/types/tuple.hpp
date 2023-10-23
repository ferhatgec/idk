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

#include "predefined.hpp"
#include "../utilities/type_traits.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<usize Index, typename T>
struct TupleElement {
    TupleElement() = default;
    ~TupleElement()= default;

    template<typename U>
    TupleElement(U&& val) : _value(idk::forward<U>(val)) {}

    template<typename U>
    TupleElement(const U& val) : _value(idk::RemoveReferenceType<U&>(const_cast<U&>(val))) {}

    T _value;
};

template<typename... Types> struct Tuple;

template<typename Head, typename... Tail>
struct Tuple<Head, Tail...> : public Tuple<Tail...>, public TupleElement<sizeof...(Tail), Head> {
    using BaseType = Tuple<Tail...>;
    using Element  = TupleElement<sizeof...(Tail), Head>;

    Tuple() = default;

    template<typename HeadArg, typename... TailArgs>
    Tuple(HeadArg&& head_arg, TailArgs&&... tail_args) 
        : BaseType(idk::forward<TailArgs>(tail_args)...), 
          Element(idk::forward<HeadArg>(head_arg)) {}

    template<typename HeadArg, typename... TailArgs>
    Tuple(const HeadArg& head_arg, const TailArgs&... tail_args) 
        : BaseType(idk::RemoveReferenceType<HeadArg&>(const_cast<HeadArg&>(tail_args))...), 
          Element(idk::RemoveReferenceType<HeadArg&>(const_cast<HeadArg&>(head_arg))) {}

    template<usize Index, usize Val = sizeof...(Tail) - Index>
    __idk_constexpr decltype(auto) 
    Get() {
        if __idk_constexpr(Val == sizeof...(Tail))
            return Element::_value;
        else
            return BaseType::template Get<Val>();
    }

    template<usize Index, usize Val = sizeof...(Tail) - Index>
    __idk_constexpr decltype(auto) 
    Get() const {
        if __idk_constexpr(Val == sizeof...(Tail))
            return Element::_value;
        else
            return BaseType::template Get<Val>();
    }

    template<usize Val = sizeof...(Tail) + 1>
    __idk_constexpr usize 
    length() const noexcept {
        return Val;
    }

    template<usize Val = sizeof...(Tail)>
    __idk_constexpr usize 
    max_index() const noexcept {
        return Val;
    }
private:
};

template<> struct Tuple<> {};
} // namespace idk