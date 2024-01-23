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
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <ostream>

#ifdef __idk_convert_into_std_complex
#   include <complex>
#endif

#include "../utilities/type_traits.hpp"
#include "../utilities/semantics.hpp"

namespace idk {
template<typename Type, idk::EnableIfType<idk::IntegralConstant<bool,
                            (idk::IsFloatingPointVal<Type> || idk::IsIntegralVal<Type>)>::value, bool> = true>
class Complex {
    Type _real_part { static_cast<Type>(0) },
         _imaginary_part { static_cast<Type>(0) };
public:
    Complex() = default;
    Complex(const Type& real_part, const Type& imaginary_part) : _real_part(real_part), 
                                                                 _imaginary_part(imaginary_part) 
                                                                 {}
    
    Complex(Type&& real_part, Type&& imaginary_part) : _real_part(idk::move(real_part)), 
                                                       _imaginary_part(idk::move(imaginary_part)) 
                                                       {}
    ~Complex() = default;

    __idk_nodiscard
    Type
    real_part() noexcept {
        return this->_real_part;
    }

    __idk_nodiscard
    Type
    real() noexcept {
        return this->_real_part;
    }

    __idk_nodiscard
    Type
    imaginary_part() noexcept {
        return this->_imaginary_part;
    }

    __idk_nodiscard
    Type
    imaginary() noexcept {
        return this->_imaginary_part;
    }

    __idk_nodiscard
    Type
    magnitude() noexcept {
        {
            using TypeNoRef = idk::RemoveConstAndVolatileType<Type>;

            if constexpr(idk::IsSameVal<TypeNoRef, idk::f32>)
                return sqrtf(this->norm());
        
            if constexpr(idk::IsSameVal<TypeNoRef, idk::f64>)
                return sqrt(this->norm());
        }

        return sqrtl(this->norm());
    }

    __idk_nodiscard
    Type
    length() noexcept {
        return this->magnitude();
    }

    __idk_nodiscard
    Type
    absolute() noexcept {
        return this->magnitude();
    }

    __idk_nodiscard
    Type
    abs() noexcept {
        return this->magnitude();
    }

    __idk_nodiscard
    Type
    norm() noexcept {
        return (this->_real_part * this->_real_part) + (this->_imaginary_part * this->_imaginary_part);
    }

    __idk_nodiscard
    Complex<Type>
    conjugate() noexcept {
        return Complex<Type>(this->_real_part, -1 * this->_imaginary_part);
    }

    __idk_nodiscard
    Complex<Type>
    copy() noexcept {
        return Complex<Type>(this->_real_part, this->_imaginary_part);
    }

    __idk_nodiscard
#ifdef __idk_convert_into_std_complex
    std::complex<Type>
#else 
    Complex<Type>
#endif
    convert() noexcept {
#ifdef __idk_convert_into_std_complex
        return std::complex<Type>(this->_real_part, this->_imaginary_part);
#else 
        return this.copy();
#endif
    }

    friend std::ostream& 
    operator<<(std::ostream& ostr, Complex<Type>& val) noexcept {
        if(val._real_part != 0) {
            ostr << val._real_part;

            if(val._imaginary_part != 0)
                ostr << " " << val._imaginary_part << "i";
        } else if(val._imaginary_part != 0)
            ostr << val._imaginary_part << "i";
        
        return ostr;
    }
    
    friend std::ostream& 
    operator<<(std::ostream& ostr, Complex<Type>&& val) noexcept {
        return operator<<(ostr, val);
    }

    friend std::wostream& 
    operator<<(std::wostream& ostr, Complex<Type>& val) noexcept {
        if(val._real_part != 0) {
            ostr << val._real_part;

            if(val._imaginary_part != 0)
                ostr << " " << val._imaginary_part << "i";
        } else if(val._imaginary_part != 0)
            ostr << val._imaginary_part << "i";

        return ostr;
    }

    friend std::wostream& 
    operator<<(std::wostream& ostr, Complex<Type>&& val) noexcept {
        return operator<<(ostr, val);
    }

    Complex<Type>& 
    operator=(const Complex<Type>& other) noexcept {
        if(this == &other)
            return *this;
        
        this->_real_part      = other._real_part;
        this->_imaginary_part = other._imaginary_part;

        return *this;
    }

