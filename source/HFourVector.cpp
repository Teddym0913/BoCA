# include "HFourVector.hh"

hanalysis::HFourVector::HFourVector() :
    CheckFourVectors(1),
    Check(0.00001),
    MassCheck(1)
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
}

hanalysis::HFourVector::~HFourVector()
{
    Print(HInformation, "Destructor");
}

void hanalysis::HFourVector::NewEvent(const HClonesArray *const NewClonesArrays)
{
    ClonesArrays = NewClonesArrays;
    Topology.assign(ClonesArrays->GetParticleSum(), HFamily(EmptyId));
    Print(HInformation, "Topology", Topology.size());
}


fastjet::PseudoJet hanalysis::HFourVector::PseudoJet(const TLorentzVector &Vector) const
{
    // construct a pseudojet from explicit components
    // PseudoJet(const double px, const double py, const double pz, const double E);
    const fastjet::PseudoJet Jet(Vector.Px(), Vector.Py(), Vector.Pz(), Vector.E());
    return Jet;
}

// TLorentzVector hanalysis::HFourVector::GetLorentzVector(const MissingET *const Particle) const
// {
//     Print(HDebug, "Get Lorentz Vector", "MissingET");
//
//     TLorentzVector LorentzVector;
//
//     const float Met = Particle->MET;
//     const float Eta = Particle->Eta;
//     const float Phi = Particle->Phi;
//     LorentzVector.SetPtEtaPhiM(Met, Eta, Phi, 0);
//
//     if (CheckFourVectors) {
//
//         const float LvMet = sqrt(std::pow(LorentzVector.M(),2)+std::pow(LorentzVector.Pt(),2));
//
//         if (std::abs(LvMet - Met) > Check) Print(HError, "Met", Met, LvMet);
//         if (std::abs(LorentzVector.Eta() - Eta) > Check) Print(HError, "Eta", Eta, LorentzVector.Eta());
//         if (std::abs(LorentzVector.Phi() - Phi) > Check) Print(HError, "Phi", Phi, LorentzVector.Phi());
//
//     }
//
//     return LorentzVector;
// }

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootElectron *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootElectron");
    return GetLorentzVectorByMass(Particle, ElectronMass);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenJet *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootGenJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootGenParticle *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootGenParticle");
    return GetLorentzVectorByEnergy(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootJet *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootJet");
    return GetLorentzVectorByMass(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootLHEFParticle *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootLHEFParticle");
    return GetLorentzVectorByM(Particle);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootMuon *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootMuon");
    return GetLorentzVectorByMass(Particle, MuonMass);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootPhoton *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootPhoton");
    return GetLorentzVectorByMass(Particle, 0);
}

TLorentzVector hanalysis::HFourVector::GetLorentzVector(const TRootTau *const Particle) const
{
    Print(HDebug, "Get Lorentz Vector", "TRootTau");
    return GetLorentzVectorByMass(Particle, TauMass);
}

// fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const MissingET *const Particle) const
// {
//     Print(HDebug, "Get Pseudo Jet", "TRootElectron");
//     return GetPseudoJet(GetLorentzVector(Particle));
// }

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootElectron *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootElectron");
    return PseudoJet(GetLorentzVectorByMass(Particle, ElectronMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenJet *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootGenJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootGenParticle *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootGenParticle");
    return PseudoJet(GetLorentzVectorByEnergy(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootJet *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootJet");
    return PseudoJet(GetLorentzVectorByMass(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootLHEFParticle *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootLHEFParticle");
    return PseudoJet(GetLorentzVectorByM(Particle));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootMuon *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootMuon");
    return PseudoJet(GetLorentzVectorByMass(Particle, MuonMass));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootPhoton *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootPhoton");
    return PseudoJet(GetLorentzVectorByMass(Particle, 0));
}

fastjet::PseudoJet hanalysis::HFourVector::GetPseudoJet(const TRootTau *const Particle) const
{
    Print(HDebug, "Get Pseudo Jet", "TRootTau");
    return PseudoJet(GetLorentzVectorByMass(Particle, TauMass));
}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(TObject *Object)
{
    Print(HInformation, "Get Mother Id", ClonesArrays->GetParticleSum());

    HFamily BranchFamily;
    if (Object->IsA() != delphes::GenParticle::Class() || Object == 0) {
        Print(HError, "Object is", Object->ClassName());
        return BranchFamily;
    }

    const int Position = ClonesArrays->GetParticleClonesArray()->IndexOf(Object);
    if (Position == EmptyPosition) return BranchFamily;

    BranchFamily = GetBranchFamily(BranchFamily, Position);
    if (BranchFamily.Mother1Id == EmptyId)
        BranchFamily = HFamily(BranchFamily.ParticlePosition, IsrId, BranchFamily.Mother1Position, IsrId);
//       Print(HError, "Truth Level Tagging Failed");

    for (auto & Node : Topology) if (Node.Marker()) Node = BranchFamily;
    //
    Print(HDebug, "Branch Family", GetParticleName(BranchFamily.ParticleId), GetParticleName(BranchFamily.Mother1Id));

    if (BranchFamily.ParticleId == EmptyId || BranchFamily.Mother1Id == EmptyId) Print(HError, "Branch Family", GetParticleName(BranchFamily.ParticleId), GetParticleName(BranchFamily.Mother1Id));
    return BranchFamily;

}

hanalysis::HFamily hanalysis::HFourVector::GetBranchFamily(HFamily &BranchFamily, int Position)
{
    Print(HInformation, "Get Branch Family ", GetParticleName(BranchFamily.ParticleId), Position);

    if (
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).Mother1Id))) != end(JetTag->HeavyParticles) ||
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).ParticleId))) != end(JetTag->HeavyParticles) ||
        Topology.at(Position).ParticleId == IsrId
    ) {
        return Topology.at(Position);
    }

    while (
        Position != EmptyPosition &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) == end(JetTag->HeavyParticles) &&
        JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) == end(JetTag->HeavyParticles)
    ) {

      Print(HDebug, "Topology", Position, GetParticleName(Topology.at(Position).ParticleId), GetParticleName(Topology.at(Position).Mother1Id));

        if (
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).Mother1Id))) != end(JetTag->HeavyParticles) ||
            JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(Topology.at(Position).ParticleId))) != end(JetTag->HeavyParticles) ||
            Topology.at(Position).ParticleId == IsrId
        ) {
            return Topology.at(Position);
        }

        if (Topology.at(Position).Mother1Id != EmptyId && Topology.at(Position).ParticleId != EmptyId
                && Topology.at(Position).Marker() == 0

           ) {
            return Topology.at(Position);
        }

        Topology.at(Position).SetMarker();
