#pragma once

#include <functional>
#include "Decuplet.hh"
#include "TopPartnerTopPairTagger.hh"
#include "HiggsTagger.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureSingleTagger : public BranchTagger<SignatureBranch>
{

public:

    SignatureSingleTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<Decuplet82> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::string Name() const final {
        return "SignatureSingle";
    }

    std::string NiceName() const final {
        return "Tth";
    }

private:

    std::vector<Decuplet82> Decuplets(const Event& event, const std::function<Decuplet82(Decuplet82&)>& function) const;

    Reader<TopPartnerTopPairTagger> pair_reader_;

    Reader<HiggsTagger> higgs_reader_;
};

}

}
