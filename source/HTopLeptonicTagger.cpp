# include "HTopLeptonicTagger.hh"

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger(HBottomTagger *const NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);

    SetTaggerName("TopLeptonic");

    Branch = new HTopLeptonicBranch();
    JetTag = new HJetTag();

    DefineVariables();

}

hanalysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
}

void hanalysis::HTopLeptonicTagger::FillBranch(const HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.GetBdt());
    FillBranch(Branch, Doublet);
}

void hanalysis::HTopLeptonicTagger::FillBranch(HTopLeptonicBranch *const TopLeptonicBranch, const hanalysis::HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.GetBdt());

    TopLeptonicBranch->Mass = Doublet.GetDoubletJet().m();
    TopLeptonicBranch->JetPt = Doublet.GetJet1().pt();
    TopLeptonicBranch->LeptonPt = Doublet.GetJet2().pt();
    TopLeptonicBranch->DeltaR = Doublet.GetDeltaR();
    TopLeptonicBranch->DeltaRap = Doublet.GetDeltaRap();
    TopLeptonicBranch->DeltaPhi = Doublet.GetPhiDelta();
    TopLeptonicBranch->BottomBdt = Doublet.GetBdt();
    TopLeptonicBranch->TopTag = Doublet.GetTag();

}

void hanalysis::HTopLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->JetPt, "JetPt"));
    Observables.push_back(NewObservable(&Branch->LeptonPt, "LeptonPt"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch->BottomBdt, "BottomBdt"));

    Spectators.push_back(NewObservable(&Branch->TopTag, "TopTag"));

    Print(HNotification, "Variables defined");

}

std::vector<HTopLeptonicBranch *> hanalysis::HTopLeptonicTagger::GetBranches(HEvent *const Event, const HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {WId, TopId, HiggsId, CpvHiggsId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else ++Lepton;
    }

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons)
        for (const auto & Jet : Jets) {
            Print(HDebug, "Lepton Tagging", GetParticleName(Lepton.user_index()), GetParticleName(Jet.user_index()));
            HDoublet Doublet(Jet, Lepton);
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.GetTag() != Tag) continue;
            Doublets.push_back(Doublet);
        }


    Print(HInformation, "Number JetPairs", Doublets.size());

    std::vector<HTopLeptonicBranch *> TopLeptonicBranches;
    for (const auto & Doublet : Doublets) {
        HTopLeptonicBranch *TopLeptonicBranch = new HTopLeptonicBranch();
        FillBranch(TopLeptonicBranch, Doublet);
        TopLeptonicBranches.push_back(TopLeptonicBranch);
    }

    return TopLeptonicBranches;

}

hanalysis::HObject::HTag hanalysis::HTopLeptonicTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Triple Tag");

    if (std::abs(Doublet.GetJet1().user_index()) != TopId) return HBackground;
    Print(HDebug, "its a top");
    if (std::abs(Doublet.GetJet2().user_index()) != WId) return HBackground;
    Print(HDebug, "its a W");
    if (sgn(Doublet.GetJet1().user_index()) != sgn(Doublet.GetJet2().user_index())) return HBackground;
    Print(HDebug, "its a Signal");

    return HSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HTopLeptonicTagger::GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::HReader *const Reader)
{

    for (auto Lepton = Leptons.begin(); Lepton != Leptons.end();) {
        if (std::abs((*Lepton).user_index()) == MixedJetId) Lepton = Leptons.erase(Lepton);
        else ++Lepton;
    }

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        for (const auto & Jet : Jets) {
            HDoublet Doublet(Jet, Lepton);
            Doublet.SetTag(GetTag(Doublet));
            FillBranch(Doublet);
            Doublet.SetBdt(Reader->GetBdt());
            Doublets.push_back(Doublet);
        }
    }
    return Doublets;

}
