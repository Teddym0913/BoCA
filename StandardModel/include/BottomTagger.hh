/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TaggerTemplate.hh"
#include "BranchesSm.hh"
#include "multiplets/Singlet.hh"


namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for bottom jets.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015-2016 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BottomTagger : public TaggerTemplate<Jet, BottomBranch>
{

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader);

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    std::vector<Jet> SubMultiplet(Jet const& jet, TMVA::Reader const& reader, int sub_jet_number);

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    Jet Multiplet(Jet & jet, TMVA::Reader const& reader);

    std::string Name() const override;

    std::string LatexName() const override;

private:

    std::vector<Particle> Particles(Event const& event) const;

    std::vector<Jet> Jets(Event const& event, PreCuts const& pre_cuts, std::function<Jet(Jet&)> const& function);

    using TaggerTemplate::Multiplets;
    std::vector<Jet> Multiplets(std::vector<Jet> jets, std::function<Jet(Jet&)> const& function, unsigned sub_jet_number = 1) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Jet const& jet, boca::PreCuts const& pre_cuts) const;

    std::vector<Jet> SubJets(std::vector<Jet> const& jets, int sub_jet_number) const;

    Mass bottom_max_mass_;

};

}

template<>
inline void TaggerTemplate<Jet, standardmodel::BottomBranch>::FillBranch(Jet const& multiplet)
{
    Branch().Fill(Singlet(multiplet));
}

}
