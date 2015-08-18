#pragma once

#include "Quintet.hh"
#include "TopHadronicTagger.hh"
#include "BosonTagger.hh"
#include "BranchesTopPartner.hh"

namespace boca
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHadronicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              Tag tag) const final;

    std::vector<Quintet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "TopPartnerHadronic";
    }

    std::string NiceName() const final {
        return "#tilde t_{h}";
    }

private:

    Reader<TopHadronicTagger> top_reader_;

    Reader<BosonTagger> boson_reader_;

};

}

}
