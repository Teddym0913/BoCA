# include "HChargedSignatureSemiTagger.hh"

hheavyhiggs::HChargedSignatureSemiTagger::HChargedSignatureSemiTagger()
{
//       DebugLevel = HDetailed;
    Print(HInformation , "Constructor");
    DefineVariables();
}

hheavyhiggs::HChargedSignatureSemiTagger::~HChargedSignatureSemiTagger()
{
    Print(HInformation , "Destructor");
}

void hheavyhiggs::HChargedSignatureSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    TopSemiTagger = NewTopSemiTagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HChargedSignatureSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    set_tagger_name("ChargedSignatureSemi");
    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.HiggsMass, "HiggsMass");
    AddVariable(Branch.PairRap, "PairRap");
    AddVariable(Branch.BottomBdt, "BottomBdt");
    AddVariable(Branch.PairBottomBdt, "PairBottomBdt");
    AddVariable(Branch.PairBdt, "PairBdt");
    AddVariable(Branch.HiggsBdt, "HiggsBdt");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

hheavyhiggs::HChargedOctetBranch hheavyhiggs::HChargedSignatureSemiTagger::GetBranch(const HOctet44 &Octet) const
{
    Print(HInformation, "branch", Octet.Bdt());

    HChargedOctetBranch EventSemiBranch;

    EventSemiBranch.Mass = Octet.Jet().m();
    EventSemiBranch.Rap = Octet.Jet().rap();
    EventSemiBranch.Phi = Octet.Jet().phi();
    EventSemiBranch.Pt = Octet.Jet().pt();
    EventSemiBranch.Ht = Octet.Ht();

    EventSemiBranch.DeltaPt = Octet.DeltaPt();
    EventSemiBranch.DeltaHt = Octet.DeltaHt();
    EventSemiBranch.DeltaM = Octet.DeltaM();
    EventSemiBranch.DeltaRap = Octet.DeltaRap();
    EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch.DeltaR = Octet.DeltaR();

    EventSemiBranch.Bdt = Octet.Bdt();
    EventSemiBranch.Tag = Octet.Tag();
    EventSemiBranch.BottomBdt = Octet.BottomBdt();
    EventSemiBranch.PairBottomBdt = Octet.PairBottomBdt();
    EventSemiBranch.HiggsBdt = Octet.Quartet1().Bdt();
    EventSemiBranch.PairBdt = Octet.Quartet2().Bdt();

    EventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    EventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    return EventSemiBranch;
}

std::vector<hheavyhiggs::HChargedOctetBranch> hheavyhiggs::HChargedSignatureSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag tag)
{
    Print(HInformation, "Get Event Tags");

    Jets jets = GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, jets, TopSemiReader);
    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, jets, ChargedHiggsSemiReader);

    Jets HiggsParticles = Event.GetParticles()->Generator();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());

//     if(Tag == HBackground && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());

    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, jets, TopHadronicReader);
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, jets, TopHadronicReader);
//         TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, jets, TopHadronicReader);
//         TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
//     }
    std::vector<hanalysis::HTriplet> FinalTriplets;
    if (tag == kSignal) {
        Jets Particles = Event.GetParticles()->Generator();
        Jets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
        if (TopParticles.size() != 1) Print(HError, "Where is the Top?");
        else for (const auto & Triplet : TripletsHadronic) if ((Triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize)) FinalTriplets.emplace_back(Triplet);
    } else FinalTriplets = TripletsHadronic;

    if (tag == kSignal && FinalTriplets.size() > 1) {
        std::sort(FinalTriplets.begin(), FinalTriplets.end());
        FinalTriplets.erase(FinalTriplets.begin() + 1, FinalTriplets.end());
    }

    Jets FinalBottoms;
    if (tag == kSignal) {
        Jets Particles = Event.GetParticles()->Generator();
        Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(HError, "Where is the Bottom?");
        else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
    } else FinalBottoms = jets;

    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(FinalTriplets, FinalBottoms, ChargedJetPairReader);

//     if(Tag == HBackground && JetQuartets.size() > 1) JetQuartets.erase(JetQuartets.begin() + 1, JetQuartets.end());

//     Print(HError, "Number of Higgs and Pairs", HiggsQuartets.size(), JetQuartets.size());
    std::vector<HOctet44> Octets;
    for (const auto HiggsQuartet  : HiggsQuartets)
        for (const auto & JetQuartet : JetQuartets) {
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Octet.SetTag(tag);
            Octets.emplace_back(Octet);
        }
//     Print(HError, "Number of Signatures", Octets.size());

    std::vector<hheavyhiggs::HChargedOctetBranch> SignatureSemiBranches;
    for (const auto & Octet : Octets) SignatureSemiBranches.emplace_back(GetBranch(Octet));

    return SignatureSemiBranches;
}


std::vector<HOctet44> hheavyhiggs::HChargedSignatureSemiTagger::GetBdt(
    const std::vector< hanalysis::HQuartet31 > &HiggsQuartets, const std::vector< hanalysis::HQuartet31 > &JetQuartets, const hanalysis::Reader &Reader)
{
    Print(HInformation, "Bdt");

//     Print(HError, "Number of Higgs and Pairs", HiggsQuartets.size(), JetQuartets.size());
    std::vector<HOctet44> Octets;
    for (const auto & JetQuartet : JetQuartets) {
        for (const auto & HiggsQuartet : HiggsQuartets) {
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Branch = GetBranch(Octet);
            Octet.SetBdt(Reader.Bdt());
            Octets.emplace_back(Octet);
        }
    }
//     Print(HError, "Number of Signatures", Octets.size());

    if (Octets.size() > 1) std::sort(Octets.begin(), Octets.end());
    Octets.erase(Octets.begin() + std::min(max_combi(), int(Octets.size())), Octets.end());
    Print(HInformation, "Event Number", Octets.size());


    return Octets;
}
