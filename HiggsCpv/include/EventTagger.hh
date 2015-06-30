#pragma once

#include "SignatureTagger.hh"
#include "MultipletEvent.hh"

namespace analysis
{

namespace higgscpv
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventTagger : public BranchTagger<EventBranch>
{

public:

    /**
    * @brief Constructor
    *
    */
    EventTagger();

    int Train(analysis::Event &event, analysis::PreCuts &, const analysis::Tag tag);

    std::vector<MultipletEvent<Octet62>> Multiplets(Event &event,PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event, pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader) {
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

private:

    SignatureTagger signature_tagger_;

    Reader signature_reader_;

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

};

}

}
