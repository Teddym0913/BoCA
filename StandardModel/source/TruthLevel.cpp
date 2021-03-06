/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TruthLevel.hh"

#include "Event.hh"
#include "PreCuts.hh"
#include "generic/Exception.hh"
#include "multiplets/Particles.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

namespace standardmodel
{


int TruthLevel::Train(Event const& event, PreCuts const& pre_cuts, Tag)
{
    INFO0;
    return SaveEntries(Jets(event, pre_cuts, [&](Particle & jet) {
//         if (Problematic(jet, pre_cuts, tag)) throw boca::Problematic();
        return jet;
    }));
}



std::vector<TruthVariables> TruthLevel::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const&)
{
    INFO0;
    return Jets(event, pre_cuts, [&](Particle & jet) {
//         if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return jet;
    });
}

std::vector<TruthVariables> TruthLevel::Jets(Event const& event, PreCuts const& pre_cuts, std::function<Particle(Particle&)> const&)const
{
    INFO0;
    auto particle = event.Partons().GenParticles();
    auto tops = CopyIfParticle(particle, Id::top);
    CHECK(tops.size() == 2, tops.size());
    std::vector<TruthVariables> truths;
    for (auto const & top : tops) {
        if (top.Pt() < pre_cuts.PtLowerCut().Get(Id::top) || top.Pt() > pre_cuts.PtUpperCut().Get(Id::top)) continue;
        TruthVariables truth;
        truth.SetTop(top);
        auto bottoms = CopyIfMother(CopyIfParticle(particle, Id::bottom), top);
        CHECK(bottoms.size() == 1, bottoms.size());
        truth.SetBottom(bottoms.front());
        auto Ws = CopyIfMother(CopyIfParticle(particle, Id::W), top);
        CHECK(Ws.size() == 1, Ws.size());
        truth.SetW(Ws.front());
        auto quarks = CopyIfGrandMother(CopyIfQuark(particle), top);
        CHECK(quarks.size() == 2, quarks.size());
        truth.SetQuark1(quarks.at(0));
        truth.SetQuark2(quarks.at(1));
        truths.emplace_back(truth);
    }
    return truths;
}


std::string TruthLevel::Name() const
{
    return "Truth";
}

std::string TruthLevel::LatexName() const
{
    return "truth";
}

}

}

