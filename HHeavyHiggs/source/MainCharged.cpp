#include "HAnalysisChargedHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hheavyhiggs::HAnalysisCharged analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::HJetPairTagger:
//             analysis::Factory(Analysis.JetPairTagger);
//             break;
//         case analysis::HAnalysis::WHadronicTagger:
//             analysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HWSemiTagger:
//             analysis::Factory(Analysis.WSemiTagger);
//             break;
//         case analysis::HAnalysis::HTopLeptonicTagger:
// //             analysis::Factory(Analysis.TopLeptonicTagger);
//             break;
//         case analysis::HAnalysis::TopHadronicTagger:
//             analysis::Factory(Analysis.top_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HTopSemiTagger:
//             analysis::Factory(Analysis.TopSemiTagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsLeptonicTagger:
// //             analysis::Factory(Analysis.HeavyHiggsLeptonicTagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsHadronicTagger:
// //             analysis::Factory(Analysis.HeavyHiggsHadronicTagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsSemiTagger:
//             analysis::Factory(Analysis.ChargedHiggsSemiTagger);
//             break;
//         case analysis::HAnalysis::EventLeptonicTagger:
// //             analysis::Factory(Analysis.eventLeptonicTagger);
//             break;
//         case analysis::HAnalysis::EventHadronicTagger:
// //             analysis::Factory(Analysis.eventHadronicTagger);
//           break;
//         case analysis::HAnalysis::HSignatureSemiTagger:
//           analysis::Factory(Analysis.SignatureSemiTagger);
//           break;
//         case analysis::HAnalysis::EventSemiTagger:
//             analysis::Factory(Analysis.eventSemiTagger);
//             break;
// //         case analysis::HAnalysis::HChargedHiggsSemiTagger:
// //           analysis::Factory(Analysis.ChargedHiggsSemiTagger);
// //           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::EventLeptonicReader: {
//             analysis::Reader Reader(Analysis.eventLeptonicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         case analysis::HAnalysis::EventSemiReader: {
//           Analysis.SetTrees(Tagger,analysis::HAnalysis::kSignal);
            analysis::Reader Reader(tagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);


    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
    RunTagger(bottom_tagger, analysis::Tagger::kReader);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Tagger::kTrainer);
    RunTagger(w_hadronic_tagger, analysis::Tagger::kReader);

    analysis::HWSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(w_semi_tagger, analysis::Tagger::kReader);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer);
    RunTagger(top_hadronic_tagger, analysis::Tagger::kReader);

    analysis::HTopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(tops_semi_tagger, analysis::Tagger::kReader);

    analysis::HChargedHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader);

    analysis::HChargedJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    hheavyhiggs::HChargedSignatureSemiTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(signature_semi_tagger, analysis::Tagger::kReader);

    hheavyhiggs::HChargedeventSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;
}
