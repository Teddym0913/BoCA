#pragma once

#include "Septet.hh"
#include "multiplets/Octet.hh"

namespace boca
{

namespace naturalness
{

class Decuplet55 : public TwoBody<Quintet, Quintet>
{

public:

    using TwoBody<Quintet, Quintet>::TwoBody;

    Quintet const& Quintet1() const {
        return Multiplet1();
    }

    Quintet const& Quintet2() const {
        return Multiplet2();
    }

};

class Decuplet73 : public TwoBody<boca::naturalness::Septet, boca::Triplet>
{

public:

    using TwoBody<boca::naturalness::Septet, boca::Triplet>::TwoBody;

    boca::naturalness::Septet const& Septet() const {
        return Multiplet1();
    }

    boca::Triplet const& Triplet() const {
        return Multiplet2();
    }

};

class Decuplet82 : public TwoBody<Octet53, boca::Doublet>
{

public:

    using TwoBody<Octet53, boca::Doublet>::TwoBody;

    Octet53 const& Octet() const {
        return Multiplet1();
    }

    boca::Doublet const& Doublet() const {
        return Multiplet2();
    }

};

class Decuplet532 : public ThreeBody<boca::Quintet, boca::Triplet, boca::Doublet>
{

public:

    using ThreeBody<boca::Quintet, boca::Triplet, boca::Doublet>::ThreeBody;

    boca::Quintet const& Quintet() const {
        return Multiplet1();
    }

    boca::Triplet const& Triplet() const {
        return Multiplet2();
    }

    boca::Doublet const& Doublet() const {
        return Multiplet3();
    }

};

}

}




