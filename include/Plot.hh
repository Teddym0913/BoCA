#pragma once

#include "Tagger.hh"
#include "TLegend.h"
#include "TFile.h"
#include "TH1F.h"
#include "Branches.hh"
#include <functional>

class TMultiGraph;
class TAttLine;
class TTree;
class TH2;
class TProfile2D;
class TExec;

class ExRootTreeBranch;
class ExRootTreeReader;
namespace exroot
{
typedef ::ExRootTreeBranch TreeBranch;
typedef ::ExRootTreeReader TreeReader;
}

namespace analysis
{

class Result
{

public:

    Result();
    std::vector<int> Integral() const;
    const static int steps = 20000;
    std::vector<float> events;
    std::vector<float> efficiency;
    std::vector<int> analysis_event_number;
    std::vector<float> bdt;
    std::vector<int> bins;
    InfoBranch info_branch;
    long event_sum() const;
    void set_event_sum(long int event_sum);
private:
    long event_sum_;
};

struct Point {
    Point() {
        x = 0;
        y = 0;
        z = 0;
    }
    float x;
    float y;
    float z;
};


class Results
{

public:

    Results();

    void Significances();

    void BestBin();

    float XValue(int value) const {
        return float(value) * 2 / Result::steps - 1;
    }

    float BestXValue() const {
      return XValue(best_bin);
    }

    int XBin(float value) const{
      return std::floor((value + 1) * Result::steps / 2);
    }

    void ExtremeXValues() {
        for (const auto & result : background) {
            float min_0 = *std::min_element(result.bdt.begin(), result.bdt.end());
            if (min_0 < min.x) {
                min.x = min_0;
            }
        }
        for (const auto & result : signal) {
            float max_0 = *std::max_element(result.bdt.begin(), result.bdt.end());
            if (max_0 > max.x) {
                max.x = max_0;
            }
        }
    }

    std::vector<Result> signal;
    std::vector<Result> background;
    std::vector<float> significances;
    std::vector<float> x_values;
    int best_bin = 0;
    Point min;
    Point max;
};
struct Plot3d {
    std::vector<Point> points;
    std::string name_x;
    std::string name_y;
    std::string nice_name_x;
    std::string nice_name_y;
    std::string name;
    std::string tree_name;
};

struct Plots {
    std::vector<Plot3d> plots;
    analysis::InfoBranch info_branch;
    std::string name;
};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class Plot
{

public:

    /**
     * @brief Default constructor
     *
     */
//     Plot();

    /**
     * @brief Constructor
     *
     */
    Plot(analysis::Tagger& tagger);

    void TaggingEfficiency() const;

    void OptimalSignificance() const;

    void RunPlots() const;

private:

    void DoPlot(analysis::Plots& signals, analysis::Plots& backgrounds, analysis::Stage stage) const;

    void Plotting(const analysis::Plot3d& signal, const analysis::Plot3d& background, analysis::Stage stage) const;

    void SetHistogram(TH2& histogram, const analysis::Plot3d& plot, EColor color, TExec& exec) const;

    void SetProfile(TProfile2D& histogram, const analysis::Plot3d& signal, const analysis::Plot3d& background) const;

  std::string IncludeGraphic(std::string& file_name, std::string caption) const;

  void CommmonHist(TH2& histogram, const analysis::Plot3d& plot, EColor color) const;

    std::vector<Plots> Import(analysis::Stage stage, analysis::Tag tag) const;

    Plots PlotResult(TFile& file, const std::string& tree_name, analysis::Stage stage) const;

    Plot3d ReadTree(TTree& tree, const std::string& leaf_1, const std::string& leaf_2, analysis::Stage stage) const;

    void PlotHistogram(const analysis::Plot3d& signal, const analysis::Plot3d& background, const analysis::Point& min, const analysis::Point& max) const;

    void PlotProfile(const analysis::Plot3d& signal, const analysis::Plot3d& background, const analysis::Point& min, const analysis::Point& max) const;

    float Bdt() const;

    void SetMultiGraph(TMultiGraph& multi_graph) const;

    void SetPlotStyle(TAttLine& att_line, int index) const;

    TLegend Legend(float x_min, float y_max, float width, float height, const std::string& name = "") const;

    Results ReadBdtFiles() const;

    std::vector<Result> ReadBdtFile(TFile& export_file, analysis::Tag tag) const;

    TH1F Histogram(const analysis::Result& result, analysis::Point& max, analysis::Point& min, int index) const;

    void PlotAcceptanceGraph(const analysis::Results& results) const;

    std::string PlotHistograms(analysis::Results& results) const;

    void SetHistogram(TH1F& histogram, TLegend& legend, std::string& nice_name, const Point& max) const;

    analysis::Tagger& Tagger() const {
        return *tagger_;
    }

    analysis::Tagger* tagger_;

    analysis::InfoBranch InfoBranch(TFile& file, const std::string& tree_name) const;

    Result BdtDistribution(exroot::TreeReader& tree_reader, const std::string& tree_name, TFile& export_file) const;

    Result BdtResult(TFile& file, const std::string& tree_name, TFile& export_file) const;

    std::string Table(const Results& results) const;

    std::string PlotEfficiencyGraph(const analysis::Results& results) const;

    std::string PlotSignificanceGraph(const analysis::Results& results) const;

    void LatexHeader(std::ofstream& latex_file) const;

    void LatexFooter(std::ofstream& latex_file) const;

    int ColorCode(int number) const;

    Plot3d CoreVector(const Plot3d& points, std::function<bool(Point&, Point&)> function) const;

    std::string ExportFileSuffix() const {
        return ".png";
    }

//     float RoundToDigits(float Value) const;
//
//     float RoundError(float Value) const;
//
//     float RoundToDigits(float Value, int Digits) const;
//
//     float RoundToError(float Value, float Error) const;

    float FloorToDigits(float value, int digits = 2) const;

    float CeilToDigits(float value, int digits = 2) const;

    std::string Reader()const {
        return "";
        return "Reader";
    }

};

}