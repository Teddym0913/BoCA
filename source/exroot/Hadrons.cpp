# include "exroot/Hadrons.hh"

bool analysis::exroot::Hadrons::GetJets(const analysis::Hadrons::JetDetail jet_detail)
{
    Print(kInformation, "Get Jet", clones_arrays_->JetSum(), jet_detail);
    for (const int JetNumber : Range(clones_arrays_->JetSum())) {
        Print(kDetailed, "Jet Number", JetNumber);
        TRootJet &jet = static_cast<TRootJet &>(clones_arrays().Jet(JetNumber));
        jets_.emplace_back(GetPseudoJet(jet));
        if (jet.BTag > 0) {
            Print(kDetailed, "Has B Tag");
            BottomLorentzVectors.emplace_back(GetLorentzVector(jet));
            BottomJets.emplace_back(GetPseudoJet(jet));
        } else {
            JetLorentzVectors.emplace_back(GetLorentzVector(jet));
        }
    }
    Print(kDebug, "Untagged jets", JetLorentzVectors.size());
    return 1;
}