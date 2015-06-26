# pragma once

# include "Septet.hh"
# include "TopPartnerSemiTagger.hh"
# include "HiggsTagger.hh"
# include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHiggsPairTagger : public BranchTagger<MultiBranch>
{

public:

    TopPartnerHiggsPairTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector<Septet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual  std::string ClassName() const {
        return "TopPartnerHiggsPairTagger";
    }

private:

    TopPartnerSemiTagger top_partner_hadronic_tagger_;

    HiggsTagger higgs_tagger_;

    Reader top_partner_hadronic_reader_;

    Reader higgs_reader_;
};

}

}