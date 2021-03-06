// @(#)root/physics:$Id$
// Author: Pasha Murat   12/02/99
// Jan Hajer 2015  make the class templated and compatible with boost units

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include <iostream>
#include "generic/Iterator.hh"
#include "math/GradedContainer.hh"
#include "physics/Units.hh"

namespace boca
{

enum class Dim2
{
    x,
    y,
    last
};

std::string Name(Dim2 dimension);

std::vector<Dim2> Dimensions2();

/**
 * @brief Copy of root::TVector2 in order to get rid of TObject
 *
 */
template<typename Value>
class Vector2
{
public:

    template<typename Value_2>
    using ValueProduct = ValueProduct<Value, Value_2>;

    template<typename Value_2>
    using ValueQuotient = ValueQuotient<Value, Value_2>;

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfQuantity = typename std::enable_if < IsQuantity<Value_2>::value>::type;

    /// Constructor
    Vector2() {
        x_ = 0;
        y_ = 0;
    }

    /// Constructor
    Vector2(Value x, Value y) {
        x_ = x;
        y_ = y;
    }

    /// Constructor
    template<typename Value_2, typename = OnlyIfQuantity<Value_2>>
    Vector2(Vector2<Value_2> const& vector) {
        x_ = Value(vector.X());
        y_ = Value(vector.Y());
    }

    /// Set vector
    void Set(Vector2 const& vector) {
        x_ = vector.X();
        y_ = vector.Y();
    }

    /// Set x and y
    void Set(Value x, Value y) {
        x_ = x ;
        y_ = y ;
    }

    /// Set x
    void SetX(Value x) {
        x_ = x;
    }

    /// Set y
    void SetY(Value y) {
        y_ = y;
    }

    /// Set vector using mag and phi
    void SetMagPhi(Value magnitude, Angle const& phi) {
        auto absolute = abs(magnitude, IsQuantity<Value>());
        x_ = absolute * boost::units::cos(phi);
        y_ = absolute * boost::units::sin(phi);
    }

    Value const& X() const {
        return x_;
    }

    Value const& Y() const {
        return y_;
    }

    Value& X() {
        return x_;
    }

    Value& Y() {
        return y_;
    }

    ValueProduct<Value> Mod2() const {
        return sqr(x_) + sqr(y_);
    }

    /// return modulo of this vector
    Value Mod() const {
        return sqrt(Mod2());
    }

/// return vector phi defined in [-pi, pi]
    Angle Phi() const {
        return atan2(-y_, -x_);
    }

    template<typename Value_2>
    Angle DeltaPhi(Vector2<Value_2> const& vector) const {
        return RestrictPhi(Phi() - vector.Phi());
    }

    /// unit vector in the direction of *this
    /// return module normalized to 1
    Vector2<double> Unit() const {
        return Mod2() ? *this / Mod() : Vector2<double>();
    }

    Vector2<double> Ort() const {
        return Unit();
    }

    /// projection of *this to the direction of Vector2 vector `v'
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 Proj(Vector2<Value_2> const& vector) const {
        return vector * (*this * vector / vector.Mod2());
    }

    // component of *this normal to `v'
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2 Norm(Vector2<Value_2> const& vector) const {
        return *this - Proj(vector);
    }

    // rotates 2-vector by phi radians
    Vector2 Rotate(Angle const& phi) const {
        return {x_* boost::units::cos(phi) - y_* boost::units::sin(phi), x_* boost::units::sin(phi) + y_* boost::units::cos(phi)};
    }

    // Scalar product
    template <typename Value_2>
    ValueProduct<Value_2> Dot(Vector2<Value_2> const& vector) const {
        return x_ * vector.X() + y_ * vector.Y();
    }

    // scale with scalar
    template <typename Value_2>
    Vector2 <ValueProduct<Value_2>> Scale(Value_2 const& scalar) const {
        return {X()* scalar, Y()* scalar};
    }

    // signed area
    template <typename Value_2>
    ValueProduct<Value_2> SignedArea(Vector2<Value_2> const& vector) const {
        return X() * vector.Y() - Y() * vector.X();
    }