    Complex<Type>&
    operator=(Complex<Type>&& other) noexcept {
        if(this == &other)
            return *this;
        
        this->_real_part      = idk::move(other._real_part);
        this->_imaginary_part = idk::move(other._imaginary_part);
        
        return *this;
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>& left, Complex<Type>& right) {
        return Complex<Type>((left._real_part + right._real_part), (left._imaginary_part + right._imaginary_part));
    }

    friend 
    Complex<Type>
    operator+(const Type& left, Complex<Type>& right) {
        return Complex<Type>(left + right._real_part, right._imaginary_part);
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>& left, const Type& right) {
        return Complex<Type>(left._real_part + right, left._imaginary_part);
    }

    friend 
    Complex<Type>
    operator+(Type&& left, Complex<Type>& right) {
        return operator+(left, right);
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>& left, Type&& right) {
        return operator+(left, right);
    }

    friend 
    Complex<Type>
    operator-(Complex<Type>& left, Complex<Type>& right) {
        return Complex<Type>((left._real_part - right._real_part), (left._imaginary_part - right._imaginary_part));
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>&& left, Complex<Type>&& right) {
        return operator+(left, right);  
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>&& left, Complex<Type>& right) {
        return operator+(left, right);  
    }

    friend 
    Complex<Type>
    operator+(Complex<Type>& left, Complex<Type>&& right) {
        return operator+(left, right);  
    }

    friend 
    Complex<Type>
    operator-(Complex<Type>&& left, Complex<Type>&& right) {
        return operator-(left, right);  
    }

    friend 
    Complex<Type>
    operator-(Complex<Type>&& left,Complex<Type>& right) {
        return operator-(left, right);  
    }

    friend 
    Complex<Type>
    operator-(const Type& left, Complex<Type>& right) {
        return Complex<Type>(left - right._real_part, right._imaginary_part);
    }

    friend 
    Complex<Type>
    operator-(Complex<Type>& left, const Type& right) {
        return Complex<Type>(left._real_part - right, left._imaginary_part);
    }

    friend 
    Complex<Type>
    operator-(Type&& left, Complex<Type>& right) {
        return operator-(left, right);
    }

    friend 
    Complex<Type>
    operator-(Complex<Type>& left, Type&& right) {
        return operator-(left, right);
    }
    
    friend 
    Complex<Type>
    operator-(Complex<Type>& left, Complex<Type>&& right) {
        return operator-(left, right);  
    }

    friend 
    Complex<Type>
    operator/(const Complex<Type>& left, const Type& value) {
        if(value == 0)
            return const_cast<Complex<Type>&>(left).copy();
        
        return Complex<Type>(left._real_part / value, left._imaginary_part / value);
    }

    friend 
    Complex<Type>
    operator/(const Complex<Type>& left, Type&& value) {
        return operator/(left, value);
    }
    
    friend 
    Complex<Type>
    operator/(const Type& left, const Complex<Type>& right) {
        auto _cast = const_cast<Complex<Type>&>(right).copy();

        if(Type _temp = _cast.norm(); _temp != 0)
            return left * (_cast.conjugate() / _cast.norm());

        return _cast.copy();
    }

    friend 
    Complex<Type>
    operator/(const Type& left, Complex<Type>&& right) {
        return operator/(left, right);
    }
    
    friend 
    Complex<Type>
    operator/(Type&& left, const Complex<Type>& right) {
        return operator/(left, right);
    }

    friend 
    Complex<Type>
    operator/(Type&& left, Complex<Type>&& right) {
        return operator/(left, right);
    }

    friend 
    Complex<Type>
    operator/(Complex<Type>& left, Complex<Type>& right) {
        if(Type div = (right._real_part * right._real_part) + (right._imaginary_part * right._imaginary_part);
            div != 0)
            return Complex<Type>(((left._real_part * right._real_part) + (left._imaginary_part * right._imaginary_part)) / div, 
                                    ((left._imaginary_part * right._real_part) - (left._real_part * right._imaginary_part)) / div);
        
        return left.copy();
    }

    friend 
    Complex<Type>
    operator/(Complex<Type>&& left, Complex<Type>&& right) {
        return operator/(left, right);
    }

    friend 
    Complex<Type>
    operator*(const Complex<Type>& left, const Type& value) {
        return Complex<Type>((left._real_part * value), (left._imaginary_part * value));
    }

    friend 
    Complex<Type>
    operator*(Complex<Type>& left, Complex<Type>& right) {
        return Complex<Type>((left._real_part * right._real_part) - (left._imaginary_part * right._imaginary_part), 
                             (left._real_part * right._imaginary_part) + (left._imaginary_part * right._real_part));
    }

