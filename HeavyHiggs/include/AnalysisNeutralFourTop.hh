#pragma once

#include "AnalysisHeavyHiggs.hh"

#include "JetPairTagger.hh"
#include "multiplets/Doublet.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

template<typename Tagger>
class AnalysisNeutralFourTop : public AnalysisHeavyHiggs<Tagger>
{

public:

    AnalysisNeutralFourTop() {
        DetectorGeometry::SetDetectorType(DetectorType::CMS);
    }

    std::string AnalysisName() const override {
        return  "NeutralFourTop-" + Name(this->Collider()) + "-" + boca::Name(this->Mass()) + "-new-bg";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::Htt);
            this->NewFile(tag, Process::Htwb);
            break;
        case Tag::background :
            if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, Process::Htt);
            if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, Process::Htwb);
            this->NewFile(tag, Process::tttt);
            this->NewFile(tag, Process::tttwb);
            this->NewFile(tag, Process::ttwbb);
            break;
        }
    }

    boca::Crosssection Crosssection(Process process) const override {
        switch (this->Collider()) {
        case Collider::LHC:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 0.911648_fb;
                case 700 : return 0.346647_fb;
                case 750 : return 0.307192_fb;
                case 800 : return 0.225386_fb;
                case 1000 : return 0.10028_fb;
                case 1500 : return 0.0168305_fb;
                case 2000 : return 0.00345315_fb;
                    DEFAULT(Int(this->Mass()), fb)
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return 0.471031_fb;
                case 700 : return 0.216664_fb;
                case 750 : return 0.188463_fb;
                case 800 : return 0.150792_fb;
                case 1000 : return 0.0758434_fb;
                case 1500 : return 0.0159789_fb;
                case 2000 : return 0.00384621_fb;
                    DEFAULT(Int(this->Mass()), fb)
                }
//             case Process::ttwwbb : return 2.126_fb;
//             case Process::ttwbb : return 0.13588_fb;
            case Process::tttt : return 0.4849_fb;
            case Process::tttwb : return 0.06012_fb;
            case Process::ttwbb :return  0.03284_fb;
                DEFAULT(Name(process), fb)
            };
        case Collider::FHC:
        case Collider::LE:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 152.154_fb;
                case 700 : return 79.3982_fb;
                case 800 : return 60.9656_fb;
                case 1000 : return 36.5579_fb;
                case 1500 : return 12.4039_fb;
                case 2000 : return 5.09533_fb;
                case 3000 : return 1.21763_fb;
                case 4000 : return 0.385975_fb;
                case 5000 : return 0.14659_fb;
                case 6000 : return 0.062513_fb;
                case 7000 : return 0.026579_fb;
                case 8000 : return 0.0132781_fb;
                case 10000 : return 0.00380676_fb;
                    DEFAULT(Int(this->Mass()), fb)
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return 117.041_fb;
                case 700 : return 79.5743_fb;
                case 800 : return 66.4861_fb;
                case 1000 : return 47.8374_fb;
                case 1500 : return 23.1449_fb;
                case 2000 : return 12.5153_fb;
                case 3000 : return 4.60995_fb;
                case 4000 : return 2.01434_fb;
                case 5000 : return 0.975944_fb;
                case 6000 : return 0.509747_fb;
                case 7000 : return 0.256938_fb;
                case 8000 : return 0.148312_fb;
                case 10000 : return 0.0539546_fb;
                    DEFAULT(Int(this->Mass()), fb)
                }
            case Process::ttwwbb : return 396_fb;
            case Process::ttwbb : return 1.3204_fb;
                DEFAULT(Name(process), fb)
            }
            DEFAULT(Name(this->Collider()), fb)
        }
    }

private:

    int PassPreCut(Event const&, Tag) const override {
//         std::vector<Particle> Particles = event.Partons().GenParticles();
//
//         std::vector<Particle> Tops = CopyIfParticle(Particles, Id::top);
//         std::vector<Particle> Bottoms = CopyIfParticle(Particles, Id::bottom);
//
//         if (event.Hadrons().MissingEt().Pt() < this->MissingEt()) return 0;
//         std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
//         if (Leptons.size() < 2) return 0;
//         int positive_lepton = 0;
//         int negative_lepton = 0;
//         for (auto const & lepton : Leptons) {
//             if (lepton.Pt() > this->LeptonPt() && lepton.Info().Charge() > 0) ++positive_lepton;
//             if (lepton.Pt() > this->LeptonPt() && lepton.Info().Charge() < 0) ++negative_lepton;
//         }
//
//         if (positive_lepton < 2 && negative_lepton < 2) return 0;
//         if ((positive_lepton + negative_lepton) > 2) return 0;
//
//         std::vector<Jet> jets = event.Hadrons().Jets();
//         if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
