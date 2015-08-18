/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "JetInfo.hh"
#include "MultipletBase.hh"

namespace boca
{

/**
 * @brief Thin wrapper to make fastjet::PseudoJet behave like a Multiplet. Additionally this class astracts away the JetInfo user_info().
 *
 */
class Singlet : public MultipletBase
{

public:

    Singlet() {};

    Singlet(fastjet::PseudoJet const& jet);

    fastjet::PseudoJet Jet() const {
        return jet_;
    }

    boca::Jets Jets() const {
        return {Jet()};
    }

    bool Overlap(fastjet::PseudoJet const& jet) const;

    bool Overlap(Singlet const& singlet) const;

    float VertexMass() const {
        return UserInfo().VertexMass();
    }

    float MaxDisplacement() const {
        return log(UserInfo().MaxDisplacement());
    }

    float MeanDisplacement() const {
        return log(UserInfo().MeanDisplacement());
    }

    float SumDisplacement() const {
        return log(UserInfo().SumDisplacement());
    }

    float Multiplicity() const {
        return UserInfo().VertexNumber();
    }

    float Radius() const {
        return Radius(Jet());
    }

    float Spread() const {
        return Spread(Jet());
    }

    float VertexRadius() const {
        return Radius(UserInfo().VertexJet());
    }

    float VertexSpread() const {
        return Spread(UserInfo().VertexJet());
    }

    float EnergyFraction() const {
        return UserInfo().VertexEnergy() / Jet().e();
    }

    float EmRadius() const {
        return UserInfo().ElectroMagneticRadius(Jet());
    }

    float TrackRadius() const {
        return UserInfo().TrackRadius(Jet());
    }

    float MomentumFraction() const {
        return UserInfo().LeadingTrackMomentumFraction();
    }

    float CoreEnergyFraction() const {
        return UserInfo().CoreEnergyFraction(Jet());
    }

    float EmFraction() const {
        return UserInfo().ElectroMagneticFraction();
    }

    float ClusterMass() const {
        return UserInfo().ClusterMass();
    }

    float TrackMass() const {
        return UserInfo().TrackMass();
    }

    float FlightPath() const {
        return log(UserInfo().MeanDisplacement());
    }

    float TrtHtFraction() const {
        return Spread(UserInfo().VertexJet());
    }

    boca::Tag Tag() const {
        return UserInfo().Tag();
    }

    float Bdt() const final {
        if(UserInfo().Bdt() != initial_value()) return UserInfo().Bdt();
        return 0;
    }

    float Ht() const {
        return Jet().pt();
    }

    void SetBdt(float bdt) final;

    float Rapidity() const;

    int Charge() const;

    Singlet const& singlet() const;

    JetInfo const& UserInfo() const;

    Vector2 Pull() const;

    fastjet::PseudoJet& Jet() {
        return jet_;
    }

    float BottomBdt() const final {
      return Bdt();
    }

private:

    float log(float number) const;

    float Radius(fastjet::PseudoJet const& jet) const;

    float Spread(fastjet::PseudoJet const& jet) const;

    fastjet::PseudoJet jet_;

    JetInfo jet_info_;

};


}