//         if (Position < 3) return HFamily(Position, IsrId, EmptyPosition, IsrId);


        delphes::GenParticle *const ParticleClone = (delphes::GenParticle *) ClonesArrays->GetParticle(Position);
        const int Status = ParticleClone->Status;

        int M1Id = EmptyId;
        int Mother1Status = EmptyStatus;
        TLorentzVector MotherVector;
        if (ParticleClone->M1 > 0) {
            delphes::GenParticle *const Mother1Clone = (delphes::GenParticle *) ClonesArrays->GetParticle(ParticleClone->M1);
            M1Id = Mother1Clone->PID;
            MotherVector = Mother1Clone->P4();
            Mother1Status = Mother1Clone->Status;
        }

        HFamily NodeFamily(ParticleClone->P4(), MotherVector, Position, ParticleClone->PID, ParticleClone->M1, M1Id);
        if (Mother1Status == GeneratorParticle)
        BranchFamily = JetTag->GetBranchFamily(NodeFamily, BranchFamily);

        Print(HDetailed, "Branch Id", GetParticleName(M1Id), GetParticleName(BranchFamily.Mother1Id));

        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
        if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;

        if (ParticleClone->M2 != EmptyPosition && ParticleClone->M2 != ParticleClone->M1) {
            if (ParticleClone->PID == StringId) {
                if (ParticleClone->M1 < ParticleClone->M2) {
                  Print(HDebug, "String", Position, ParticleClone->M1, ParticleClone->M2);
                    HJetInfo JetInfo;
//                     for (int Counter = ParticleClone->M2; Counter >= ParticleClone->M1; --Counter) {
                    for (int Counter = ParticleClone->M1; Counter <= ParticleClone->M2; ++Counter) {
//                         BranchFamily = GetBranchFamily(BranchFamily, Counter);
                        HFamily NewFamily = GetBranchFamily(BranchFamily, Counter);
                        JetInfo.AddFamily(NewFamily, NewFamily.Pt);
                        Print(HDebug, "StringPart", Counter, GetParticleName(BranchFamily.ParticleId));
//                         if (std::abs(BranchFamily.ParticleId) == IsrId) return BranchFamily;
                    }
                        JetInfo.PrintAllFamInfos(HDebug);
                    if (JetInfo.FamilyFractions().size() > 1) {
                      for (int Counter = ParticleClone->M1; Counter <= ParticleClone->M2; ++Counter) {
                        Topology.at(Counter).UnSetMarker();
                      }
                      Print(HDebug,"To many String fractions");
                    };
                    BranchFamily = JetInfo.MaximalFamily();
                } else {
                    Print(HError, "Strange Particle String");
                }
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.Mother1Id))) != end(JetTag->HeavyParticles)) return BranchFamily;
                if (JetTag->HeavyParticles.find(static_cast<HParticleId>(std::abs(BranchFamily.ParticleId))) != end(JetTag->HeavyParticles)) return BranchFamily;
            } else {
                Print(HDebug, "Not a String", Position, ParticleClone->M1, ParticleClone->M2);
            }
        }

        Position = ParticleClone->M1;
        Print(HDetailed, "Mother 1 Position", Position);
    }
    return BranchFamily;
}

