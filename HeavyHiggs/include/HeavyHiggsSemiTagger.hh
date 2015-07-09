#pragma once

#include "TopSemiTagger.hh"
#include "Sextet.hh"
#include "TopHadronicTagger.hh"
#include "Branch.hh"

namespace analysis
{

namespace heavyhiggs {

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class HeavyHiggsSemiTagger : public BranchTagger<HeavyHiggsSemiBranch>
{

public:

    HeavyHiggsSemiTagger();

    int Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const final;

    std::vector<Sextet> Multiplets(const Event& event, PreCuts &pre_cuts, const TMVA::Reader &reader) const;

    int GetBdt(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const  final {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    std::string name() const final {
      return "HeavyHiggsSemi";
    }

private:

    Reader<TopHadronicTagger> top_hadronic_reader_;

    Reader<TopSemiTagger> top_semi_reader_;
};

}

}
