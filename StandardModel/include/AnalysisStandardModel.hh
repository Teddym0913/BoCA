#pragma once

#include "Analysis.hh"
#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Standard Model analyses
 *
 */
namespace standardmodel
{

enum class Process
{
    tt, tt_lep, tt_had, hh, hh_bb, zz, zz_bb, ww, bb, cc, qq, gg
};

std::string Name(Process process);

std::string NiceName(Process process);


enum class Collider
{
    LHC, FHC, LE
};

std::string Name(Collider collider);

/**
 *
 * @brief Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisStandardModel : public Analysis<Tagger>
{

protected:

    Momentum LowerPtCut() const {
        return 1000. * GeV;
        return 350. * GeV;
        return 700. * GeV;
        return 800. * GeV;
        return 500. * GeV;
        return 1200. * GeV;
    }

    long EventNumberMax() const override {
        return 5000;
        return 1000;
        return 100;
    }

    int BackgroundFileNumber() const {
        return 1;
        return 2;
        return 4;
        return 5;
        return 10;
    }

    Collider collider_type() const {
        return Collider::LE;
        return Collider::LHC;
        return Collider::FHC;
    }

    Momentum UpperPtCut() const {
        switch (Int(LowerPtCut())) {
        case 700 : return 1000. * GeV;
        case 1000 : return 1500. * GeV;
        case 1200 : return 1500. * GeV;
        case 500: return 1000. * GeV;
        default :
            Error("no pt upper cut");
            return 0;
        }
    }

    Momentum MadGraphCut() const {
        switch (Int(LowerPtCut())) {
        case 500: return 500. * GeV;
        case 700 : return 500. * GeV;
        case 1000 : return 1000. * GeV;
        case 1200 : return 1000. * GeV;
        default :
            Error("no madgraph cut");
            return 0;
        }
    }

    Momentum LowerQuarkCut() const {
        return LowerPtCut() * 0.9;
    }

    Momentum UpperQuarkCut() const {
        return UpperPtCut() * 1.1;
    }

    void NewFile(Tag tag, Process process) {
        boca::AnalysisBase::NewFile(tag, FileName(process), NiceName(process));
    }

    std::string FileName(Process process) const {
        return Name(process) + "_" + boca::Name(MadGraphCut()) + "";
    }

    std::string FilePath() const {
        return this->working_path_ + "../";
    }

};

}

}
