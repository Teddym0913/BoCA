#include "HeavyHiggsTauTagger.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int HeavyHiggsTauTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    std::vector<Jet> jets;// = tau_reader_.Multiplets(event);
    INFO(jets.size());
    auto MissingEt = event.Hadrons().MissingEt();
    auto TauParticles = event.Partons().GenParticles();
    TauParticles = CopyIfParticle(TauParticles, Id::tau);
//     TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(Id::tau)), TauParticles.end());
    CHECK(TauParticles.size() == 1, TauParticles.size());
    auto HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(Id::charged_higgs)), HiggsParticles.end());
    CHECK(HiggsParticles.size() == 1, HiggsParticles.size());
    for (auto const & Particle : TauParticles) {
        SortedByMinDeltaRTo(jets, Particle);
        if (jets.front().DeltaRTo(Particle) < 0.4_rad) jets.front().Info().SetTag(Tag::signal);
    }
    std::vector<Jet>NewCleanJets;
    for (auto const & jet : jets) {
        if (jet.Info().Tag() != tag) continue;
        NewCleanJets.emplace_back(jet);
    }
    std::vector<Doublet> doublets;
    for (auto const & Jet : NewCleanJets) {
        Doublet Predoublet(Jet, MissingEt);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         std::sort(Postdoublets.begin(), Postdoublets.end(), MinDeltaR(HiggsParticles.front()));
//         if (Tag == Tag::signal && Postdoublets.size() > 1) Postdoublets.erase(Postdoublets.begin() + 1, Postdoublets.end());
//         if (Tag == HBackground && !Postdoublets.empty()) Postdoublets.erase(Postdoublets.begin());
//         for (auto & Postdoublet : Postdoublets) {
        Predoublet.SetTag(tag);
        doublets.emplace_back(Predoublet);
//         }
    }
    INFO(doublets.size());
    return SaveEntries(doublets);
}

std::vector<Doublet>  HeavyHiggsTauTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    std::vector<Jet> jets;// = tau_reader_.Multiplets(event);
    INFO(jets.size());
    auto missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (auto const & jet : jets)  {
        Doublet pre_doublet(jet, missing_et);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         for (auto & Postdoublet : Postdoublets) {
//             if (Postdoublet.Mass() < 10) continue;
        pre_doublet.SetBdt(Bdt(pre_doublet, reader));
        doublets.emplace_back(pre_doublet);
//         }
    }
    return doublets;
}

}

}
