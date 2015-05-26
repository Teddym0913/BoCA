# pragma once

# include "Branch.hh"
# include "ChargedHiggsSemiTagger.hh"
# include "TripletJetPairTagger.hh"
# include "Octet44.hh"

namespace heavyhiggs
{

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    SignatureChargedTagger();

    int Train(analysis::Event &event, const Tag tag);

    std::vector<Octet44> Multiplets(analysis::Event &event, const TMVA::Reader &reader);

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "SignatureChargedTagger";
    }

private:

    analysis::ChargedHiggsSemiTagger charged_higgs_semi_tagger_;

    analysis::TripletJetPairTagger triplet_jet_pair_tagger_;

    analysis::Reader charged_higgs_semi_reader_;

    analysis::Reader triplet_jet_pair_reader_;

    TClass &Class() const {
      return *OctetChargedBranch::Class();
    }

    void DefineVariables();

    OctetChargedBranch branch_;

};

}