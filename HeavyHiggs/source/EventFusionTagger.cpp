#include "EventFusionTagger.hh"
#include "Event.hh"
#include "multiplets/Particles.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

int EventFusionTagger::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons().leptons();
    auto sextets = heavy_higgs_semi_reader_.Multiplets(event);
    auto HiggsParticles = event.Partons().GenParticles();
    auto Even = CopyIfFamily(HiggsParticles, Id::heavy_higgs, Id::gluon);
    auto Odd = CopyIfFamily(HiggsParticles, Id::CP_odd_higgs, Id::gluon);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    Particle HiggsBoson;
    if (tag == Tag::signal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else ERROR("Where is the Higgs?", HiggsParticles.size());
        SortedByMinDeltaRTo(sextets, HiggsParticles.front());
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }
//     std::vector<EventFusionBranch> eventSemiBranches;
    if (sextets.empty()) return 0;
    if (tag == Tag::signal && sextets.size() > 1) {
        ERROR("more than one event", sextets.size());
        std::sort(sextets.begin(), sextets.end());
        sextets.erase(sextets.begin() + 1, sextets.end());
    }
    MultipletEvent<Sextet> sextet_event(sextets.front(), event, jets);
    sextet_event.SetTag(tag);
    std::vector<MultipletEvent<Sextet>> sextet_events;
    sextet_events.emplace_back(sextet_event);
    return SaveEntries(sextet_events);
}

std::vector<MultipletEvent<Sextet>> EventFusionTagger::Multiplets(Event const& event, PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    auto sextets = heavy_higgs_semi_reader_.Multiplets(event);
    auto jets = bottom_reader_.Jets(event);
    auto leptons = event.Leptons().leptons();
    std::vector<MultipletEvent<Sextet>> sextet_events;
    for (auto const & sextet : sextets) {
        MultipletEvent<Sextet> multiplet_event(sextet, event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        sextet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(sextet_events,1);
}
std::string EventFusionTagger::Name() const
{
    return "EventFusion";
}

}

}
