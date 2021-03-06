#include "AnalysisTopPartnerEffective.hh"
#include "../include/TruthLevel.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast | boca::Output::plot_hist)
{
    boca::naturalness::AnalysisEffective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::naturalness::TruthLevel>();
}

