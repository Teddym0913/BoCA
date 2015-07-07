#pragma once

#include "TopPartnerHadronicTagger.hh"
#include "TopPartnerSemiTagger.hh"
#include "BranchesTopPartner.hh"
#include "Decuplet.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerPairTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const;

    std::vector<Decuplet55> Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const {
      return "TopPartnerPair";
    }

private:

    ReaderTagger<TopPartnerHadronicTagger> top_partner_hadronic_reader_;

    ReaderTagger<TopPartnerSemiTagger> top_partner_semi_reader_;
};

}

}
