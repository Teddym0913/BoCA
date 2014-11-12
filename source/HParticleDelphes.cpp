# include "HParticleDelphes.hh"

hdelphes::HParticle ::HParticle()
{

    Print(3, "Constructor");

//     Debug = 5;

}

hdelphes::HParticle ::~HParticle()
{

    Print(3, "Destructor");

}


bool hdelphes::HParticle ::GetParticles()
{

    Print(2, "Get Particles", ClonesArrays->GetParticleSum());

    for (const int ParticleNumber : HRange(ClonesArrays->GetParticleSum())) {

        const GenParticle *const ParticleClone = (GenParticle *) ClonesArrays->GetParticle(ParticleNumber);

        const int ParticleID = ParticleClone->PID;
        Print(4, "Particles ID", ParticleID);

        if (ParticleClone->Status == Stable) {
            Print(4, "Particles Status", "stable");

            if (std::abs(ParticleID) == ElectronId) {

                TLorentzVector ElectronLorentzVector = const_cast<GenParticle *>(ParticleClone)->P4();
                PseudoJet ElectronJet = GetPseudoJet(ElectronLorentzVector);

                if (ParticleID > 0) {

                    ElectronLorentzVectors.push_back(ElectronLorentzVector);
                    ElectronJets.push_back(ElectronJet);
                    Print(3, "Electron");

                } else if (ParticleID < 0) {

                    AntiElectronLorentzVectors.push_back(ElectronLorentzVector);
                    AntiElectronJets.push_back(ElectronJet);
                    Print(3, "Anti Electron");

                }

            }

            if (std::abs(ParticleID) == MuonId) {

                TLorentzVector MuonLorentzVector = const_cast<GenParticle *>(ParticleClone)->P4();
                PseudoJet MuonJet = GetPseudoJet(MuonLorentzVector);

                if (ParticleID > 0) {

                    MuonLorentzVectors.push_back(MuonLorentzVector);
                    MuonJets.push_back(MuonJet);
                    Print(3, "Muon");

                } else if (ParticleID < 0) {

                    AntiMuonLorentzVectors.push_back(MuonLorentzVector);
                    AntiMuonJets.push_back(MuonJet);
                    Print(3, "Anti Muon");

                }

            }

        }



        if (ParticleClone->Status == Unstable) {
            Print(4, "Particles Status", "unstable");

            if (std::abs(ParticleID) == CharmId) {

                CharmJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(3, "Charm");

            }

            if (std::abs(ParticleID) == CpvHiggsId) {

                HiggsJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                Print(3, "CPV Higgs");

            }


            if (std::abs(ParticleID) == BottomId) {

                BottomJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJetVector.push_back(GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4()));
                ParticleJetVector.back().set_user_index(BottomId);

                Print(3, "Bottom");

            }


            if (std::abs(ParticleID) == HeavyHiggsId) {

                PseudoJet HiggsParticle = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());

                HiggsJetVector.push_back(HiggsParticle);
                Print(3, "Heavy CPV Higgs");

                Print(0, "HeavyHiggs", ParticleClone->Status);
                if (ParticleClone->D1 != -1) Print(0, "Daughter1", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D1))->PID);
                if (ParticleClone->D2 != -1) Print(0, "Daughter2", ((GenParticle *) ClonesArrays->GetParticle(ParticleClone->D2))->PID);

            }

        }



        if (ParticleClone->Status == Undefined) {
            Print(4, "Particles Status", "undefined");

            if (std::abs(ParticleID) == TopId) {

                TLorentzVector TopQuark = const_cast<GenParticle *>(ParticleClone)->P4();
                PseudoJet TopJet = GetPseudoJet(const_cast<GenParticle *>(ParticleClone)->P4());
                TopJet.set_user_index(TopId);

                TopJetVector.push_back(TopJet);
                ParticleJetVector.push_back(TopJet);

                if (ParticleID > 0) {

                    TopVector.push_back(TopQuark);
                    Print(3, "Top");

                } else if (ParticleID < 0) {

                    AntiTopVector.push_back(TopQuark);
                    Print(3, "Anti Top");

                }

            }

        }

    }

    return 1;

}

