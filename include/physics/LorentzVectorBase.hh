// Author: Pasha Murat , Peter Malzacher  12/02/99
// Jan Hajer 2015

/*************************************************************************
 * Copyright(C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#pragma once

#include "Vector3.hh"

namespace boca
{

/**
 * @brief Copy of root::TLorentzVector in order to get rid of TObject which makes it unsuitable for heavy usage
 *
 */
template<typename Value>
class LorentzVectorBase
{

public:

    using ValueSqr = boca::ValueProduct<Value, Value>;

    template<typename Value_2>
    using ValueProduct = boca::ValueProduct<Value, Value_2>;

    template <typename> struct IsQuantity : std::false_type {};
    template <typename T> struct IsQuantity<boost::units::quantity<T>> : std::true_type {};

    template<typename Value_2>
    using OnlyIfNotOrSameQuantity = typename std::enable_if < !IsQuantity<Value_2>::value || std::is_same<Value, Value_2>::value >::type;

    template<typename Value_2>
    using OnlyIfNotQuantity = typename std::enable_if < !IsQuantity<Value_2>::value >::type;

// Safe indexing of the coordinates when using with matrices, arrays, etc.
    enum { kX = 0, kY = 1, kZ = 2, kT = 3, kNUM_COORDINATES = 4, kSIZE = kNUM_COORDINATES };

    LorentzVectorBase() : vector_3_(), scalar_(Value(0)) {}

// Constructor giving the components x, y, z, t.
    LorentzVectorBase(Value x, Value y, Value z, Value t) : vector_3_(x, y, z), scalar_(t) {}

// Constructor giving a 3-Vector and a time component.
    LorentzVectorBase(Vector3<Value> vector3, Value t) : vector_3_(std::move(vector3)), scalar_(t) {}

// Get position and time.
    Value X() const {
        return vector_3_.X();
    }
    Value Y() const {
        return vector_3_.Y();
    }
    Value Z() const {
        return vector_3_.Z();
    }
    Value T() const {
        return scalar_;
    }

// Set position and time.
    void SetX(Value a) {
        vector_3_.SetX(a);
    }
    void SetY(Value a) {
        vector_3_.SetY(a);
    }
    void SetZ(Value a) {
        vector_3_.SetZ(a);
    }
    void SetT(Value a) {
        scalar_ = a;
    }

// Get spatial component.
    Vector3<Value> Vect() const {
        return vector_3_;
    }

// Set spatial component.
    void SetVect(Vector3<Value> const& vector) {
        vector_3_ = vector;
    }

// Get spatial vector components in spherical coordinate system.
    boca::Angle Theta() const {
        return vector_3_.Theta();
    }
    Value CosTheta() const {
        return vector_3_.CosTheta();
    }
    //returns phi from -pi to pi
    boca::Angle Phi() const {
        return vector_3_.Phi();
    }
    Value Rho() const {
        return vector_3_.Mag();
    }

// Set spatial vector components in spherical coordinate system.
    void SetTheta(boca::Angle theta) {
        vector_3_.SetTheta(theta);
    }
    void SetPhi(boca::Angle phi) {
        vector_3_.SetPhi(phi);
    }
    void SetRho(Value rho) {
        vector_3_.SetMag(rho);
    }

// Setters to provide the functionality(but a more meanigful name) of
// the previous version eg SetV4... PsetV4...
    void SetXYZT(Value x, Value y, Value z, Value t) {
        vector_3_.SetXYZ(x, y, z);
        SetT(t);
    }

    void SetXYZM(Value x, Value y, Value z, Value m) {
        if (m >= Value(0)) SetXYZT(x, y, z, sqrt(sqr(x) + sqr(y) + sqr(z) + sqr(m)));
        else SetXYZT(x, y, z, sqrt(std::max((sqr(x) + sqr(y) + sqr(z) - sqr(m)), ValueSqr(0))));
    }

// Getters into an arry
// no checking!
//     void GetXYZT(Value* carray) const;

// Get components by index.
    Value operator()(int i) const {
        //dereferencing operatorconst
        switch (i) {
        case kX:
        case kY:
        case kZ: return vector_3_(i);
        case kT: return scalar_;
        default: std::cout << "bad index(%d) returning 0 " << i << std::endl;
        }
        return 0.;
    }
    Value operator[](int i) const {
        return (*this)(i);
    }

// Set components by index.
    Value& operator()(int i) {
        //dereferencing operator
        switch (i) {
        case kX:
        case kY:
        case kZ: return vector_3_(i);
        case kT: return scalar_;
        default:  std::cout << "bad index(%d) returning &e_ " << i << std::endl;
        }
        return scalar_;
    }
    Value& operator[](int i) {
        return (*this)(i);
    }

