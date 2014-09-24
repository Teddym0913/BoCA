# include "HAnalysisHeavyHiggsPgs.hh"

HAnalysisHeavyHiggsPgs::HAnalysisHeavyHiggsPgs()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggsPgs";

    EventNumberMax = 10000;

    Cut = 0;

}

void HAnalysisHeavyHiggsPgs::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    FileVector.push_back(new HFileFolder("Signal_5f"));
    FileVector.push_back(new HFileFolder("5f_10k_Pt20"));

//     FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    FileVector.front()->FileSuffix = "_PGS.root";
    FileVector.front()->TreeString = "LHCO";

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysisHeavyHiggsPgs::NewFile()
{

    Print(0, "New File");


    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());


    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void HAnalysisHeavyHiggsPgs::CloseFile()
{
    Print(0, "Close File");

    if (Cut) {

        Print(0, "EventCounter", EventCounter);
        Print(0, "JetCounter", JetCounter);
        Print(0, "DeltaEtaCounter", DeltaEtaCounter);
        Print(0, "BMassCounter", BMassCounter);
        Print(0, "Jet2Counter", Jet2Counter);
        Print(0, "TMassCounter", TMassCounter);

    }

}


bool HAnalysisHeavyHiggsPgs::Analysis()
{

    Print(1, "Analysis");

    Event->GetJets();

    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;

    Print(1, "BJet Sum", BJets.size());

//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
// 
//         Print(1, "BJet Pt", BJets[BJetNumber].pt());
// 
//     }
// 
// //     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
// //
// //         if (BJets[BJetNumber].pt() < 1 || BJets[BJetNumber].pt() > 10000) {
// //
// //             BJets.erase(BJets.begin() + BJetNumber);
// //
// //         }
// //     }
// 
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](PseudoJet Jet) {
//         return Jet.pt() > 1000000;
//     }), BJets.end());
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](PseudoJet Jet) {
//         return Jet.pt() < 1;
//     }), BJets.end());
// 
//     Print(1, "BJet Sum", BJets.size());
// 
//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
// 
//         Print(1, "BJet Pt", BJets[BJetNumber].pt());
// 
//     }



    if (BJets.size() > 1) {

        for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {

            Print(1, "BJetNumber", BJetNumber);

            for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {

                Print(1, "BJetNumber2", BJetNumber2);

                PseudoJet FrontJet, BackJet;

                if (BJets[BJetNumber].eta() > BJets[BJetNumber2].eta()) {

                    FrontJet = BJets[BJetNumber];
                    BackJet = BJets[BJetNumber2];

                } else if (BJets[BJetNumber].eta() < BJets[BJetNumber2].eta()) {

                    FrontJet = BJets[BJetNumber2];
                    BackJet = BJets[BJetNumber];

                } else {

                    Print(0, "Comparison broken");

                }

                float FrontPt = FrontJet.pt();
                float FrontEta = FrontJet.eta();
                float FrontPhi = FrontJet.phi_std();
                Print(1, "FrontPt", FrontPt);
                Print(1, "FrontEta", FrontEta);
                Print(1, "FrontPhi", FrontPhi);

                float BackEta = BackJet.eta();
                float BackPt = BackJet.pt();
                float BackPhi = BackJet.phi_std();

                Print(1, "BackPt", BackPt);
                Print(1, "BackEta", BackEta);
                Print(1, "BackPhi", BackPhi);

                float InvMass = (FrontJet + BackJet).m();
                float DeltaEta = FrontEta - BackEta;

                Print(1, "InvMass", InvMass);
                Print(1, "DeltaEta", DeltaEta);

                float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);

                HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

                HeavyHiggs->BottomEta1 = FrontEta;
                HeavyHiggs->BottomEta2 = BackEta;
                HeavyHiggs->BottomDeltaEta = DeltaEta;

                HeavyHiggs->BottomPhi1 = FrontPhi;
                HeavyHiggs->BottomPhi2 = BackPhi;
                HeavyHiggs->BottomDeltaPhi = DeltaPhi;

                HeavyHiggs->BottomPt1 = FrontPt;
                HeavyHiggs->BottomPt2 = BackPt;
                HeavyHiggs->BottomInvMass = InvMass;

                HeavyHiggs->BTag = BJets.size();
                HeavyHiggs->JetNumber = Event->Jets->JetVector.size();

            }

        }

        return 1;

    } else {

        Print(1, "Just 1 B Jet");

    }

    return 0;

}