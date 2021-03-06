/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Result.hh"
#include "Tagger.hh"
#include "Observables.hh"
#include "physics/Rectangle.hh"

class TFile;
class TTree;

namespace boca
{

class Plots;
// class Result;
class Results;
class Plot;
class Graphs;
class InfoBranch;

/**
 * @brief Presents result of multivariant analysis
 *
 */
class PlottingBase
{

public:

    /**
     * @brief Constructor
     *
     */
//     PlottingBase(boca::Tagger& tagger);

    void TaggingEfficiency() const;

    void OptimalCuts() const;

    void RunPlots(Stage stage) const;

    void RunPlotHist() const;

private:

    Results ReadBdtFiles(boca::Stage stage) const;

    std::vector<Result> ReadBdtFile(TFile& export_file, Phase const& phase) const;

    Result BdtDistribution(const boca::Phase& phase, int tree_number, TFile& export_file) const;

    Result CutDistribution(const boca::Phase& phase, int tree_number, TFile& export_file) const;

    void DoPlot(Plots& signals, Plots& backgrounds, Stage stage) const;

    void PlotDetails(Plot& signal, Plot& background, Stage stage) const;

    std::vector<Plots> Import(Phase const& phase) const;

    std::vector<Plots> Import2() const;

    Plots PlotResult(TFile& file, int tree_number, const boca::Phase& phase) const;

    Plots PlotResult2(const Observable& variable, Tag tag, Plots& plots) const;

    Plots PlotResult3(const Observable& variable) const;

    Plot ReadTree(TTree& tree, std::string const& leaf_1_name, std::string const& leaf_2_name, Stage stage) const;

    Plot ReadTree2(TTree& tree, std::string const& leaf_name) const;

    void PlotHistogram(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    void PlotProfile(const Plot& signal, const Plot& background, Rectangle<double> const& range) const;

    std::vector<std::string> PlotAcceptanceGraph(Results const& results) const;

    std::string PlotCrosssectionsGraph(Results const& results) const;

    std::string PlotMDExperimentalGraph(Results const& results) const;

    std::string PlotSBvsSsqrtBGraph(Results const& results) const;

    std::string PlotHistograms(Results const& results) const;

    std::pair<boca::InfoBranch, int> InfoBranch(Phase const& phase, int tree_number) const;

    std::string BestValueTable(const boca::Result& signal, const std::vector< double >& x_values) const;

    std::string BestValueRow(const boca::Result& signal, const std::vector< double >& x_values, boca::Significance significance, int bin) const;

//     std::string ScalingTable(boca::Results& results) const;

//     std::string ScalingRow(const boca::Results& results, double factor) const;

    std::string EfficienciesTable(Results const& results, int bin) const;

    std::string EfficienciesRow(const Result& result, int index, Tag tag, int bin) const;

    std::string EfficienciesTableMI(Results const& results, int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const;

    std::string EfficienciesRowMI(const Result& result, int index, Tag tag, int bin, std::function<std::vector<Crosssection>(Result const&)> const& function) const;

    std::string EfficienciesRowMI(const Result& result, int index, Tag tag, int bin) const;

    std::string CutEfficiencyTable(Results const& results) const;

    std::string CutEfficiencyRow(Result const& result, int index, Tag tag) const;

    std::string TruthLevelCutTable(Results const& results) const;

    std::string TruthLevelCutRow(Result const& result, Tag tag) const;

    std::string PlotEfficiencyGraph(Results const& results) const;

    std::string PlotMDGraph(Results const& results) const;

    std::string PlotMIGraph(Results const& results) const;

    std::string PlotMISignificanceGraph(Results const& results) const;

    std::string PlotMIExperimentalGraph(Results const& results) const;

    void SetDefaultXAxis(Graphs& graphs, Results const& results) const;

    void PlotVariables(Plots const& plots) const;

    virtual boca::Tagger const& Tagger() const = 0;
    virtual boca::Tagger & Tagger() = 0;

    template<typename Branch_>
    Branch_ ConstCast(Branch_ const& branch) const{
      return const_cast<Branch_&>(branch);
    }

//     boca::Tagger& tagger_;

};

}

