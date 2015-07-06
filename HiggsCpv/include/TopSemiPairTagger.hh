#pragma once

#include "TopHadronicTagger.hh"
#include "TopSemiTagger.hh"
#include "Sextet.hh"
#include "BranchesHiggsCpv.hh"
#include "ReaderTagger.hh"

namespace analysis
{

namespace higgscpv
{

/**
 * @brief JetPair BDT tagger
 *
 */
class TopSemiPairTagger : public BranchTagger<TripletPairBranch>
{

public:

    TopSemiPairTagger();

    int Train(const Event &event, const Tag tag);

    std::vector<Sextet> Multiplets(const Event &event, const TMVA::Reader &reader) const;

private:

    ReaderTagger<TopSemiTagger> top_semi_reader_;

    ReaderTagger<TopHadronicTagger> top_hadronic_reader_;

};

}

}
