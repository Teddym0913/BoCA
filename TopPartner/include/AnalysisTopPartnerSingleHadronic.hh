/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "EventSingleHadronicTagger.hh"
#include "Debug.hh"

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

public:

    AnalysisSingleHadronic() {
        Info();
        this->tagger().SetAnalysisName(ProjectName());
    }

protected:

    std::string ProjectName() const final {
        Info();
        return "Naturalness-Single-Hadronic-" + Name(DetectorGeometry::detector_type()) + "-" + boca::Name(this->Mass())
               + "-pt";
//         + "-problems";
//         + "-wrong";
//         + "-full";
//         + "newbg";
//                + "type";
    }

    void SetFiles(Tag tag) final {
        Info();
        switch (tag) {
        case Tag::signal :
            if (this->template TaggerIs<TopPartnerLeptonicTagger>()) this->NewFile(tag, Process::TT);
            else this->NewFile(tag, Process::TthHad);
            break;
        case Tag::background :
            if (this->template TaggerIs<TopPartnerLeptonicTagger>()) this->NewFile(tag, Process::TthHad);
            else
//             if (!this->template TaggerIs<TopPartnerHadronicTagger>())
                this->NewFile(tag, Process::TT);
            this->NewFile(tag, Process::ttBB);
            this->NewFile(tag, Process::ttBjj);
            break;
        }
    }

private:
//         TopPartnerHadronicTagger partner_tagger;

    int PassPreCut(Event const& event, Tag tag) const final {
        Info();
//       if(tag == Tag::signal){
//         Jets partner = partner_tagger.Particles(event);
//         if(partner.empty()) return 0;
//       }
//       static int counter = 0;
//       ++counter;
//     Error(counter);

//      Error();
//      this->PrintGeneratorLevel(event);



//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if (jets.size() < 3) return 0;
//         if (jets.at(2).pt() < this->JetPreCut()) return 0;
//
//
//         Jets particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//         Jets tops = CopyIfParticle(particles, Id::top);
//         Jets higgs = CopyIfParticle(particles, Id::higgs);
//         Jets vectors = CopyIfParticles(particles, Id::Z, Id::W);
//         Jets partner = CopyIfParticle(particles, Id::top_partner);
//         if (tag == Tag::signal && partner.size() != 1) {
//             return 0;
//         }
//         if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) {
//             return 0;
//         }
        return 1;
    }

};

}

}
