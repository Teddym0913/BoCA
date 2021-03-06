#include "NewPartnerPairTagger.hh"
#include "generic/Exception.hh"
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int NewPartnerPairTagger::Train(Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto decuplets = Pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetTag(tag);
        return decuplet;
    });
    return SaveEntries(decuplets, 1);
}

std::vector<Decuplet55> NewPartnerPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    return Pairs(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    });
}
std::string NewPartnerPairTagger::Name() const
{
    return "NewPartnerPair";
}
std::string NewPartnerPairTagger::LatexName() const
{
    return "T_{h} T_{l}";
}

}

}
