#include "TopPartnerPairTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerPairTagger::TopPartnerPairTagger()
{
  Info();
    DefineVariables();
}

int TopPartnerPairTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets_2 = top_partner_leptonic_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets;
    for (const auto& quintet_1 :  quintets_1) {
        for (const auto& quintet_2 : quintets_2) {
            Decuplet55 decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }
    }
    return SaveEntries(decuplets,1);
}

std::vector<Decuplet55> TopPartnerPairTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets_2 = top_partner_leptonic_reader_.Multiplets(event);
    std::vector<Decuplet55> decuplets;
    for (const auto& quintet_1 :  quintets_1) {
        for (const auto& quintet_2 : quintets_2) {
            Decuplet55 decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetBdt(Bdt(decuplet, reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}

}
