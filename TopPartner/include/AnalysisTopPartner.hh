#pragma once

#include "Analysis.hh"
#include "Vector.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

enum class Process
{
    Tth,
    TT,
    ttBjj,
    tthBjj,
    TThh
};

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisNaturalness : public analysis::Analysis<Tagger>
{

public:

protected:

    long EventNumberMax() const override {
        return 1000;
        return 5000;
        return 3000;
        return 500;
        return 100;
        return 10;
    }

    std::string FilePath() const final {
        return "~/Projects/TopPartner/Analysis/";
    }

protected:

    int PreCut() const {
        return 0;
        return 200;
    }

    int JetPreCut() const {
        return 100;
        return 0;
    }

    int Mass() const {
        return 2000;
    }

    float Crosssection(Process process) const {
        float crosssection;
        switch (process) {
        case Process::Tth : crosssection = 0.004964;
            break;
        case Process::TT : crosssection = 0.264;
            break;
        case Process::ttBjj :
            switch (PreCut()) {
            case 0 : crosssection = 1.669;
                break;
            case 200 : crosssection = 0.1754;
                break;
            }
            break;
        case Process::tthBjj :
            switch (PreCut()) {
            case 0 : crosssection = 0.02535;
                break;
            case 200 : crosssection = 0.02535;
                break;
            }
            break;
        case Process::TThh : crosssection = 3.057e-05;
            break;
        }
        return crosssection * 2 * 1000;
    }

    std::string Name(Process process) const {
        switch (process) {
        case Process::TT : return "pp-TT-tthB-bbbbjjjjlv";
        case Process::ttBjj : {
            std::string name = "PP-ttBJJ";
            switch (PreCut()) {
            case 0 : return name + "-0GeV";
            case 200 : return name + "-200GeV";
            }
        }
        case Process::tthBjj : {
            std::string name = "PP-tthB";
            switch (PreCut()) {
            case 0 : return name + "-0GeV";
            case 200 : return name + "-200GeV";
            }
        }
        case Process::Tth : return "PP-Tth-ttBh";
        case Process::TThh : return "PP-TThh";
        default: Error("no case");
        }
    }

    std::string NiceName(Process process) const {
        switch (process) {
        case Process::TT : return "#tilde t_{h}#tilde t_{l}";
        case Process::ttBjj : return "t_{l}t_{h}Bjj";
        case Process::tthBjj : return "t_{l}t_{h}hBjj";
        case Process::Tth : return "#tilde t_{l}t_{h}h";
        case Process::TThh : return "#tilde t_{l}#tilde t_{h}hh";
        default: Error("no case");
        }
//         (" + std::to_string(PreCut()) + " GeV)";
    }

    void NewFile(Tag tag, Process process) {
        AnalysisBase::NewFile(tag, this->Name(process), this->Crosssection(process), this->NiceName(process));
    }

};

}

}
