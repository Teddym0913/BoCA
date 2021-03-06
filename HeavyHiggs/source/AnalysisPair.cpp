#include "AnalysisPair.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace fusionpair
{

std::string Name(Process process)
{
    switch (process) {
    case Process::bb : return "bb";
    case Process::cc : return "cc";
    case Process::jj : return "jj";
    case Process::qq : return "qq";
    case Process::gg : return "gg";
    case Process::Hbb : return "Hbb";
    case Process::ttbb : return "ttbb";
    case Process::ttcc : return "ttcc";
    case Process::ttjj : return "ttjj";
    case Process::ttqq : return "ttqq";
    case Process::ttgg : return "ttgg";
    default:
        ERROR("ProcessName", "unhandeld case");
        return "";
    }
}
std::string Name(Production production)
{
    switch (production) {
    case Production::Associated : return "llbb_";
    case Production::DYP : return "pp_z_";
    case Production::VBF : return "VBF_";
    default:
        ERROR("ProductionChannelName", "unhandeld case");
        return "";
    }
}
std::string Name(Detector detector_type)
{
    switch (detector_type) {
    case Detector::LHC : return "14TeV";
    case Detector::FHC : return "100TeV";
    case Detector::LE : return "LE";
    default:
        ERROR("Detector Name", "unhandeld case");
        return "";
    }
}
}

}
