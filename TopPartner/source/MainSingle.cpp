#include "AnalysisTopPartnerSingle.hh"
#include "EventSingleTagger.hh"

int main()
{
    boca::naturalness::AnalysisSingle<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();
    bottom_analysis.RunPlots();

    boca::naturalness::AnalysisSingle<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunNormal();

    boca::naturalness::AnalysisSingle<boca::BosonTagger> boson_analysis;
    boson_analysis.RunNormal();

    boca::naturalness::AnalysisSingle<boca::WHadronicTagger> w_hadronic_analysis;
    w_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisSingle<boca::TopHadronicTagger> top_hadronic_analysis;
    top_hadronic_analysis.RunNormal();

    boca::naturalness::AnalysisSingle<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

    boca::naturalness::AnalysisSingle<boca::naturalness::TopPartnerLeptonicTagger> top_partner_leptonic_analysis;
    top_partner_leptonic_analysis.RunFullEfficiency();

//     boca::naturalness::AnalysisSingle<boca::naturalness::TopPartnerTopPairTagger> top_partner_hadronic_analysis;
//     top_partner_hadronic_analysis.RunFullEfficiency();
//     top_partner_hadronic_analysis.RunPlots();

    boca::naturalness::AnalysisSingle<boca::naturalness::SignatureSingleTagger> top_partner_pair_analysis;
    top_partner_pair_analysis.RunFullEfficiency();
    top_partner_pair_analysis.RunPlots();

    boca::naturalness::AnalysisSingle<boca::naturalness::EventSingleTagger> event_analysis;
    event_analysis.RunFullSignificance();
    event_analysis.RunPlots();
}

