# pragma once

# include "Tagger.hh"

/**
 * @brief Bottom BDT tagger
 *
 */
namespace hanalysis
{
class BottomTagger : public Tagger
{

public:

    BottomTagger();

    BottomBranch GetBranch(const fastjet::PseudoJet &Jet) const;

    int Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag){
      PreCuts pre_cuts;
      return Train(event,pre_cuts,tag);
    }

    int Train(hanalysis::HEvent &event, PreCuts &pre_cuts, const hanalysis::HObject::Tag tag);

    Jets GetMultiJetBdt(Jets &jets, const TMVA::Reader &reader);

    Jets GetJetBdt(HEvent &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Jets GetJetBdt(HEvent &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return GetJetBdt(event,pre_cuts,reader);
    }

    Jets GetSubBdt(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number);

    int GetBdt(hanalysis::HEvent &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
        Jets jets = GetJetBdt(event, pre_cuts, reader);
        SaveEntries(jets);
        return jets.size();
    }

    int GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader) {
      PreCuts pre_cuts;
      return GetBdt(event,pre_cuts,reader);
    }

    fastjet::PseudoJet GetJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader);


    Jets GetSubJets(const Jets &jets, const int sub_jet_number){
      Jets subjets;
      for(const auto &jet : jets){
        Jets jets = Tagger::GetSubJets(jet,sub_jet_number);
        subjets = JoinVectors(subjets, jets);
      }
      return subjets;
    }

    Jets GetMultiJetBdt(Jets &jets, const Reader &reader) {
        Print(kError, "Bdt", "depreciated");
    }

    Jets GetJetBdt(const Jets &jets, const Reader &reader) {
        Print(kError, "Bdt", "depreciated");
    }

    Jets GetJetBdt(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader);

    Jets GetJetBdt(const Jets &jets, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return GetJetBdt(jets,pre_cuts,reader);
    }

    Jets GetSubBdt(const Jets &jets, const Reader &reader, const int sub_jet_number) {
        Print(kError, "Bdt", "depreciated");
    }

    Jets GetSubJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number);

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<BottomBranch &>(*clones_array.At(entry)).Bdt;
    }

    void SaveEntries(const Jets &jets) {
        for (const auto & jet : jets) static_cast<BottomBranch &>(*tree_branch().NewEntry()) = GetBranch(jet);
    }

    TClass &Class() const {
        return *BottomBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "BottomTagger";
    }

private:

    void DefineVariables();

    Jets CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const hanalysis::HObject::Tag tag);

    Jets GetSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const hanalysis::HObject::Tag tag, const int sub_jet_number);

    BottomBranch branch_;

};
}
