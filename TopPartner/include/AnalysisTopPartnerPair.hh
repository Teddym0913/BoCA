/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisPair : public AnalysisNaturalness<Tagger>
{

    std::string AnalysisName() const override {
        INFO0;
        return "Naturalness-Pair-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-new-event";
    }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TT);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttBjj);
            this->NewFile(tag, Process::ttBB);
            break;
        }
    }

};

}

}
