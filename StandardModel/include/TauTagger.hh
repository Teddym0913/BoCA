/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "BranchesSm.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Singlet.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for tau leptons
 *
 */
class TauTagger : public TaggerTemplate<Singlet, TauBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Singlet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

  std::vector<Jet> CleanJets(std::vector<Jet>& jets, std::vector<Particle> const& Particles, Tag tag) const;

};

}

}
