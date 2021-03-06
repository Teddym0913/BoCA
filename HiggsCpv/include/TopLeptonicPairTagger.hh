#pragma once

#include "TopLeptonicTagger.hh"
#include "multiplets/Sextet.hh"
#include "BranchesHiggsCpv.hh"

namespace boca
{

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopLeptonicPairTagger : public TaggerTemplate<Sextet, TopLeptonicPairBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<Sextet> Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector<Sextet> TruthLevel(boca::Event const& event, std::vector< boca::Sextet > sextets, Tag tag) const;

private:

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
