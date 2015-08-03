#pragma once

#include "Triplet.hh"

namespace analysis {

class Quartet22 : public TwoBody<Doublet, Doublet> {

public:

    using TwoBody<Doublet, Doublet>::TwoBody;

    const Doublet& Doublet1() const;

    const Doublet& Doublet2() const;

    Doublet& Doublet1();

    Doublet& Doublet2();

};

class Quartet31 : public TwoBody<analysis::Triplet, analysis::Singlet> {

public:

    using TwoBody<analysis::Triplet, analysis::Singlet>::TwoBody;

    const analysis::Triplet& Triplet() const;

    const analysis::Singlet& Singlet() const;

};

}