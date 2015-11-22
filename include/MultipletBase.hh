/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "Vector2.hh"
#include "Jet.hh"
#include "Particle.hh"
#include "Units.hh"

namespace boca {

class MultipletBase : public Identification {

public:

  virtual MultipletBase const& singlet() const = 0;

  virtual boca::Jet Jet() const = 0;

  virtual Vector2<float> Pull() const = 0;

  virtual float Ht() const = 0;

  virtual int Charge() const = 0;

  virtual float BottomBdt() const = 0;

  boca::Mass Mass() const {
    return Jet().Mass();
  }

  Momentum Pt() const {
    return Jet().Pt();
  }

  Angle Rap() const {
    return Jet().Rap();
  }

  Angle Phi() const {
    return Jet().Phi();
  }

  Angle DeltaRTo(boca::Jet const& jet) const {
    return Jet().DeltaRTo(jet);
  }

  Angle DeltaRTo(boca::Particle const& jet) const {
    return Jet().DeltaRTo(jet);
  }

  /**
   * @brief calculate Reference vector for other - this
   * @return Vector2<float> reference vector
   *
   */
  Vector2<double> Reference(boca::Jet const& jet) const
  {
    return {jet.rap() - Jet().rap(), Jet().delta_phi_to(jet)};
  }

};

}