void hanalysis::HFourVector::PrintTruthLevel(int const Severity) const
{
    if (Severity <= DebugLevel) {

        PrintCell("Position");
        PrintCell("Top Part");
        PrintCell("Top PP");
        PrintCell("Top Moth");
        PrintCell("Top MP");
        PrintCell("Status");
        PrintCell("Particle");
        PrintCell("Pos M1");
        PrintCell("Mother 1");
        PrintCell("Pos M2");
        PrintCell("Mother 2");
        PrintCell("Pos D1");
        PrintCell("Child 1");
        PrintCell("Pos D2");
        PrintCell("Child 2");
        PrintCell("Energy");
        PrintCell("Px");
        PrintCell("Py");
        PrintCell("Pz");
        std::cout << std::endl;

//         for (const int Position : HRange(ClonesArrays->GetParticleSum())) {
        for (const int Position : HRange(30)) {

            const delphes::GenParticle *Particle = (delphes::GenParticle *)ClonesArrays->GetParticle(Position);

            PrintCell(Position);
            PrintCell(GetParticleName(Topology.at(Position).ParticleId));
            PrintCell(Topology.at(Position).ParticlePosition);
            PrintCell(GetParticleName(Topology.at(Position).Mother1Id));
            PrintCell(Topology.at(Position).Mother1Position);
            PrintCell(Particle->Status);
            PrintCell(GetParticleName(Particle->PID));
            PrintCell(Particle->M1);
            PrintCell(PrintParticle(Particle->M1));
            PrintCell(Particle->M2);
            PrintCell(PrintParticle(Particle->M2));
            PrintCell(Particle->D1);
            PrintCell(PrintParticle(Particle->D1));
            PrintCell(Particle->D2);
            PrintCell(PrintParticle(Particle->D2));
            PrintCell(Particle->E);
            PrintCell(Particle->Px);
            PrintCell(Particle->Py);
            PrintCell(Particle->Pz);
            std::cout << std::endl;

        }

    }

}

std::string hanalysis::HFourVector::PrintParticle(const int Position) const
{

    if (Position != -1) {
        return GetParticleName(((delphes::GenParticle *)ClonesArrays->GetParticle(Position))->PID);
    } else {
        return " ";
    };

}

