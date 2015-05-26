# include "EventChargedTagger.hh"

heavyhiggs::EventChargedTagger::EventChargedTagger()
{
//       DebugLevel = kDebug;
    Print(kInformation , "Constructor");
    set_tagger_name("ChargedeventSemi");
    bottom_reader_.set_tagger(bottom_tagger_);
    signature_semi_reader_.set_tagger(signature_semi_tagger_);
    DefineVariables();
}

void heavyhiggs::EventChargedTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.LeptonNumber, "LeptonNumber");
    AddVariable(branch_.JetNumber, "JetNumber");
    AddVariable(branch_.BottomNumber, "BottomNumber");
    AddVariable(branch_.ScalarHt, "ScalarHt");

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.PairRap, "PairRap");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");
    AddVariable(branch_.SignatureBdt, "SignatureBdt");
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");

    AddVariable(branch_.BottomBdt1, "BottomBdt1");
    AddVariable(branch_.BottomBdt2, "BottomBdt2");
    AddVariable(branch_.BottomBdt3, "BottomBdt3");
    AddVariable(branch_.BottomBdt4, "BottomBdt4");
    AddVariable(branch_.BottomBdt5, "BottomBdt5");
    AddVariable(branch_.BottomBdt6, "BottomBdt6");
    AddVariable(branch_.BottomBdt7, "BottomBdt7");
    AddVariable(branch_.BottomBdt8, "BottomBdt8");
    AddVariable(branch_.BottomBdt12, "BottomBdt12");
    AddVariable(branch_.BottomBdt34, "BottomBdt34");
    AddVariable(branch_.BottomBdt56, "BottomBdt56");
    AddVariable(branch_.BottomBdt78, "BottomBdt78");

    AddVariable(branch_.SubBottomBdt1, "SubBottomBdt1");
    AddVariable(branch_.SubBottomBdt2, "SubBottomBdt2");
    AddVariable(branch_.SubBottomBdt3, "SubBottomBdt3");
    AddVariable(branch_.SubBottomBdt4, "SubBottomBdt4");
    AddVariable(branch_.SubBottomBdt5, "SubBottomBdt5");
    AddVariable(branch_.SubBottomBdt6, "SubBottomBdt6");
    AddVariable(branch_.SubBottomBdt7, "SubBottomBdt7");
    AddVariable(branch_.SubBottomBdt8, "SubBottomBdt8");
    AddVariable(branch_.SubBottomBdt12, "SubBottomBdt12");
    AddVariable(branch_.SubBottomBdt34, "SubBottomBdt34");
    AddVariable(branch_.SubBottomBdt56, "SubBottomBdt56");
    AddVariable(branch_.SubBottomBdt78, "SubBottomBdt78");

    AddVariable(branch_.RestNumber, "RestNumber");
    AddVariable(branch_.RestM, "RestM");
    AddVariable(branch_.RestPt, "RestPt");
    AddVariable(branch_.RestHt, "RestHt");
    AddVariable(branch_.RestPhi, "RestPhi");
    AddVariable(branch_.RestRap, "RestRap");
    AddVariable(branch_.RestBdt, "RestBdt");
    AddVariable(branch_.LeptonHt, "LeptonHt");
    AddVariable(branch_.MissingEt, "MissingEt");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

int heavyhiggs::EventChargedTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "Get event Tags");

//     Jets PreJets = GetJets(event);
//     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
//     Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);

    Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//     std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_tagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);


//     Jets HiggsParticles = event.partons().Generator();
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), analysis::WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
//     if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
//     std::sort(Higgsquartets.begin(), Higgsquartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
//     if (tag == kSignal && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());
//     if (tag == kBackground && Higgsquartets.size() > 0) Higgsquartets.erase(Higgsquartets.begin());


//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     std::vector<analysis::Triplet> Finaltriplets;
//     if (tag == kSignal) {
//         Jets Particles = event.partons().Generator();
//         Jets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
//         if (TopParticles.size() != 1) Print(kError, "Where is the Top?",TopParticles.size());
//         else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.at(0)) < detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
//     } else Finaltriplets = tripletsHadronic;

//     if (tag == kSignal && Finaltriplets.size() > 1) {
//         std::sort(Finaltriplets.begin(), Finaltriplets.end());
//         Finaltriplets.erase(Finaltriplets.begin() + 1, Finaltriplets.end());
//     }

//     Jets FinalBottoms;
//     if (tag == kSignal) {
//         Jets Particles = event.partons().Generator();
//         Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
//         if (BottomParticles.size() != 1) Print(kError, "Where is the Bottom?",BottomParticles.size());
//         else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.at(0)) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
//     } else FinalBottoms = jets;


