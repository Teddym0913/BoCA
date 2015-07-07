#pragma once

#include "TopLeptonicTagger.hh"
#include "Triplet.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs
{

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class ChargedHiggsLeptonicTagger : public analysis::BranchTagger<ChargedHiggsLeptonicBranch>
{

public:

    ChargedHiggsLeptonicTagger();

    int Train(const Event &event, const analysis::Tag tag);

    std::vector<analysis::Triplet> Multiplets(const Event &event, const TMVA::Reader &reader) const;

    std::string name() const {
      return "ChargedHiggsLeptonic";
    }

private:

    analysis::ReaderTagger<analysis::BottomTagger> bottom_reader_;

    analysis::ReaderTagger<analysis::TopLeptonicTagger> top_leptonic_reader_;

};

}

}
