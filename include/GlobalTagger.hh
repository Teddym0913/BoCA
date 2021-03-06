#pragma once

#include "../StandardModel/include/BottomTagger.hh"
#include "Reader.hh"
#include "GlobalObservables.hh"

namespace boca
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class GlobalTagger : public TaggerTemplate<GlobalObservables, GlobalObservableBranch>
{

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<GlobalObservables> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<standardmodel::BottomTagger> bottom_reader_;

};

}
