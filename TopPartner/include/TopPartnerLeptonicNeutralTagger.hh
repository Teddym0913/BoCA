#pragma once

#include "TopLeptonicTagger.hh"
#include "BosonTagger.hh"
#include "multiplets/Quintet.hh"
#include "BranchesTopPartner.hh"

namespace boca
{

namespace naturalness
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerLeptonicNeutralTagger : public TaggerTemplate<Quintet, TopPartnerBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

    std::vector<Particle> Particles(Event const& event, Tag tag = Tag::signal) const;

private:

    std::vector<Quintet> Quintets(Event const& event, std::function<Quintet(Quintet&)> const& function);

    Reader<standardmodel::TopLeptonicTagger> top_reader_;

    Reader<standardmodel::BosonTagger> boson_reader_;
};

}

}
