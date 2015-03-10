# include "HAnalysisBTagger.hh"

hbtagger::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

//     //JetTag = new hanalysis::HJetTag();

    SubStructure = new hanalysis::HDoublet();

}

hbtagger::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    //delete JetTag;

    delete SubStructure;

}

HStrings hbtagger::HAnalysis::GetStudyNames() const
{

    return  {"Bottom", "LightJet", "Test"};

}

std::vector<hanalysis::HFile *> hbtagger::HAnalysis::GetFiles(const std::string &Name)
{
    Print(HNotification, "Set File Vector", Name);

    std::vector<hanalysis::HFile *> NewFiles;

//     hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.push_back(Test3);
//     return Files;

//     hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
//     Files.push_back(Test4);

    hanalysis::hdelphes::HFile *Background = new hanalysis::hdelphes::HFile("pp-bbtt-bblvlv", "background");
    Background->SetCrosssection(3.215); // pb
    Background->SetError(0.012); // pb
//     Files.push_back(Background);

    hanalysis::hdelphes::HFile *Even = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(30.02079); // pb
    Even->SetError(0.000078); // pb
//     Even->TagString="tag_2";
//     Files.push_back(Even);

    hanalysis::hdelphes::HFile *Mix = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(30.01172); // pb
    Mix->SetError(0.000045); // pb
//     Mix->TagString="tag_2";
//     Files.push_back(Mix);

    hanalysis::hdelphes::HFile *Odd = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(30.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
//     Files.push_back(Odd);

    hanalysis::hdelphes::HFile *Test = new hanalysis::hdelphes::HFile("pp-hjj-bbjj");
    NewFiles.push_back(Test);

//     hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
//     Files.push_back(Test2);

//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.push_back(Signal);

    Print(HNotification, "Files prepared");

    return NewFiles;

}


void hbtagger::HAnalysis::NewBranches(ExRootTreeWriter *NewTreeWriter)
{
    Print(HNotification, "New File");

    BTaggerBranch = NewTreeWriter->NewBranch("BTagger", HBTaggerBranch::Class());

}


// int hbtagger::HJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
//
//     Print(HDebug, "Get Branch Id", ParticleId, BranchId);
//
//     if (
//         HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = ParticleId;
//     } else if (
//         RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles)
//     ) {
//         BranchId = IsrId;
//     }
//
//     Print(HDebug, "Branch Id", BranchId);
//
//     return BranchId;
//
// }

bool hbtagger::HAnalysis::Analysis(hanalysis::HEvent &Event, const std::string &Name)
{

    Print(HInformation, "Analysis", Name);
    HJets Jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (Name == "Bottom") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            Print(HInformation, "Truth Level", (*it).user_info<hanalysis::HJetInfo>().MaximalId());
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().MaximalId()) != BottomId || (*it).user_info<hanalysis::HJetInfo>().MaximalFraction() < .8) {
                it = Jets.erase(it);
            } else {
                ++it;
            }
        }

    } else if (Name == "LightJet") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().MaximalId()) == BottomId) {
                it = Jets.erase(it);
            } else {
                ++it;
            }
        }

    }


    if (Jets.size() < 1) {
        Print(HInformation, "Not Jets");
        return 0;
    }
    Print(HInformation, "Number Jets", Jets.size());

    for (const auto & Jet : Jets) {

        HBTaggerBranch *BTagger = static_cast<HBTaggerBranch *>(BTaggerBranch->NewEntry());

        BTagger->JetMass = Jet.m();

        Print(HInformation, "Mass", Jet.m());
//         if (Jet.has_constituents()) {
//             BTagger->Pull = SubStructure->GetDiPolarity(Jet);
//             BTagger->DeltaR = SubStructure->GetDeltaR();
//         }
        if (Jet.has_user_info<hanalysis::HJetInfo>()) {
            Print(HInformation, "Has Info", BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().MaxDisplacement());
            BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
            BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().VertexMass();
            BTagger->VertexNumber = Jet.user_info<hanalysis::HJetInfo>().VertexNumber();
        }

//         HVectors ConstituentVectors = FirstPair.GetConstituents();
//         for (const auto & ConstituentVector : ConstituentVectors) {
//
//           if (std::abs(ConstituentVector.Rap()) > LargeNumber) {
//             Print(HError, "ERROR");
//             continue;
//           }
//
//             HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
//             Constituent->Rap = ConstituentVector.Rap();
//             Constituent->Phi = ConstituentVector.Phi();
//             Constituent->Pt = ConstituentVector.Pt();
//
//         }

    }

    return 1;

}