#pragma once

#include "Multiplet.hh"
#include "Singlet.hh"
#include "TVector2.h"

namespace analysis {

class Doublet : public Multiplet<Singlet, Singlet> {

public:

    using Multiplet<Singlet, Singlet>::Multiplet;

    Singlet& Singlet1() const;

    Singlet& Singlet2() const;

    float PullDifference() const;

    float PullSum() const;

    float Dipolarity() const;

private:

    float Pull1() const;

    float Pull2() const;

};

}
