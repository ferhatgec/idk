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

#include "tuple.hpp"

namespace idk {
template<typename... Types> struct ReversedTuple;

template<typename Head, typename... Tail>
struct ReversedTuple<Head, Tail...> : public ReversedTuple<Tail...>, public TupleElement<sizeof...(Tail), Head> {
    using BaseType = ReversedTuple<Tail...>;
    using Element  = TupleElement<sizeof...(Tail), Head>;

    ReversedTuple() = default;

    template<typename HeadArg, typename... TailArgs>
    ReversedTuple(HeadArg&& head_arg, TailArgs&&... tail_args) 
        : BaseType(std::forward<TailArgs>(tail_args)...), 
          Element(std::forward<HeadArg>(head_arg)) {}

    template<typename HeadArg, typename... TailArgs>
    ReversedTuple(const HeadArg& head_arg, const TailArgs&... tail_args) 
        : BaseType(idk::RemoveReferenceType(const_cast<HeadArg&>(tail_args))...), 
          Element(idk::RemoveReferenceType(const_cast<HeadArg&>(head_arg))) {}

    template<usize Index>
    constexpr decltype(auto) 
    Get() {
        if constexpr(Index == sizeof...(Tail))
            return Element::_value;
        else
            return BaseType::template Get<Index>();
    }

    template<usize Index>
    constexpr decltype(auto) 
    Get() const {
        if constexpr(Index == sizeof...(Tail))
            return Element::_value;
        else
            return BaseType::template Get<Index>();
    }

    template<usize Val = sizeof...(Tail) + 1>
    constexpr usize 
    length() const noexcept {
        return Val;
    }

    template<usize Val = sizeof...(Tail)>
    constexpr usize 
    max_index() const noexcept {
        return Val;
    }
private:
};

template<> struct ReversedTuple<> {};
} // namespace idk