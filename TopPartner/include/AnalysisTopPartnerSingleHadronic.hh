/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "EventSingleHadronicTagger.hh"
#include "VetoTopPartnerLeptonicTagger.hh"
#include "TopPartnerLeptonicNeutralTagger.hh"
#include "TopPartnerHadronicTagger.hh"
#define INFORMATION
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisSingleHadronic : public AnalysisNaturalness<Tagger>
{

protected:

    std::string AnalysisName() const override {
        INFO0;
        return "Single-Hadronic-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-smaller";
    }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<VetoTopPartnerLeptonicTagger>() || this->template TaggerIs<TopPartnerLeptonicNeutralTagger>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthHad);
            break;
        case Tag::background :
            if (this->template TaggerIs<VetoTopPartnerLeptonicTagger>() || this->template TaggerIs<TopPartnerLeptonicNeutralTagger>()) this->NewFile(tag, Process::TthHad);
            else if (!this->template TaggerIs<TopPartnerHadronicTagger>()){ this->NewFile(tag, Process::TT);
//             if (!this->template TaggerIs<VetoTopPartnerLeptonicTagger>() || !this->template TaggerIs<TopPartnerLeptonicNeutralTagger>()) {
                this->NewFile(tag, Process::ttBB);
                this->NewFile(tag, Process::ttBjj);
            }
            break;
        }
    }

private:
//         TopPartnerHadronicTagger partner_tagger;

    int PassPreCut(Event const& , Tag) const override {
        INFO0;
//       if(tag == Tag::signal){
//        std::vector<Jet> partner = partner_tagger.Particles(event);
//         if(partner.empty()) return 0;
//       }
//       static int counter = 0;
//       ++counter;
//     ERROR(counter);

//      ERROR0;
//      this->PrintGeneratorLevel(event);

//        std::vector<Jet> jets = SortedByPt(event.Hadrons().Jets());
//         if (jets.size() < 3) return 0;
//         if (jets.at(2).Pt() < this->JetPreCut()) return 0;
//
//
//        std::vector<Jet> particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//        std::vector<Jet> tops = CopyIfParticle(particles, Id::top);
//        std::vector<Jet> higgs = CopyIfParticle(particles, Id::higgs);
//        std::vector<Jet>vectors = CopyIfParticles(particles, Id::Z, Id::W);
//        std::vector<Jet> partner = CopyIfParticle(particles, Id::top_partner);
//         if (tag == Tag::signal && partner.size() != 1) {
//             return 0;
//         }
//         if (tops.size() < 2 || (higgs.empty() && vectors.empty())) {
//             return 0;
//         }
        return 1;
    }

};

}

}
