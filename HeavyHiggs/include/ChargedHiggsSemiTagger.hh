#pragma once

#include "TopLeptonicTagger.hh"
#include "multiplets/Quartet.hh"
#include "BranchesHeavyHiggs.hh"

namespace boca
{

namespace heavyhiggs
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsSemiTagger : public TaggerTemplate<Quartet31, ChargedHiggsSemiBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Quartet31> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

    Reader<standardmodel::TopLeptonicTagger> top_leptonic_reader_;
};

}

}
