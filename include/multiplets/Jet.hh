/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "multiplets/PseudoJet.hh"
#include "multiplets/JetInfo.hh"

namespace boca
{

class Jet : public PseudoJet
{

public:

    Jet();

    Jet(double x, double y, double z, double e);

    Jet(const boca::Momentum& x, const boca::Momentum& y, const boca::Momentum& z, const boca::Energy& e);

    Jet(fastjet::PseudoJet const& jet);

    Jet(fastjet::PseudoJet const& jet, JetInfo const& info);

    Jet(LorentzVector<Momentum> const& lorentz_vector);

    Jet(TLorentzVector const& lorentz_vector);

    Jet(TLorentzVector const& lorentz_vector, ::delphes::Jet const& jet);

    Jet(TLorentzVector const& lorentz_vector, Constituent const& constituent);

    Jet(TLorentzVector const& lorentz_vector, std::vector<Constituent> const& constituents);

    Jet(TLorentzVector const& lorentz_vector, int charge);

    Jet(exroot::Electron const& electron);

    Jet(exroot::GenJet const& gen_jet);

    Jet(exroot::Jet const& jet);

    Jet(exroot::Muon const& muon);

    Jet(exroot::Photon const& photon);

    Jet(exroot::Tau const& tau);

    Jet(double const Momentum[4]);

    JetInfo const& Info() const;

    JetInfo& Info();

    void SetDelphesTags(::delphes::Jet const& delphes_jet);

    std::vector<Jet> Constituents() const;

    LorentzVector<Momentum> Vector() const;

    double Bdt() const;

protected:

    void SetInfo(JetInfo const& user_info = JetInfo());

    void ResetInfo(JetInfo const& user_info);

private:

};

using Lepton = Jet;

using MissingEt = Jet;

std::vector<Jet> JetVector(std::vector<fastjet::PseudoJet> const& pseudo_jets);

std::vector<fastjet::PseudoJet> PseudoJetVector(std::vector<Jet> const& jets);

Jet Join(std::vector<Jet> const& jets);

Jet Join(Jet const& jet_1, Jet const& jet_2);

Jet Join(Jet const& jet_1, Jet const& jet_2, Jet const& jet_3);

}
