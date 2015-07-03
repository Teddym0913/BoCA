#pragma once

#include "DetectorGeometry.hh"
#include "Global.hh"

namespace analysis
{

struct MinDeltaRTo {
    MinDeltaRTo(const fastjet::PseudoJet &jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet1, const Multiplet &multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    bool operator()(const fastjet::PseudoJet &jet1, const fastjet::PseudoJet &jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

struct MaxDeltaRap {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    }
};

struct SortByMassTo {
    SortByMassTo(const float mass) {
        mass_ = mass;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &Multiplet1, const Multiplet &Multiplet2) {
        return std::abs(Multiplet1.Jet().m() - mass_) < std::abs(Multiplet2.Jet().m() - mass_);
    }
    float mass_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> &multiplets, const fastjet::PseudoJet &jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

struct SortPairs {
    template <typename Template>
    bool operator()(const std::pair<Template, float> &pair_1, const std::pair<Template, float> &pair_2) {
        return (pair_1.second < pair_2.second);
    }
};

template <class Multiplet>
std::vector<Multiplet> SortByMaxDeltaRap(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), MaxDeltaRap());
    return multiplets;
}

template <class HMultiplet>
std::vector<HMultiplet> SortedByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass)
{
    std::sort(Multiplets.begin(), Multiplets.end(), SortByMassTo(Mass));
    return Multiplets;
}

// template <class HMultiplet>
//  std::vector<HMultiplet> SortedByMassTo(std::vector<HMultiplet> &Multiplets, const Object::Id id )
// {
//   return SortedByMassTo(Multiplets,Object::Mass(id));
// }


struct SortByMass {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return jet_1.m() > jet_2.m();
    }
};

template <class Multiplet>
std::vector<Multiplet> SortedByMass(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMass());
    return multiplets;
}


struct SortByPt {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return multiplet_1.Jet().pt() > multiplet_2.Jet().pt();
    }
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return jet_1.pt() > jet_2.pt();
    }
    bool operator()(const TLorentzVector &lorentz_vector_1, const TLorentzVector &lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByPt());
    return multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

/**
 * @brief create a fastjet::PseudoJet from a TLorentzVector
 *
 */
fastjet::PseudoJet PseudoJet(const TLorentzVector &vector);

Jets copy_if_abs_particle(const Jets &jets, const Id id);

Jets copy_if_abs_particle(const Jets &jets, const Id id_1, const Id id_2);

Jets copy_if_neutrino(const Jets &jets);

Jets copy_if_particle(const Jets &jets, const int id);

Jets remove_if_particle(const Jets &jets, const int id);

Jets remove_if_not_in_pt_window(Jets &jets, const float lower_cut, const float upper_cut);

Jets RemoveIfWrongAbsFamily(const Jets &jets, const Id id, Id mother_id);

Jets RemoveIfWrongFamily(const Jets &jets, const int id, int mother_id);

Jets RemoveIfWrongAbsStepFamily(const Jets &jets, const int id , const int mother_2_id);

Jets RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id);

Jets RemoveIfWrongParticle(const Jets &NewJets, const int id);

Jets RemoveIfWrongAbsParticle(const Jets &NewJets, const Id id);

Jets RemoveIfWrongAbsMother(const Jets &NewJets, const Id MotherId);

Jets CopyIfAbsMother(const analysis::Jets &jets, const Id mother_id);

Jets RemoveIfAbsMother(const analysis::Jets &NewJets, const analysis::Id MotherId);

Jets RemoveIfLetpons(const Jets &jets);

Jets RemoveIfQuark(const Jets &jets);

Jets CopyIfQuark(const Jets &jets);

Jets RemoveIfNot5Quarks(const Jets &jets);

Jets RemoveIfSoft(const Jets &jets, const float pt_min);


struct Close {
    Close(const fastjet::PseudoJet &particle) {
        particle_ = particle;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet) {
        return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize()
//         & multiplet.Jet().delta_R(particle_) < multiplet.Radius()
        );
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
    }
    fastjet::PseudoJet particle_;
    DetectorGeometry detector_geometry_;
};

struct Close2 {
  Close2(const fastjet::PseudoJet &particle) {
    particle_ = particle;
  }
  template <typename Multiplet>
  bool operator()(const Multiplet &multiplet) {
    return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize());
  }
  bool operator()(const fastjet::PseudoJet &jet) {
    return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
  }
  fastjet::PseudoJet particle_;
  DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(const std::vector<Multiplet> &jets, const Jets &particles)
{
    std::vector<Multiplet> quarks = jets;
    for (const auto & particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
    return quarks;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(const std::vector<Multiplet> &multiplets, const Jets &particles)
{
    if (multiplets.empty()) return multiplets;
    std::vector<Multiplet> final_multiplets;
    for (const auto & particle : particles) for (const auto & multiplet : multiplets) if (Close(particle)(multiplet)) final_multiplets.emplace_back(multiplet);
    return final_multiplets;
}

}
