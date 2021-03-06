#pragma once

#include "ChargedHiggsSemiTagger.hh"
#include "TripletJetPairTagger.hh"
#include "multiplets/Octet.hh"

namespace boca {

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class SignatureChargedTagger : public TaggerTemplate<Octet44,OctetChargedBranch> {

public:

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Octet44> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<ChargedHiggsSemiTagger> charged_higgs_semi_reader_;

    Reader<TripletJetPairTagger> triplet_jet_pair_reader_;


};

}

}
