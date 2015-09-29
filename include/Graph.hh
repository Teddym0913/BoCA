# pragma once

#include "Rtypes.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraph.h"

#include "Flag.hh"

class TH1F;
class TH1;
class TLegend;
class TMultiGraph;
class TH2;
class THStack;
class TLine;
class TGraph;
class TExec;

namespace boca
{
  typedef std::vector<std::string> Strings;

  class Point;
  struct Plot;
  class Result;
  class Results;

enum class Orientation
{
    center = 0,
    left = 1 << 0,
    right = 1 << 1,
    top = 1 << 2,
    bottom = 1 << 3
};

template<>
struct Flag<Orientation> {
  static const bool enable = true;
};


TH1F Histogram(Result const& result, Point& max, Point& min, int index);

void AddHistogram(THStack& stack, TH1& histogram, TLegend& legend);

TLegend Legend(Point const& min, float width, float height, std::string const& title = "");

TLegend Legend(Orientation orientation, Strings const& entries, std::string const& title = "");


TLine Line(float bin, float y_min, float y_max, int index);

void AddGraph(TGraph& graph, TMultiGraph& multi_graph, TLegend& legend, Strings const& names, int index);


void SetMultiGraph(TMultiGraph& multi_graph, Point const& min, Point const& max);

TGraph Graph(Results const& results, std::vector<float> const& values, std::string const& title);

void SetHistogram(TH2& histogram, Plot const& plot, EColor color, TExec& exec);


void SetProfile(TH2& histogram, Plot const& signal, Plot const& background);

void CommonHist(TH1& histogram, Plot const& plot, EColor color);

}
