# include "HEventDelphes.hh"

hanalysis::hdelphes::HEvent::HEvent()
{
// DebugLevel=HDebug;
    Print(HNotification, "Constructor");

    Particles = new HParticle();
    Jets = new HJet();
    Lepton = new HLepton();
    TopTagger = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

}

hanalysis::hdelphes::HEvent::~HEvent()
{

    Print(HNotification, "Destructor");

    delete Particles;
    delete Jets;
    delete Lepton;
    delete TopTagger;
    delete HiggsTagger;
    delete Discriminator;

}

void hanalysis::hdelphes::HEvent::NewEvent(const hanalysis::HClonesArray *const ClonesArrays)
{

    Print(HInformation, "New Event");

    Particles->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    Lepton->NewEvent(ClonesArrays);

    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

}



fastjet::PseudoJet hanalysis::hdelphes::HEvent::GetHiggs()
{

    Print(HInformation, "Get Higgs");

    fastjet::PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(Jets->GetEFlowJets(),Particles->GetBottomJets(),Particles->GetCharmJets());

    return (HiggsJet);

}

HJets hanalysis::hdelphes::HEvent::GetTops(hanalysis::HJetTag &JetTag)
{

    Print(HInformation, "Get Tops", JetTag.GetBranchId(0,0));

    HJets EFlowJets = Jets->GetEFlowJets();

    HJets TopJetVector = TopTagger->GetTops(EFlowJets);

    return(TopJetVector);

}




HJets hanalysis::hdelphes::HEvent::GetCandidates(hanalysis::HJetTag  &JetTag) // FIXME why does this not work
{
    Print(HInformation, "GetHiggsTopCandidates");

    return Discriminator->GetCandidateJets(Jets->GetIsolatedTaggedEFlowJets(JetTag), Jets->GetScalarHt());

}