    // Additions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator+(const LorentzVectorBase<Value_2>& lorentz_vector) const {
        return {vector_3_ + lorentz_vector.Vect(), scalar_ + lorentz_vector.T()};
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator+=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ += lorentz_vector.Vect();
        scalar_ += lorentz_vector.T();
        return *this;
    }

    // Subtractions.
    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase operator-(LorentzVectorBase<Value_2> const& lorentz_vector) const {
        return {vector_3_ - lorentz_vector.Vect(), scalar_ - lorentz_vector.T()};
    }

    template <typename Value_2, typename = OnlyIfNotOrSameQuantity<Value_2>>
    LorentzVectorBase& operator-=(LorentzVectorBase<Value_2> const& lorentz_vector) {
        vector_3_ -= lorentz_vector.Vect();
        scalar_ -= lorentz_vector.T();
        return *this;
    }

// Unary minus.
    LorentzVectorBase operator-() const {
        return { -X(), -Y(), -Z(), -T()};
    }

// Scaling with real numbers.
//     LorentzVectorBase operator*(Value a) const {
//         return {a * X(), a * Y(), a * Z(), a * T()};
//     }

    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase& operator*=(Value_2 a) {
        vector_3_ *= a;
        scalar_ *= a;
        return *this;
    }

    template <typename Value_2, typename = OnlyIfNotQuantity<Value_2>>
    LorentzVectorBase& operator/=(Value_2 a) {
      vector_3_ /= a;
      scalar_ /= a;
      return *this;
    }

// Comparisons.
    bool operator==(LorentzVectorBase const& lorentz_vector) const {
        return Vect() == lorentz_vector.Vect() && T() == lorentz_vector.T();
    }
    bool operator!=(LorentzVectorBase const& lorentz_vector) const {
        return Vect() != lorentz_vector.Vect() || T() != lorentz_vector.T();
    }

// Transverse component of the spatial vector squared.
    ValueSqr Perp2() const {
        return vector_3_.Perp2();
    }

    Value Perp() const {
        return vector_3_.Perp();
    }

// Set the transverse component of the spatial vector.
    void SetPerp(Value perp) {
        vector_3_.SetPerp(perp);
    }

// Transverse component of the spatial vector w.r.t. given axis squared.
    ValueSqr Perp2(Vector3<Value> const& vector) const {
        return vector_3_.Perp2(vector);
    }

    Value Perp(Vector3<Value> const& vector) const {
        return vector_3_.Perp(vector);
    }

    boca::Angle DeltaPhi(LorentzVectorBase const& lorentz_vector) const {
        return RestrictPhi(Phi() - lorentz_vector.Phi());
    }

    boca::Angle DeltaR(LorentzVectorBase const& lorentz_vector) const {
        boca::Angle deta = Eta() - lorentz_vector.Eta();
        boca::Angle dphi = RestrictPhi(Phi() - lorentz_vector.Phi());
        return sqrt(sqr(deta) + sqr(dphi));
    }

    boca::Angle DrEtaPhi(LorentzVectorBase const& lorentz_vector) const {
        return DeltaR(lorentz_vector);
    }

    Vector2<boca::Angle> EtaPhiVector() {
        return {Eta(), Phi()};
    }

// Angle wrt. another vector.
    Value Angle(Vector3<Value> const& vector) const {
        return vector_3_.Angle(vector);
    }

// Invariant mass squared.
    ValueSqr Mag2() const {
        return sqr(T()) - vector_3_.Mag2();
    }
// Invariant mass. If mag2() is negative then -sqrt(-mag2()) is returned.
    Value Mag() const {
        ValueSqr mm = Mag2();
        return mm < ValueSqr(0) ? -sqrt(-mm) : sqrt(mm);
    }

    double Beta() const {
        return vector_3_.Mag() / scalar_;
    }

    double Gamma() const {
        double beta = Beta();
        return 1. / std::sqrt(1. - sqr(beta));
    }

    // Scalar product.
    template <typename Value_2>
    ValueProduct<Value_2> Dot(LorentzVectorBase<Value_2> const& lorentz_vector) const {
        return T() * lorentz_vector.T() - Z() * lorentz_vector.Z() - Y() * lorentz_vector.Y() - X() * lorentz_vector.X();
    }

//     ValueSqr operator*(LorentzVectorBase const& q) const {
//         return Dot(q);
//     }

