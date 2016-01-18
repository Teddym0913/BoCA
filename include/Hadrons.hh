/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Types.hh"
#include "FourVector.hh"
#include "Jet.hh"

namespace boca
{

/**
 * @brief Base class for jets
 *
 */
class Hadrons : public FourVector
{

public:

    Hadrons(boca::TreeReader const& tree_reader);

    virtual ~Hadrons() {};

    virtual std::vector<Jet> Jets() const = 0;

    virtual Momentum ScalarHt() const;

    virtual boca::MissingEt MissingEt() const;

protected:

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1& particle_1, const Particle_2& particle_2, Angle delta_r_isolation_max) const {
        bool isolated = false;
        if (boca::PseudoJet(const_cast<Particle_1&>(particle_1).P4()).DeltaRTo(boca::PseudoJet(const_cast<Particle_2&>(particle_2).P4())) < delta_r_isolation_max) isolated = true;
        return isolated;
    }

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1& particle_1, const Particle_2& particle_2) const {
        Angle delta_r_isolation_max = 0_rad; // TODO decide on best value
        return CheckIsolation(particle_1, particle_2, delta_r_isolation_max);
    }

};

}
