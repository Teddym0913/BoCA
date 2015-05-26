# pragma once

# include "Quattuordecuplet.hh"
# include "TopPartnerTagger.hh"
# include "HiggsTagger.hh"
# include "Branches.hh"

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class SignatureTagger : public analysis::Tagger
{

public:

    SignatureTagger();

    int Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const analysis::Object::Tag tag);

    std::vector<Quattuordecuplet> Quintets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string ClassName() const {
        return "EventTagger";
    }

private:

    TClass &Class() const {
      return *SignatureBranch::Class();
    }

    void DefineVariables();

    SignatureBranch branch_;

    TopPartnerTagger top_partner_tagger_;

    analysis::HiggsTagger higgs_tagger;

    analysis::Reader top_partner_reader_;

    analysis::Reader higgs_reader_;
};

}
