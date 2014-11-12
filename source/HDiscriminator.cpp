# include "HDiscriminator.hh"

hdelphes::HDiscriminator::HDiscriminator()
{

    Print(1, "Constructor");

//     DebugLevel = 5;

}

hdelphes::HDiscriminator::~HDiscriminator()
{

    Print(1, "Destructor");

}

HJets hdelphes::HDiscriminator::GetCandidateJets(const HJets &EFlowJets, const float ScalarHt)
{

    Print(2, "Get Tagged Candidate Jets", EFlowJets.size());

    const HJets Jets;

    if (EFlowJets.size() == 0) {

        Print(2, "No EFlow Jets");
        return Jets;

    }

    const float DeltaR = 750. / ScalarHt;

    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    const HJets FatJets = GetFatJets(EFlowJets, FatJetDefinition);

    HJets MassDropJets = GetMassDropJets(FatJets);
//     HJets MassDropJets = GetSubJetTaggedJets(FatJets);

    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

    std::sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


HJets hdelphes::HDiscriminator::GetCandidateJetsForced(const HJets &EFlowJets, const float ScalarHt)
{

    Print(2, "Get Tagged Candidate Jets", EFlowJets.size());

    const HJets Jets;

    if (EFlowJets.size() == 0) {

        Print(2, "No EFlow Jets");
        return Jets;

    }

//     float DeltaR = 1000. / ScalarHt;
    float DeltaR = 750. / ScalarHt;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    HJets MassDropJets;

    while (MassDropJets.size() < 1 && DeltaR < 7) {

        const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
        const HJets FatJets = GetFatJets(EFlowJets, FatJetDefinition);

        MassDropJets = GetMassDropJets(FatJets);
        MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

        DeltaR += .25;
    }

    std::sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


bool hdelphes::HDiscriminator::JetIsBad(const PseudoJet &Jet)
{

    HObject Object;

    if (std::abs(Jet.m()) <= 40.) {

        Object.Print(2, "Fat Jet Mass", Jet.m());
        return 1;

    }


    if (Jet.pieces().size() != 2) {

        Object.Print(1, "Pieces Sum", Jet.pieces().size());
        return 1;

    }

    if (!Jet.has_structure()) {

        Object.Print(1, "PseudoJet has no structure");
        return 1;

    }

    return 0;

}
