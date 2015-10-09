/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "SignatureSingleHadronicTagger.hh"
#include "Event.hh"
// #define DEBUG
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int SignatureSingleHadronicTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = partner_reader_.Multiplets(event);
//     Jets top_partner = partner_reader_.Tagger().Particles(event);
//     quintets = BestMatches(quintets, top_partner, tag);
//     Error(top_partner.size(), quintets.size());

    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
//     Jets top = top_reader_.Tagger().Particles(event);
//     triplets = BestMatches(triplets, top, tag);
//     Error(top.size(), triplets.size());

    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
//     Jets higgs = higgs_reader_.Tagger().Particles(event);
//     doublets = BestMatches(doublets, higgs, tag);
//     Error(higgs.size(), doublets.size());

//     std::vector<Decuplet532> decuplets = triples(quintets, triplets, doublets, [&](Quintet const & quintet, Triplet const & triplet, Doublet const & doublet) {
//         Decuplet532 decuplet(quintet, triplet, doublet);
//         if (decuplet.Overlap()) throw "overlap";
//         decuplet.SetVetoBdt(veto_reader_.Bdt(Quintet(triplet, boson_reader_.Multiplet(doublet, pre_cuts))));
//         decuplet.SetTag(tag);
//         return decuplet;
//     });

    std::vector<Decuplet532> decuplets;
    for (auto const & doublet : doublets) {
        Doublet doublet_2 = boson_reader_.Multiplet(doublet, pre_cuts);
        for (auto const & triplet : triplets) {
            float veto = veto_reader_.Bdt(Quintet(triplet, doublet_2));
            for (auto const & quintet : quintets) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                decuplet.SetVetoBdt(veto);
                decuplet.SetTag(tag);
                decuplets.emplace_back(decuplet);
            }
        }
    }

    Info(decuplets.size());
    return SaveEntries(decuplets, 1);
}

std::vector<Decuplet532> SignatureSingleHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, pre_cuts, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);

}

// std::vector<Decuplet532> SignatureSingleHadronicTagger::Decuplets(boca::Event const& event, std::function< Decuplet532(Decuplet532&)> const& function) const
// {
//   return pairs(partner_reader_.Multiplets(event) , veto_reader_.Multiplets(event), [&](Quintet const & quintet, Quintet const & veto) {
//         Decuplet532 decuplet(quintet, veto.Triplet(), veto.Doublet());
//         if (decuplet.Overlap()) throw "overlap";
//         decuplet.SetVetoBdt(veto.Bdt());
//         Error(decuplet.VetoBdt());
//         return function(decuplet);
//     });
// }

std::vector<Decuplet532> SignatureSingleHadronicTagger::Decuplets(Event const& event, PreCuts const& pre_cuts, std::function<Decuplet532(Decuplet532&)> const& function) const
{
    std::vector<Decuplet532> decuplets;
    for (auto const & doublet : higgs_reader_.Multiplets(event)) {
        Doublet doublet_2 = boson_reader_.Multiplet(doublet, pre_cuts);
        for (auto const & triplet : top_reader_.Multiplets(event)) {
            float veto = veto_reader_.Bdt(Quintet(triplet, doublet_2));
            for (auto const & quintet : partner_reader_.Multiplets(event)) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                decuplet.SetVetoBdt(veto);
                decuplets.emplace_back(function(decuplet));
            }
        }
    }
    return decuplets;
}

}

}