    // assignment operator including casting
    template <typename Value_2, typename = OnlyIfQuantity<Value_2>>
    Vector2& operator=(Vector2<Value_2> const& vector) {
        x_ = Value(vector.X());
        y_ = Value(vector.Y());
        return *this;
    }

    /// vector sum
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2& operator+=(Vector2<Value_2> const& vector) {
        x_ += vector.x_;
        y_ += vector.y_;
        return *this;
    }

    /// vector difference
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    Vector2& operator-=(Vector2<Value_2> const& vector) {
        x_ -= vector.x_;
        y_ -= vector.y_;
        return *this;
    }

    /// product with scalar
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2& operator*=(Value_2 scalar) {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    /// division by scalar
    template < typename Value_2, typename = OnlyIfNotQuantity<Value_2> >
    Vector2& operator/=(Value_2 scalar) {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    /// vector sum
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector2<Value> operator+(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return {vector_1.X() + vector_2.X(), vector_1.Y() + vector_2.Y()};
    }

    /// vector difference
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    friend Vector2 operator-(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return {vector_1.X() - vector_2.X(), vector_1.Y() - vector_2.Y()};
    }

    template<typename Value_2>
    friend ValueProduct<Value_2> operator^(Vector2 const& vector_1, Vector2<Value_2> const& vector_2) {
        return vector_1.SignedArea(vector_2);
    }

    template <typename Value_2>
    friend auto operator/(Vector2 const& vector, Value_2 const& scalar) {
        return vector.Scale(1. / scalar);
    }

    // Unary minus
    Vector2 operator-() const {
        return { -x_, -y_};
    }

    // Comparisons
    bool operator==(Vector2 const& vector) const {
        return vector.x_ == x_ && vector.y_ == y_;
    }

    bool operator!=(Vector2 const& vector) const {
        return vector.x_ != x_ || vector.y_ != y_ ;
    }

    // Get components by index
    Value operator()(Dim2 dimension) const {
        //dereferencing operator const
        switch (dimension) {
        case Dim2::x : return x_;
        case Dim2::y : return y_;
        default : std::cout << "bad index(%d) returning 0 " << Name(dimension) << std::endl;
            return 0;
        }
    }

    Value operator[](Dim2 dimension) const {
        return operator()(dimension);
    }

    // Set components by index.
    Value& operator()(Dim2 dimension) {
        //dereferencing operator
        switch (dimension) {
        case Dim2::x : return x_;
        case Dim2::y : return y_;
        default : std::cout << "bad index(%d) returning &x_" <<  Name(dimension) << std::endl;
        }
        return x_;
    }

    Value& operator[](Dim2 dimension) {
        return operator()(dimension);
    }

    ConstIterator<boca::Vector2, Value, Dim2> begin() const {
        return {this, Dim2::x};
    }

    ConstIterator<boca::Vector2, Value, Dim2> end() const {
        return {this, Dim2::last};
    }

    Iterator<boca::Vector2, Value, Dim2> begin() {
        return {this, Dim2::x}; //0
    }

    Iterator<boca::Vector2, Value, Dim2> end() {
        return {this, Dim2::last}; //0
    }

private:

    Value x_;

    Value y_;
};

template <typename>
struct IsVector2 : std::false_type {};

template <typename Value>
struct IsVector2<Vector2<Value>> : std::true_type {};

template<typename Value>
using OnlyIfNotVector2 = typename std::enable_if < !IsVector2<Value>::value >::type;

template <class Value, class Value_2>
auto operator*(Vector2<Value> const& vector_1, const Vector2<Value_2>& vector_2)
{
    return vector_1.Dot(vector_2);
}

template < class Value, class Value_2, typename = OnlyIfNotVector2<Value_2> >
auto operator*(Vector2<Value> const& vector, Value_2 const& scalar)
{
    return vector.Scale(scalar);
}

template < class Value, class Value_2, typename = OnlyIfNotVector2<Value> >
auto operator*(Value const& scalar, Vector2<Value_2> const& vector)
{
    return vector.Scale(scalar);
}

template<typename Value_>
using GradedVector2 = GradedContainer<Vector2, Value_>;

}