    friend 
    Complex<Type>
    operator*(Complex<Type>&& left, Complex<Type>&& right) {
        return operator*(left, right);
    }

    friend 
    Complex<Type>
    operator*(Complex<Type>& left, Complex<Type>&& right) {
        return operator*(left, right);
    }

    friend 
    Complex<Type>
    operator*(Complex<Type>&& left, Complex<Type>& right) {
        return operator*(left, right);
    }

    friend 
    Complex<Type>
    operator*(Complex<Type>& left, Type&& value) {
        return operator*(left, value);
    }

    friend 
    Complex<Type>
    operator*(const Type& value, const Complex<Type>& right) {
        return operator*(right, value);
    }

    friend 
    Complex<Type>
    operator*(Type&& value, const Complex<Type>& right) {
        return operator*(right, idk::move(value));
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>& left, Complex<Type2>& right) noexcept {
        return ((left._real_part == right._real_part) && (left._imaginary_part == right._imaginary_part));
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>& left, Complex<Type2>&& right) noexcept {
        return operator==(left, right);
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>&& left, Complex<Type2>& right) noexcept {
        return operator==(left, right);
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>&& left, Complex<Type2>&& right) noexcept {
        return operator==(left, right);
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>&& left, const Type2& right) noexcept {
        return left.copy()._real_part == right;
    }
    
    template<typename Type2>
    friend bool 
    operator==(const Complex<Type>& left, const Type2& right) noexcept {
        return left.copy()._real_part == right;
    }

    template<typename Type2>
    friend bool 
    operator==(Complex<Type>&& left, Type2&& right) noexcept {
        return left.copy()._real_part == right;
    }

    template<typename Type2>
    friend bool 
    operator==(const Complex<Type>& left, Type2&& right) noexcept {
        return left.copy()._real_part == right;
    }

    template<typename Type2>
    friend bool 
    operator!=(const Complex<Type>& left, const Complex<Type2>& right) noexcept {
        return !operator==(left, right);
    }

    template<typename Type2>
    friend bool 
    operator!=(Complex<Type>& left, Complex<Type2>&& right) noexcept {
        return !operator==(left, idk::move(right));
    }

    template<typename Type2>
    friend bool 
    operator!=(Complex<Type>&& left, Complex<Type2>& right) noexcept {
        return !operator==(idk::move(left), right);
    }

    template<typename Type2>
    friend bool 
    operator!=(Complex<Type>&& left, Complex<Type2>&& right) noexcept {
        return !operator==(idk::move(left), idk::move(right));
    }

    template<typename Type2>
    friend bool 
    operator!=(const Complex<Type>& left, const Type2& right) noexcept {
        return !operator==(left, right);
    }

    template<typename Type2>
    friend bool 
    operator!=(Complex<Type>&& left, Type2&& right) noexcept {
        return !operator==(idk::move(left), idk::move(right));
    }

    template<typename Type2>
    friend bool 
    operator!=(const Complex<Type>& left, Type2&& right) noexcept {
        return !operator==(left, idk::move(right));
    }
};

using ComplexFloat32    = idk::Complex<idk::f32>;
using ComplexFloat64    = idk::Complex<idk::f64>;
using ComplexFloat80    = idk::Complex<idk::f80>;

__idk_nodiscard
ComplexFloat64
operator""_i(unsigned long long img) noexcept {
    return ComplexFloat64(0_f64, static_cast<idk::f64>(img));
}

__idk_nodiscard
ComplexFloat64
operator""_i_f64(unsigned long long img) noexcept {
    return ComplexFloat64(0_f64, static_cast<idk::f64>(img));
}
    
__idk_nodiscard
ComplexFloat32
operator""_if(unsigned long long img) noexcept {
    return ComplexFloat32(0_f32, static_cast<idk::f32>(img));
}

__idk_nodiscard
ComplexFloat32
operator""_i_f32(unsigned long long img) noexcept {
    return ComplexFloat32(0_f32, static_cast<idk::f32>(img));
}

__idk_nodiscard
ComplexFloat80
operator""_il(unsigned long long img) noexcept {
    return ComplexFloat80(0_f80, static_cast<idk::f80>(img));
}

__idk_nodiscard
ComplexFloat80
operator""_i_f80(unsigned long long img) noexcept {
    return ComplexFloat80(0_f80, static_cast<idk::f80>(img));
}
} // namespace idk