// Copy spatial coordinates, and set energy = sqrt(mass^2 + spatial^2)
    void SetVectMag(Vector3<Value> const& spatial, Value magnitude) {
        SetXYZM(spatial.X(), spatial.Y(), spatial.Z(), magnitude);
    }

    void SetVectM(Vector3<Value> const& spatial, Value mass) {
        SetVectMag(spatial, mass);
    }

// Returns t +/- z.
// Related to the positive/negative light-cone component,
// which some define this way and others define as(t +/- z)/sqrt(2)
//Member functions Plus() and Minus() return the positive and negative
//light-cone components:
//
// Value pcone = v.Plus();
// Value mcone = v.Minus();
//
//CAVEAT: The values returned are T{+,-}Z. It is known that some authors
//find it easier to define these components as(T{+,-}Z)/sqrt(2). Thus
//check what definition is used in the physics you're working in and adapt
//your code accordingly.
    Value Plus() const {
        return T() + Z();
    }
    Value Minus() const {
        return T() - Z();
    }

// Returns the spatial components divided by the time component.
    Vector3<Value> BoostVector() const {
        return {X() / T(), Y() / T(), Z() / T()};
    }

// Lorentz boost.
    void Boost(Value bx, Value by, Value bz) {
        //Boost this Lorentz vector
        ValueSqr b2 = bx * bx + by * by + bz * bz;
        Value gamma = 1.0 / std::sqrt(1.0 - b2);
        ValueSqr bp = bx * X() + by * Y() + bz * Z();
        Value gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;
        SetX(X() + gamma2 * bp * bx + gamma * bx * T());
        SetY(Y() + gamma2 * bp * by + gamma * by * T());
        SetZ(Z() + gamma2 * bp * bz + gamma * bz * T());
        SetT(gamma * (T() + bp));
    }
    void Boost(Vector3<Value> const& b) {
        Boost(b.X(), b.Y(), b.Z());
    }

// Returns the rapidity, i.e. 0.5*ln((E+pz)/(E-pz))
    boca::Angle Rapidity() const {
        //return rapidity
        return 0.5_rad * std::log((T() + Z()) / (T() - Z()));
    }

// Returns the pseudo-rapidity, i.e. -ln(tan(theta/2))
    boca::Angle Eta() const {
        return PseudoRapidity();
    }

    boca::Angle PseudoRapidity() const {
        return vector_3_.PseudoRapidity();
    }

// Rotate the spatial component around the x-axis.
    void RotateX(Value angle) {
        vector_3_.RotateX(angle);
    }

// Rotate the spatial component around the y-axis.
    void RotateY(Value angle) {
        vector_3_.RotateY(angle);
    }

// Rotate the spatial component around the z-axis.
    void RotateZ(Value angle) {
        vector_3_.RotateZ(angle);
    }

// Rotates the reference frame from Uz to newUz(unit vector).
    void RotateUz(Vector3<Value>& newUzVector) {
        vector_3_.RotateUz(newUzVector);
    }

protected:

    // 3 vector component
    Vector3<Value> vector_3_;

    // time or energy of(x,y,z,t) or(px,py,pz,e)
    Value scalar_;

};

template <typename>
struct IsLorentzVectorBase : std::false_type {};

template <typename Value>
struct IsLorentzVectorBase<LorentzVectorBase<Value>> : std::true_type {};

template<typename Value>
using OnlyIfNotLorentzVectorBase = typename std::enable_if < !IsLorentzVectorBase<Value>::value >::type;

// Scalar product of lorentzvectors.
template <class Value, class Value_2>
ValueProduct<Value, Value_2> operator*(LorentzVectorBase<Value> const& vector_1, LorentzVectorBase<Value_2> const& vector_2)
{
    return vector_1.Dot(vector_2);
}

// Scaling of lorentzvectors with a real number
template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value_2> >
LorentzVectorBase <ValueProduct<Value, Value_2>> operator*(LorentzVectorBase<Value> const& vector, Value_2 scalar)
{
    return {scalar * vector.X(), scalar * vector.Y(), scalar * vector.Z(), scalar * vector.T()};
}

template < class Value, class Value_2, typename = OnlyIfNotLorentzVectorBase<Value_2> >
LorentzVectorBase <ValueProduct<Value, Value_2>> operator*(Value_2 scalar, LorentzVectorBase<Value> const& vector)
{
    return {scalar * vector.X(), scalar * vector.Y(), scalar * vector.Z(), scalar * vector.T()};
}

}

