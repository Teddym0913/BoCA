/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "EventSingleHadronicTagger.hh"
#include "plotting/Font.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int EventSingleHadronicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Events(event, [&](MultipletEvent<Decuplet532>& multiplet_event) {
        multiplet_event.SetTag(tag);
        return multiplet_event;
    }), tag);
}

std::vector<MultipletEvent<Decuplet532>> EventSingleHadronicTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Events(event, [&](MultipletEvent<Decuplet532>& multiplet_event) {
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        return multiplet_event;
    }), 1);
}

std::vector<MultipletEvent<Decuplet532>> EventSingleHadronicTagger::Events(Event const& event, std::function<MultipletEvent<Decuplet532>(MultipletEvent<Decuplet532> &)> const& function) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletEvent<Decuplet532>> multiplet_events;
    for (auto const & decuplet : signature_reader_.Multiplets(event)) {
        MultipletEvent<Decuplet532> multiplet_event(decuplet, event, jets);
        multiplet_events.emplace_back(function(multiplet_event));
    }
    return multiplet_events;
}
std::string EventSingleHadronicTagger::Name() const
{
    return "EventSingleHadronic";
}
std::string EventSingleHadronicTagger::LatexName() const
{
    return Formula("T_{h}t_{l}h");
}

}

}
