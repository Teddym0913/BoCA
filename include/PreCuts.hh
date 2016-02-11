/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Jet.hh"
#include "physics/Range.hh"

#include "PreCut.hh"

namespace boca
{

enum class Bosstness
{
    unboosted,
};

class PreCuts
{

public:

    template <typename Multiplet>
    bool PtTooSmall(Id id, Multiplet const& multiplet) const {
      return pt_lower_cut_.TooSmall(id, multiplet.Pt());
    }

    template <typename Multiplet>
    bool PtTooLarge(Id id, Multiplet const& multiplet) const {
        return pt_upper_cut_.TooLarge(id, multiplet.Pt());
    }

    template <typename Multiplet>
    bool MassTooSmall(Id id, Multiplet const& multiplet) const {
      return mass_lower_cut_.TooSmall(id, multiplet.Mass());
    }

    template <typename Multiplet>
    bool MassTooLarge(Id id, Multiplet const& multiplet) const {
      return mass_upper_cut_.TooLarge(id, multiplet.Mass());
    }

    template <typename Multiplet>
    bool OutsideTracker(Id id, Multiplet const& multiplet) const {
      return tracker_eta_upper_cut_.TooLarge(id, boost::units::abs(multiplet.Rap()));
    }

    template <typename>
    struct IsVector : std::false_type {};

    template <typename Value>
    struct IsVector<std::vector<Value>> : std::true_type {};

    template<typename Value>
    using OnlyIfNotVector = typename std::enable_if < !IsVector<Value>::value >::type;

    template <typename Multiplet>
    std::vector<Multiplet> ApplyCuts(Id id, std::vector<Multiplet> const& multiplets) const {
        std::vector<Multiplet> good;
        for (auto const & multiplet : multiplets) if (!ApplyCuts(id, multiplet)) good.emplace_back(multiplet);
        return good;
    }

    template <typename Multiplet, typename = OnlyIfNotVector<Multiplet>>
    bool ApplyCuts(Id id, Multiplet const& multiplet) const {
        return PtTooSmall(id, multiplet) || PtTooLarge(id, multiplet) || MassTooSmall(id, multiplet) || MassTooLarge(id, multiplet) || OutsideTracker(id, multiplet);
    }

    bool DoSubJets(Id id) const;

    bool SemiLeptonic() const;

    void SetSemiLeptonic(bool semi_leptonic);

    template <typename Multiplet>
    bool NotParticleRho(Multiplet const& multiplet, Range<float> range = Range<float>(0.5, 2)) const {
        return multiplet.Rho() > 0 && (multiplet.Rho() < range.Min() || multiplet.Rho() > range.Max());
    }

    template<typename Multiplet>
    bool OutSideMassWindow(Multiplet const& multiplet, Mass mass_window, Id id) const {
        return boost::units::abs(multiplet.Mass() - MassOf(id)) > mass_window;
    }

    Angle JetConeMax(Id id) const;

    PreCut<Momentum>& PtLowerCut();

    PreCut<Momentum>& PtUpperCut();

    PreCut<Mass>& MassLowerCut();

    PreCut<Mass>& MassUpperCut();

    PreCut<Angle>& TrackerMaxEta();

    PreCut<bool>& ConsiderBuildingBlock();

    PreCut<Momentum> const& PtLowerCut() const;

    PreCut<Momentum> const& PtUpperCut() const;

    PreCut<Mass> const& MassLowerCut() const;

    PreCut<Mass> const& MassUpperCut() const;

    PreCut<Angle> const& TrackerMaxEta() const;

    PreCut<bool> const& ConsiderBuildingBlock() const;

private:

    PreCut<Momentum> pt_lower_cut_;

    PreCut<Momentum> pt_upper_cut_;

    PreCut<Mass> mass_lower_cut_;

    PreCut<Mass> mass_upper_cut_;

    PreCut<Angle> tracker_eta_upper_cut_;

    PreCut<bool> consider_building_block_;

    bool semi_leptonic_ = true;

};

}