//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);

//     std::vector<analysis::Quartet31> Jetquartets = Chargedjet_pair_tagger.GetBdt(tripletsHadronic, jets, ChargedJetPairReader);


//     Jets TopParticles = event.partons().Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
//     if (Tag== kSignal && TopParticles.size() != 1) Print(kError, "Where is the Top?");
//     Jets BottomParticles = event.partons().Generator();
//     BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
//     if (Tag== kSignal && BottomParticles.size() != 1) Print(kError, "Where is the Bottom?");
//
//     if (TopParticles.size() > 0 && BottomParticles.size() > 0) {
//         analysis::Doublet ParticlePair(TopParticles.front(), BottomParticles.front());
//         std::sort(Jetquartets.begin(), Jetquartets.end(), MinDeltaR(ParticlePair.Jet()));
//         if (Tag == kSignal && Jetquartets.size() > 1) Jetquartets.erase(Jetquartets.begin() + 1, Jetquartets.end());
//         if (Tag == HBackground && Jetquartets.size() > 0) Jetquartets.erase(Jetquartets.begin());
//     }

//     std::vector<Octet44> octets = SignatureSemiTagger.GetBdt(Higgsquartets, Jetquartets, SignatureSemiReader);
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);

    std::vector<analysis::MultipletEvent<Octet44>> events;
    for (const auto & octet : octets) {
      analysis::MultipletEvent<Octet44> octetevent(octet);
//       analysis::GlobalObservables global_observables;
//         global_observables.lepton_number = event.leptons().GetLeptonJets().size();
//         global_observables.jet_number = event.hadrons().GetJets().size();
//         global_observables.bottom_number = event.hadrons().GetBottomJets().size();
//         global_observables.scalar_ht = event.hadrons().GetScalarHt();
//         global_observables.missing_et = event.hadrons().GetMissingEt().pt();
        octetevent.Setglobal_observables(analysis::GlobalObservables(event));
        octetevent.SetLeptons(Leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        octetevent.SetTag(tag);
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(octetevent.multiplet().quartet1().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().quartet1().triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().quartet1().triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().quartet1().triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().quartet2().singlet()) < detector_geometry().JetConeSize) continue;
            if (Jet.delta_R(octetevent.multiplet().quartet2().triplet().singlet()) < detector_geometry().JetConeSize) continue;
            octetevent.AddRestJet(Jet);
        }
        events.emplace_back(octetevent);
    }

//     std::vector<heavyhiggs::EventChargedBranch> eventSemiBranches;
//     for (const auto & event : events)eventSemiBranches.emplace_back(GetBranch(event));

//     return eventSemiBranches;
return SaveEntries<EventChargedBranch>(events);
}

// analysis::GlobalObservables heavyhiggs::EventChargedTagger::global_observables(analysis::Event &event){
//   analysis::GlobalObservables global_observables;
//   global_observables.lepton_number = event.leptons().GetLeptonJets().size();
//   global_observables.jet_number = event.hadrons().GetJets().size();
//   global_observables.bottom_number = event.hadrons().GetBottomJets().size();
//   global_observables.scalar_ht = event.hadrons().GetScalarHt();
//   global_observables.missing_et = event.hadrons().GetMissingEt().pt();
//   return global_observables;
// }

std::vector<analysis::MultipletEvent<Octet44>> heavyhiggs::EventChargedTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  Print(kInformation, "Get event Tags");
  std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);
  Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    Jets Leptons = event.leptons().GetLeptonJets();



    std::vector<analysis::MultipletEvent<Octet44>> events;
    for (auto & octet : octets) {
      analysis::MultipletEvent<Octet44> octetevent(octet, analysis::GlobalObservables(event));
        for (const auto & Jet : jets)  {
            if (octet.quartet1().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet1().triplet().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet1().triplet().doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet1().triplet().doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet2().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet2().triplet().singlet().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet2().triplet().doublet().Singlet1().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            if (octet.quartet2().triplet().doublet().Singlet2().delta_R(Jet) < detector_geometry().JetConeSize) continue;
            octetevent.AddRestJet(Jet);
        }
        octetevent.SetLeptons(Leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        branch_ = branch<EventChargedBranch>(octetevent);
        octetevent.SetBdt(Bdt(reader));
        events.emplace_back(octetevent);
    }

    std::sort(events.begin(), events.end());
    if (events.size() > 1)events.erase(events.begin() + 1, events.end());
    Print(kInformation, "event Number", events.size(), jets.size());

    return events;
}