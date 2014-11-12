# include "HAnalysisTopTagger.hh"

htoptagger::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    JetTag = new htoptagger::HJetTag();

    SubStructure = new hdelphes::HSubStructure();

//     DebugLevel = 3;

}

htoptagger::HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

    delete JetTag;

    delete SubStructure;

}

std::vector<std::string> htoptagger::HAnalysis::GetStudyNames() const
{

    return  {"Top"};

}

std::vector<hanalysis::HFile *> htoptagger::HAnalysis::GetFiles(const std::string &StudyName) const
{

    Print(1, "Set File Vector");

    std::vector<hanalysis::HFile*> Files;

    if (StudyName != "Higgs") {

      hdelphes::HFile *Background = new hdelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->SetCrosssection(3.215); // pb
        Background->SetError(0.012); // pb
        Files.push_back(Background);

    }

    hdelphes::HFile *Even = new hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(0.02079); // pb
    Even->SetError(0.000078); // pb
//     Even->TagString="tag_2";
    Files.push_back(Even);

    hdelphes::HFile *Mix = new hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(0.01172); // pb
    Mix->SetError(0.000045); // pb
//     Mix->TagString="tag_2";
    Files.push_back(Mix);

    hdelphes::HFile *Odd = new hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(0.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
    Files.push_back(Odd);

    Print(1, "Files prepared");

    return Files;

}


void htoptagger::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
//     LeptonBranch = TreeWriter->NewBranch("Lepton", HLeptonBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());

}

void htoptagger::HAnalysis::CloseFile()
{
    Print(1, "Close File");

}

int htoptagger::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(3, "Get Branch Id", ParticleId);

    if (
        RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles) &&
        HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}

bool htoptagger::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(2, "Analysis", StudyName);


    const HJets CandidateJets = Event->GetTops(JetTag);

    if (CandidateJets.size() < 1) {

        Print(0, "No Candidates", CandidateJets.size());

        return 0;

    } else Print(2, "Number of Candidates", CandidateJets.size());

    bool HasCandidate =0;

    for (const auto & CandidateJet : CandidateJets) {

        if (CandidateJet == 0 || CandidateJet.m() <= 0 || CandidateJet.pt() <= 0) {

            Print(0, "Illeagal Candidate", CandidateJet.m());
            continue;

        }


        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Eta = CandidateJet.rap();
        Candidate->Phi = CandidateJet.phi_std();

        Print(2, "Candidate Mass", CandidateJet.m());

        // Tagging

        int UserIndex = std::abs(CandidateJet.user_index());

        if (UserIndex == CpvHiggsId) {
            Candidate->HiggsTag = 1;
            Candidate->TopTag = 0;

        } else if (UserIndex == TopId) {

            Candidate->TopTag = 1;
            Candidate->HiggsTag = 0;

        } else {

            Candidate->TopTag = 0;
            Candidate->HiggsTag = 0;

        }

//         SubStructure->NewEvent();
//         if (!SubStructure->GetSubJets(CandidateJet)) {
//
//             Print(0,"No SubJets");
//
//             return 0;
//
//         }
//
//         Candidate->SubJetsDeltaR = SubStructure->GetSubJetsDeltaR();
//         Candidate->Asymmetry = SubStructure->GetAsymmetry();
//         Candidate->DeltaR = SubStructure->GetDeltaR();
//         Candidate->DiPolarity = SubStructure->GetDiPolarity(CandidateJet);
//
//         Candidate->SubJet1Mass = SubStructure->GetSubJet1Mass();
//         Candidate->SubJet1Pt = SubStructure->GetSubJet1Pt();
//         Candidate->SubJet1DeltaR = SubStructure->GetSubJet1DeltaR();
//
//         Candidate->SubJet2Mass = SubStructure->GetSubJet2Mass();
//         Candidate->SubJet2Pt = SubStructure->GetSubJet2Pt();
//         Candidate->SubJet2DeltaR = SubStructure->GetSubJet2DeltaR();
//
// //         SubStructure->GetIsolation(CandidateJet, Leptons);
//
//         Candidate->IsolationEta = SubStructure->GetIsolationEta();
//         Candidate->IsolationPhi = SubStructure->GetIsolationPhi();
//         Candidate->IsolationPt = SubStructure->GetIsolationPt();
//         Candidate->IsolationDeltaR = SubStructure->GetIsolationDeltaR();
//         Candidate->IsolationAngle = SubStructure->GetIsolationAngle();
//
//         Print(3, "Isolation", Candidate->IsolationDeltaR);
//
//         if (!SubStructure->GetConstituents(CandidateJet, ConstituentBranch)) {
//
//             Print(0,"No Constituents");
//
//             return 0;
//
//         }
//
//         Candidate->ConstEta = SubStructure->GetConstituentEta();
//         Candidate->ConstPhi = SubStructure->GetConstituentPhi();
//         Candidate->ConstDeltaR = SubStructure->GetConstituentDeltaR();
//         Candidate->ConstAngle = SubStructure->GetConstituentAngle();

//         CandidateJet.user_info<HJetInfo>().PrintAllInfos(4);
//         Print(1, "Tag", CandidateJet.user_info<HJetInfo>().GetMaximalId(), CandidateJet.user_info<HJetInfo>().GetMaximalFraction(), CandidateJet.m());

        HasCandidate = 1;
    }

    if (HasCandidate) return 1;

    Print(2, "No Candidates found");

    return 0;

}
