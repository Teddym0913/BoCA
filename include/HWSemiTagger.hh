# pragma once

# include "HDoublet.hh"
# include "Tagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HWSemiTagger : public Tagger
{

public:

    HWSemiTagger();

    HWSemiBranch GetBranch(const hanalysis::HDoublet &doublet) const;

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag);

    std::vector<HDoublet> GetDoublets(HEvent &event, const TMVA::Reader &reader);

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader) {
        std::vector<HDoublet> doublets = GetDoublets(event, reader);
        SaveEntries(doublets);
        return doublets.size();
    }

    std::vector<hanalysis::HDoublet> GetBdt(const Jets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &reader) {
      Print(HError,"get bdt", "depreciated");
    }

    std::vector<HDoublet>  GetBdt(const Jets &Leptons, const fastjet::PseudoJet &MissingEt, const TMVA::Reader &reader){
      Print(HError,"get bdt", "depreciated");
    }

    void SaveEntries(const std::vector<HDoublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<HWSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
    }

    int WSemiId(hanalysis::HEvent &event) {
        return WSemiId(WSemiDaughters(event));
    }

    TClass &Class() const {
      return *HWSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    }

private:

    Jets WSemiDaughters(hanalysis::HEvent &Event);

    int WSemiId(const Jets &jets);

    void DefineVariables();

    Tag GetTag(const hanalysis::HDoublet &Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet &Doublet)const;

    std::vector<hanalysis::HDoublet> GetNeutrino(const HDoublet &Doublet, const Jets &Neutrinos, const Tag Tag)const;

//     std::vector<hanalysis::HDoublet> GetDoublets(const hanalysis::HDoublet &Doublet, const Jets &Neutrinos, const hanalysis::HObject::Tag Tag);

    HWSemiBranch branch_;

    float w_mass_window_;

};

