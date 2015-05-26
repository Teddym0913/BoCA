# pragma once

# include "Analysis.hh"
# include "EventNeutralTagger.hh"

namespace heavyhiggs
{

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisNeutral : public analysis::Analysis
{

public:

  using analysis::Analysis::Analysis;

    /**
     * @brief Constructor
     *
     */
//     AnalysisNeutral();

//     analysis::BottomTagger bottom_tagger_;
//     analysis::JetPairTagger jet_pair_tagger;
//     analysis::HWSemiTagger w_semi_tagger;
//     analysis::HWTagger w_hadronic_tagger;
//
// //     analysis::HTopLeptonicTagger TopLeptonicTagger;
//     analysis::TopHadronicTagger top_hadronic_tagger;
//     analysis::HTopSemiTagger top_semi_tagger;
//
// //     analysis::HHeavyHiggsLeptonicTagger HeavyHiggsLeptonicTagger;
// //     analysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;
//     analysis::HeavyHiggsSemiTagger heavy_higgs_semi_tagger;
//
// //     EventLeptonicTagger eventLeptonicTagger;
// //     EventHadronicTagger eventHadronicTagger;
//
//     SignatureNeutralTagger SignatureSemiTagger;
//     EventNeutralTagger eventSemiTagger;

//     std::string StudyName(const analysis::HAnalysis::HTagger Tagger) const;

//     void PrepareReader(const analysis::HAnalysis::HTagger Tagger, const analysis::HAnalysis::Tag Tag);

    void SetTrees();

    std::vector<analysis::File> Files(const analysis::Object::Tag tag);

    inline std::string ProjectName() const {
//        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV-Eta2.5";
        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }

    inline std::string ProcessName() const {
        return "Neutral";
    }

    // in GeV
    inline int Mass() const {
        //     return 300;
        //     return 400;
//         return 500;
        //     return 600;
        //     return 700;
//             return 800;
        //     return 900;
//         return 1000;
         return 2000;
//            return 3000;
//         return 4000;
//                 return 5000;
//                return 6000;
//             return 7000;
//         return 8000;
//             return 9000;
//                 return 10000;
//                 return 12000;
//                 return 15000;
//                return 20000;
    }

    // in GeV
    inline int PreCut() const {
      switch (collider_type()) {
        case LHC :
          switch (Mass()) {
            case 500 :
              return 0;
            case 1000 :
              return 250;
            case 2000 :
              return 250;
            case 3000 :
              return 250;
            default :
              return 0;
          }
            case LE :
              switch (Mass()) {
                case 500 :
                  return 0;
                case 1000 :
                  return 300;
                case 2000 :
                  return 300;
                case 4000 :
                  return 1500;
                case 6000 :
                  return 2500;
                case 10000 :
                  return 2500;
                case 15000 :
                  return 2500;
                case 20000 :
                  return 2500;
                default :
                  return 0;
              }
                default :
                  return 0;
      }
//         return 0;
        //     return 30;
        //     return 80;
// return 100;
        //     return 150;
//         return 250;
//              return 300;
//            return 1000;
//         return 1500;
//        return 2000;
//         return 2500;
    }

    inline int EventNumberMax() const {
//            return 10000000;
//                   return 1000000;
//         return 100000;
        return 10000;
//                 return 1000;
//                         return 500;
//                         return 10;
    };



    enum ColliderType {LHC, FHC, LE};


    inline ColliderType collider_type() const {
         return LHC;
//       return FHC;
//        return LE;
    }

    float MissingEt() {
        switch (collider_type()) {
        case LHC :
            return 30;
        case LE :
            return 60;
        default :
            return 0;
        }
    }

    float LeptonPt() {
        switch (collider_type()) {
        case LHC :
            return 50;
        case LE :
            return 100;
        default :
            return 0;
        }
    }


    inline int BackgroundFileNumber() const {
        switch (collider_type()) {
        case LHC :
            switch (PreCut()) {
            case  0 :
                return 127;
            case  250 :
                return 41;
                //                 return 1; // < this must be removed !!
            default :
                return 1;
            }
        case LE :
            switch (PreCut()) {
            case  0 :
                return 118;
//                 return 1; // < this must be removed !!
            case  100 :
                return 15;
            case  250 :
                return 15;
            case  300 :
                return 110;
//                 return 1; // < this must be removed !!
            case  1000 :
                return 32;
            case  1500 :
                return 34;
            case  2000 :
                return 26;
            case  2500 :
                return 11;
            default :
                return 1;
            }
            default :
              return 1;
        }
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt};

    // in fb
    float SignalCrosssection() const {
        switch (collider_type()) {
        case LHC:
            switch (Mass()) {
            case 500:
                return 25.528929726502543;
            case 1000:
                return 1.2783507034600217;
            case 2000:
                return 0.021907574118663196;
            default:
                Print(kError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
              case 500:
                return 973.5805772514352;
              case 1000:
                return 123.02005671222373;
              case 1500:
                return 28.624904980998327;
              case 2000:
                return 9.485582085140349;
              case 3000:
                return 1.7540841248835577;
              case 4000:
                return 0.4851939478031553;
              case 5000:
                return 0.16696738296715652;
              case 6000:
                return 0.06731697180862359;
              case 7000:
                return 0.029372932414373627;
              case 8000:
                return 0.014255221936825225;
              case 10000:
                return 0.0038428602375120795;
              case 12000:
                return 0.0012219523755405267;
              case 15000:
                return 0.00026507004708327343;
              case 20000:
                return 0.000028218388829563033;
            default:
                Print(kError,  "Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Print(kError,  "Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    inline analysis::File BackgroundFile(const ProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    analysis::File BackgroundFile(const ProcessType Background, const int FileSum) const {
        std::string FileName = ProcessName(Background) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV";
        Strings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
            FileNames.emplace_back(FileName + "_" + std::to_string(FileNumber));
        }
        return analysis::File(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const ProcessType Process) const {
        return ProcessName(Process) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
    }

    float BackgroundCrosssection(const ProcessType Process) const {
        switch (collider_type()) {
        case LHC :
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 97.54 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                };
            case 30 :
                switch (Process) {
                case ttbb :
                    return 298.2;
                case ttcc:
                    return 264.6;
                case ttjj:
                    return 9999999999;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                };
            case 80 :
                switch (Process) {
                case ttbb :
                    return 89.32;
                case ttcc:
                    return 78.42;
                case ttjj:
                    return 9999999999;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 250 :
                switch (Process) {
                case tt :
                    return 5.698 * 2 * 1000;
                default :
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        case FHC:
            switch (PreCut()) {
            case 30 :
                switch (Process) {
                case ttbb :
                    return 2990;
                case ttcc:
                    return 2684;
                case ttjj:
                    return 9999999999;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 80 :
                switch (Process) {
                case ttbb :
                    return 1171.6;
                case ttcc:
                    return 1042.0;
                case ttjj:
                    return 9999999999;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Process) {
                case ttbb :
                    return 605.199003171 * 2;
                case ttcc:
                    return 468.061778817 * 2;
                case ttjj:
                    return 61.9287096863 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 300 :
                switch (Process) {
                case ttbb :
                    return 242;
                case ttcc:
                    return 176;
                case ttjj:
                    return 26000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        case LE:
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 3564 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Process) {
                case ttbb :
                    return 688;
                case ttcc:
                    return 534;
                case ttjj:
                    return 70289;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 300 :
                switch (Process) {
                case ttbb :
                    return 263;
                case ttcc:
                    return 192.82;
                case ttjj:
                    return 28200;
                case tt :
                    return 178.1 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1000 :
                switch (Process) {
                case tt :
                    return 1.532 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1500 :
                switch (Process) {
                case tt :
                    return 0.2524 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2000 :
                switch (Process) {
                case tt :
                    return 0.09014 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2500 :
                switch (Process) {
                case tt :
                    return 0.0222 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        default:
            Print(kError, "Background Crosssection",  "unhandled case");
            return 1;
        }
    }

    std::string ColliderName(const ColliderType Collider) const {
        switch (Collider) {
        case LHC :
            return "14TeV";
        case FHC:
            return "100TeV";
        case LE:
            return "LE";
        default:
            Print(kError, "unhandled case");
            return "";
        }
    }

    std::string ProcessName(const ProcessType Process) const {
        switch (Process) {
        case Hbb:
            return "H0bb-ljbbbb";
        case ttbb :
            return "ttbb-ljbbbb";
        case ttcc:
            return "ttcc-ljbbcc";
        case ttjj:
            return "ttjj-ljbbjj";
        case tt:
            return "tt_inc";
        default:
            Print(kError, "unhandled case");
            return "";
        }
    }

    analysis::JetTag jet_tag;

    analysis::Reader BottomReader;
    analysis::Reader JetPairReader;
    analysis::Reader WSemiReader;
    analysis::Reader WHadronicReader;
    analysis::Reader TopLeptonicReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader HeavyHiggsLeptonicReader;
    analysis::Reader SignatureSemiReader;
    analysis::Reader eventSemiReader;
    analysis::Reader eventLeptonicReader;

//     void NewBranches(ExRootTreeWriter &tree_writer, const analysis::HAnalysis::HTagger tagger);

    /**
     * @brief Main Analysis function
     *
     */
    int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag);

//     bool GetBottomTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetBottomReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWSemiTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWSemiReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWReader(analysis::Event &event, const Tag Tag);
//     bool GetJetPairTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetJetPairReader(analysis::Event &event, const Tag Tag);
//     bool GetTopLeptonicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetTopLeptonicReader(analysis::Event &event, const Tag Tag);
//     bool GetTopHadronicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetTopSemiTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetTopHadronicReader(analysis::Event &event, const Tag Tag);
//     bool GetTopSemiReader(analysis::Event &event, const Tag Tag);
//     bool GetHeavyHiggsHadronicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsLeptonicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsLeptonicReader(analysis::Event &event, const Tag Tag);
//     bool GetHeavyHiggsSemiTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag);
//     bool GeteventLeptonicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GeteventHadronicTag(analysis::Event &event, const Tag Tag);
//
//     bool GeteventSemiTag(analysis::Event &event, const Tag Tag);
//
//     bool GetSignatureSemiTag(analysis::Event &event, const Tag Tag);
//     bool GetSignatureSemiReader(analysis::Event &event, const Tag Tag);
//
//     bool GeteventSemiReader(analysis::Event &event, const Tag Tag);
//     bool GeteventLeptonicReader(analysis::Event &event, const Tag Tag);


};

}