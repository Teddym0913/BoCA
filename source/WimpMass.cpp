/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "WimpMass.hh"

#include <map>

#include "WIMPMASS.h"

#include "Quartet.hh"
#include "Math.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

void WimpMass::Momentum(double momentum[4], Jet const& jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

std::vector<boca::Sextet> WimpMass::Sextets(std::vector<Quartet22> const& quartets, Jet const& missing_et)
{
    std::vector<boca::Sextet> sextets;
    for (auto const& quartet : quartets)
        Join(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextets(Quartet22 const& quartet, Jet const& missing_et)
{
    INFO("Triple Pairs");
    event22 structure;
    Momentum(structure.p3, quartet.Doublet1().Singlet2().Jet());
    Momentum(structure.p4, quartet.Doublet2().Singlet2().Jet());
    Momentum(structure.p5, quartet.Doublet1().Singlet1().Jet());
    Momentum(structure.p6, quartet.Doublet2().Singlet1().Jet());
    Momentum(structure.pmiss, missing_et);
//     Debug("Lepton 1 (p3)", PseudoJet(structure.p3));
//     Debug("Lepton 2 (p4)" , PseudoJet(structure.p4));
//     Debug("Jet 1 (p5)" , PseudoJet(structure.p5));
//     Debug("Jet 2 (p6)" , PseudoJet(structure.p6));
//     Debug("PMiss" , PseudoJet(structure.pmiss));
    double momentum_1[4][4], momentum_2[4][4];
    int solution_sum;
    solve22(structure, MassOf(Id::electron_neutrino) / GeV, MassOf(Id::W) / GeV, MassOf(Id::top) / GeV, solution_sum, momentum_1, momentum_2);
    Debug("Number solutions", solution_sum);
    std::vector<boca::Sextet> sextets;
    for (auto const& solution_number : Range(solution_sum)) {
        Debug("Solution ", solution_number);
//         Debug("Neutrino 1 (p1)" , PseudoJet(momentum_1[solution_number]));
//         Debug("Neutrino 2 (p2)" , PseudoJet(momentum_2[solution_number]));
        Doublet doublet_1(quartet.Doublet1().Singlet2().Jet(), Jet(momentum_1[solution_number]));
        if (doublet_1.Mass() <= massless) continue;
        Doublet doublet_2(quartet.Doublet2().Singlet2().Jet(), Jet(momentum_2[solution_number]));
        if (doublet_2.Mass() <= massless) continue;
        Triplet triplet_1(doublet_1, quartet.Doublet1().Singlet1().Jet());
        if (triplet_1.Mass() <= massless) continue;
        triplet_1.SetBdt(quartet.Doublet1().Bdt());
        Triplet triplet_2(doublet_2, quartet.Doublet2().Singlet1().Jet());
        if (triplet_2.Mass() <= massless) continue;
        triplet_2.SetBdt(quartet.Doublet2().Bdt());
        boca::Sextet sextet(triplet_1, triplet_2);
        if (sextet.Mass() <= massless) continue;
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);
        Debug("TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
        //         Debug("Neutrino masses", Jet1.m(), Jet2.m());
//         Debug("W masses", (PseudoJet(momentum_1[solution_number]) + quartet.Doublet1().Singlet2().Jet()).m(), (PseudoJet(momentum_2[solution_number]) + quartet.Doublet2().Singlet2().Jet()).m());
//         Debug("top masses", (PseudoJet(momentum_1[solution_number]) + quartet.Doublet1().Singlet2().Jet() + quartet.Doublet1().Singlet1().Jet()).m(), (PseudoJet(momentum_2[solution_number]) + quartet.Doublet2().Singlet2().Jet() + quartet.Doublet2().Singlet1().Jet()).m());
        //         Debug("Higg mass", (Jet1 + Pair1.PseudoJet2() + Pair1.PseudoJet1() + Jet2 + Pair2.PseudoJet2() + Pair1.PseudoJet1()).m());
    }
    if (solution_sum == 0) {
//         if (counter_ == 10) {
//             Error("No Solution", counter_);
//             return sextets;
//         }
//         ++counter_;
//         sextets = Sextets(quartet, missing_et - 0.1 * (quartet.Jet() - missing_et));
        sextets.emplace_back(Fake(quartet));
    }
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextet(Quartet22 const& quartet, Jet const& missing_et, std::vector<Particle> const& neutrinos, Tag tag)
{
    INFO("Triple Pair");
    std::vector<boca::Sextet> sextets = Sextets(quartet, missing_et);
    Debug("Number Solutions", sextets.size());
    if (sextets.empty())
        return sextets;
//     if (Neutrinos.size() < 2) return sextets;
    for (auto const& neutrino : neutrinos) Debug(neutrino);
//     Debug(neutrinos.at(0) + neutrinos.at(1));
    Debug(missing_et);
    std::map<float, boca::Sextet> map;
    for (auto const& sextet : sextets) {
        Jet neutrino_1 = sextet.Triplet1().Doublet().Singlet2().Jet();
        Jet neutrino_2 = sextet.Triplet2().Doublet().Singlet2().Jet();
        std::vector<float> errors_1, errors_2;
        for (auto const& neutrino : neutrinos) {
            //             Error("Neutrino Mass", Neutrino.m());
            errors_1.emplace_back((neutrino + Particle(neutrino_1)).m());
//             Debug("Neutrino 1 Error", (neutrino + neutrino_1).m());
            errors_2.emplace_back((neutrino + Particle(neutrino_2)).m());
//             Debug("Neutrino 2 Error", (neutrino + neutrino_2).m());
        }
        float error = LargeNumber();
        for (auto const& error_1 : errors_1)
            for (auto const& error_2 : errors_2) {
                if (&error_1 - &errors_1.at(0) == &error_2 - &errors_2.at(0))
                    continue;
                if (error_1 + error_2 < error)
                    error = error_1 + error_2;
            }
//         for (size_t i = 0; i < Neutrino1Errors.size(); ++i) {
//             for (size_t j = i + 1; j < Neutrino2Errors.size(); ++j) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
//         for (size_t j = 0; j < Neutrino2Errors.size(); ++j) {
//             for (size_t i = j + 1; i < Neutrino1Errors.size(); ++i) {
//                 if (Neutrino1Errors[i] + Neutrino2Errors[j] < Error) Error = Neutrino1Errors[i] + Neutrino2Errors[j];
//             }
//         }
        map[error] = sextet;
        Debug("TriplePair Bdt", sextet.Bdt());
    }
    for (auto const& pair : map)
        Debug("Neutrino Error Sum", pair.first);
    if (tag == Tag::signal)
        map.erase(std::next(map.begin()), map.end());
    else
        map.erase(map.begin());
    std::vector<boca::Sextet> final_sextets;
    for (auto const& pair : map) {
        boca::Sextet sextet = pair.second;
        final_sextets.emplace_back(sextet);
    }
//     std::pair<float , Hsextet> Pair = *(Map.begin());
//     Hsextet sextet = Pair.second;
//     Finalsextet.emplace_back(sextet);
//     Finalsextet.emplace_back(*(Map.begin()).second);
    return final_sextets;
}

Sextet WimpMass::Fake(Quartet22 const& quartet) const
{
    Triplet triplet_1(Doublet(quartet.Doublet1().Singlet2().Jet()), quartet.Doublet1().Singlet1().Jet());
    triplet_1.SetBdt(quartet.Doublet1().Bdt());
    Triplet triplet_2(Doublet(quartet.Doublet2().Singlet2().Jet()), quartet.Doublet2().Singlet1().Jet());
    triplet_2.SetBdt(quartet.Doublet2().Bdt());
    return boca::Sextet(triplet_1, triplet_2);
}

// Jet WimpMass::PseudoJet(double const Momentum[4]) const
// {
    // wimpmass (E,px,py,pz)
    // fastjet (px,py,pz,E)
//     return Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
// }

}
