#pragma once

#include "multiplets/Octet.hh"
#include "TopPartnerLeptonicTagger.hh"
#include "TopHadronicTagger.hh"
#include "BranchesTopPartner.hh"

namespace boca {

namespace naturalness {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerTopPairTagger : public TaggerTemplate<Octet53,MultiBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Octet53> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

private:

    Reader<TopPartnerLeptonicTagger> top_partner_reader_;

    Reader<standardmodel::TopHadronicTagger> top_reader_;
};

}

}
