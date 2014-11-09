# include "HSuperStructure.hh"

hanalysis::HSuperStructure::HSuperStructure()
{
    Print(2, "Constructor");

    Position1 = EmptyPosition;
    Position2 = EmptyPosition;

}

hanalysis::HSuperStructure::~HSuperStructure()
{

    Print(2, "Destructor");

}

void hanalysis::HSuperStructure::operator=(const HSuperStructure &other)
{

    Jet1 = other.Jet1;
    Jet2 = other.Jet2;
    Position1 = other.Position1;
    Position2 = other.Position2;

}

float hanalysis::HSuperStructure::GetReferenceAngle(const PseudoJet &Jet, const PseudoJet &ReferenceJet) const
{

    const float Rap = Jet.rap() - ReferenceJet.rap();
    const float Phi = GetDeltaPhi(Jet.phi_std(), ReferenceJet.phi_std());

    return (std::atan2(-Phi, -Rap));

}


float hanalysis::HSuperStructure::GetPullAngle1() const
{
    const float Pull = GetPull(Jet1);
    const float ReferenceAngle = GetReferenceAngle(Jet1, Jet2);
    Print(3, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));

//     if (std::abs(GetDeltaPhi(Pull, ReferenceAngle) > 3)) {
//         Print(0, "extrema", Pull, ReferenceAngle);
//         Print(0, "extrema", Jet1.rap(), Jet1.phi_std());
//         Print(0, "extrema", Jet2.rap(), Jet2.phi_std());
//         Print(0, " ");
//     }

    return GetDeltaPhi(Pull, ReferenceAngle);

}

float hanalysis::HSuperStructure::GetPullAngle2() const
{
    const float Pull = GetPull(Jet2);
    const float ReferenceAngle = GetReferenceAngle(Jet2, Jet1);
    Print(3, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));

    return GetDeltaPhi(Pull, ReferenceAngle);

}


float hanalysis::HSuperStructure::GetPull(const PseudoJet &CandidateJet) const
{
    float Rap = 0;
    float Phi = 0;

    for (const auto & Constituent : CandidateJet.constituents()) {

        const float DeltaY = Constituent.rap() - CandidateJet.rap();
        const float DeltaPhi = GetDeltaPhi(Constituent.phi_std(), CandidateJet.phi_std());
        const float DeltaR = std::sqrt(std::pow(DeltaY, 2) + std::pow(DeltaPhi, 2));
        const float PullFactor = Constituent.pt() / CandidateJet.pt() * DeltaR;
//         const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);

        Rap += (PullFactor * DeltaY);
        Phi += (PullFactor * DeltaPhi);

    }

    return std::atan2(Phi, Rap);

}







bool hanalysis::HSuperStructure::GetConstituents(ExRootTreeBranch *const ConstituentBranch)
{

  if (Jet1.constituents().size() < 1 || Jet2.constituents().size() < 1) {

    Print(1, "Not enough Constituents", Jet1.constituents().size(),Jet2.constituents().size());
    return 0;

  }

  const float Shift = 3;

  const float Theta = atan2(Jet2.phi_std(), Jet2.eta());
      const float OriginEta = ( Jet1.eta() + Jet2.eta() ) / 2;
      const float OriginPhi = ( Jet1.phi_std() + Jet2.phi_std() ) / 2;
      const float Distance = Jet1.delta_R(Jet2);
      const float SubJetRatio = 2. * Shift / Distance;




  for (const auto & ConstituentJet : Jet1.constituents()) {

    if (
//       ConstituentJet.user_index() != IsrId &&
      ConstituentJet.user_index() != CpvHiggsId &&
//       std::abs(ConstituentJet.user_index()) != TopId &&
      ConstituentJet.user_index() != HiggsId
    )
      Print(0, "Wrong UserId", ConstituentJet.user_index());

      // Get Constituent coordinates in Higgs Jet coordinates

      float ConstEta = ConstituentJet.eta() - OriginEta;
      float ConstPhi = GetDeltaPhi(ConstituentJet.phi_std(),OriginPhi);

      // move subjet1 together with constituent to origin

      ConstEta -= Jet1.eta();
      ConstPhi = GetDeltaPhi(ConstPhi, Jet1.phi_std());

      // scale distance to reference value

      ConstEta *= SubJetRatio;
      ConstPhi *= SubJetRatio;

      // rotate Constituent according to subjet2

      float ObservableEta = ConstEta * cos(Theta) + ConstPhi * sin(Theta);
      const float ObservablePhi = ConstEta * sin(Theta) - ConstPhi * cos(Theta);

      // move subjet2 to (1,0)
      ObservableEta -= Shift;


      Print(3,"eta",ObservableEta);

      HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
      Constituent->Eta = ObservableEta;
      Constituent->Phi = ObservablePhi;
      Constituent->Pt = ConstituentJet.pt();

  }


/*

  for (const auto & ConstituentJet : Jet2.constituents()) {

    if (ConstituentJet.user_index() != IsrId &&
      ConstituentJet.user_index() != CpvHiggsId &&
      std::abs(ConstituentJet.user_index()) != TopId &&
      ConstituentJet.user_index() != HiggsId
    )
      Print(0, "Wrong UserId", ConstituentJet.user_index());



      //       const float DistanceJet1 = ConstituentJet.delta_R(Jet1);


      // Get Constituent coordinates in Higgs Jet coordinates

      float ConstEta = ConstituentJet.eta() - OriginEta;
      float ConstPhi = GetDeltaPhi(ConstituentJet.phi_std(),OriginPhi);

      // move subjet1 together with constituent to origin

      ConstEta -= Jet1.eta();
      ConstPhi = GetDeltaPhi(ConstPhi, Jet1.phi_std());

      // scale distance to reference value

      ConstEta = ConstEta * SubJetRatio;
      ConstPhi = ConstPhi * SubJetRatio;

      // rotate Constituent according to subjet2

      float ObservableEta = ConstEta * cos(Theta) + ConstPhi * sin(Theta);
      const float ObservablePhi = ConstEta * sin(Theta) - ConstPhi * cos(Theta);

      // move subjet2 to (1,0)
      ObservableEta -= Shift;


      Print(3,"eta",ObservableEta);

      HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
      Constituent->Eta = ObservableEta;
      Constituent->Phi = ObservablePhi;
      Constituent->Pt = ConstituentJet.pt();

  }*/


  return 1;

}
























//
// hanalysis::HPull::HPull()
// {
//     Print(2, "Constructor");
//
//     InitialValue = -1000;
//     PullPhi = 0;
//     PullRap = 0;
// //     DiPolarity = 0;
//
// }
//
// hanalysis::HPull::~HPull()
// {
//
//     Print(2, "Destructor");
//
// }
//
//
// void hanalysis::HPull::BTagCalculation(const Jet& JetClone)
// {
//
//     Print(2, "BTagCalculation");
//
//     PseudoJet CandidateJet = GetPseudoJet(const_cast<Jet*>(&JetClone)->P4());
//
// //     if (Jet.pt() > 0) {
//
//         int ValidConstituentsSum = 0;
//         int ConstituentsSum = JetClone.Constituents.GetEntriesFast();
//         Print(2, "Number of b Jet Constituents", ConstituentsSum);
//
//
//         for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ++ConstituentsNumber) {
//
//             const TObject * const ConstituentObject = JetClone.Constituents.At(ConstituentsNumber);
//             if (ConstituentObject == 0) continue;
//             Print(3, "Entering b Jet Constituent", ConstituentsNumber);
//             ValidConstituentsSum++;
//
//             const PseudoJet ConstituentJet = GetConstituentJet(ConstituentObject);
//
//             const float PullFactor = ConstituentJet.pt() * ConstituentJet.delta_R(CandidateJet) / CandidateJet.pt();
//             PullRap += PullFactor * ConstituentJet.rap();
//             PullPhi += PullFactor * ConstituentJet.phi_std();
//
//         }
//
//         if (ValidConstituentsSum != ConstituentsSum) Print(3, "Number of valid Jet Constituents", ValidConstituentsSum);
//         Print(2, "PullPhi", PullPhi);
//         Print(2, "PullY", PullRap);
//
// //     }
//
// }
//
// float hanalysis::HPull::PullAngle(float Rap, float Phi)
// {
//
//     Print(2, "Pull Angle");
//
//     float Theta = InitialValue;
//     if (Rap != 0) {
//         Theta = atan(Phi / Rap);
//     }
//
//     if (Rap < 0) {
//         if (Phi > 0) {
//             Theta += Pi();
//         }
//         if (Phi < 0) {
//             Theta -= Pi();
//         }
//     }
//
//     if (fabs(Theta) > Pi()  && Theta !=  InitialValue) {
//         Print(0, "Error in Theta Calculation");
//     }
//
//     return (Theta);
//
// }
//
//
// float hanalysis::HPull::ConfineAngle(float Angle)
// {
//
//     Print(2, "Confine Angle");
//
//     if (Angle > Pi()) {
//         Angle -= 2 * Pi();
//     }
//     if (Angle < -Pi()) {
//         Angle += 2 * Pi();
//     }
//     if (fabs(Angle) > Pi()) {
//         Print(0, "Error in Angle Confinment", Angle);
//     }
//
//     return (Angle);
//
// }
//
//
// float hanalysis::HPull::SubPull(const PseudoJet& SubJet, const PseudoJet& RefJet, const PseudoJet& CandidateJet)
// {
//
//     Print(2, "Sub Pull");
//
//     Print(4, "Mass", CandidateJet.m());
//
//     float SubJetPt = SubJet.pt();
//
//     float SubJetPhi = SubJet.phi_std();
//     float SubJetRap = SubJet.rap();
//
//     float RefJetPhi = RefJet.phi_std();
//     float RefJetRap = RefJet.rap();
//
//     float DeltaRSubJetRefJet = RefJet.delta_R(SubJet);
//     float DeltaPhi = ConfineAngle(RefJetPhi - SubJetPhi);
//     Print(2, "DeltaPhi", DeltaPhi);
//
//     float DeltaRap = RefJetRap - SubJetRap;
//     Print(2, "DeltaRap", DeltaRap);
//
//     float RefTheta = PullAngle(DeltaRap, DeltaPhi);
//     Print(2, "RefTheta", RefTheta);
//
//     float SubPullRap = 0;
//     float SubPullPhi = 0;
//     int ValidConstituents = 0;
//
//     vector<PseudoJet> ConstVector = CandidateJet.constituents();
// //     vector<PseudoJet> ConstVector = SubJet.constituents();
//     int ConstSum = ConstVector.size();
//     Print(2, "Number of Constituents", ConstSum);
//
//     for (int ConstNumber = 0; ConstNumber < ConstSum; ConstNumber++) {
//
//         PseudoJet ConstJet = ConstVector[ConstNumber];
//
//         float DeltaRConstSubJet = ConstJet.delta_R(SubJet);
//         float DeltaRConstRefJet = ConstJet.delta_R(RefJet);
// //         if (DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/ && DeltaRConstSubJet < DeltaRSubJetRefJet / sqrt(2) /*/ 2*/) {
// //         if (DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/ /2) {
//
//         if (
//             DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/  &&
//             pow(DeltaRConstSubJet, 2) + pow(DeltaRConstRefJet, 2) < 2 * pow(DeltaRSubJetRefJet, 2)
//             &&
//             DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/
//         ) {
//
//             float ConstPhi = ConstJet.phi_std();
//             float DeltaPhiConstSubJet = ConfineAngle(ConstPhi - SubJetPhi);
//
//             float ConstRap = ConstJet.rap();
//             float DeltaRapConstSubJet = ConstRap - SubJetRap;
//
//             float DeltaRConstSubJetCalc = sqrt(pow(DeltaPhiConstSubJet, 2) + pow(DeltaRapConstSubJet, 2));
//             float ConstPt = ConstJet.pt();
//             float PullFactor = ConstPt / SubJetPt * DeltaRConstSubJetCalc;
//
//             SubPullRap += PullFactor * DeltaRapConstSubJet;
//             SubPullPhi += PullFactor * DeltaPhiConstSubJet;
//
//             ++ValidConstituents;
//
//         }
//
//     }
//     Print(2, "Number of Valid Constituents", ValidConstituents);
//     Print(2, "SubPullRap", SubPullRap);
//     Print(2, "SubPullPhi", SubPullPhi);
//
//     float PullTheta = PullAngle(SubPullRap, SubPullPhi);
//     Print(2, "PullTheta", PullTheta);
//
//     float Result = InitialValue;
//     if (ValidConstituents > ConstSum / 5) {
//
//         if (PullTheta != InitialValue && RefTheta != InitialValue) {
//             Result = ConfineAngle(PullTheta - RefTheta);
//         }
//
//         if (fabs(Result) > Pi() && Result != InitialValue) {
//             Print(0, "Error in Result Calculation");
//         }
//
//     }
//
//     Print(2, "Result", Result);
//
//     return (Result);
//
// }
//
//
//
// float hanalysis::HPull::CalculateDiPolarity(const PseudoJet& FatJet, const PseudoJet& FatJetPiece1, const PseudoJet& FatJetPiece2)
// {
//
//     Print(2, "Calculate DiPolarity");
//
//     // Filtering
// //     PseudoJet Parent1 = MassDropJet.pieces()[0];
// //     PseudoJet Parent2 = MassDropJet.pieces()[1];
// //     float ParentCylinderDistance = Parent1.delta_R(Parent2);
// //     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
// //     float MinimalCylinderDistance = .3;
// //     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
// //     JetDefinition MassDropJetDefinition(cambridge_algorithm, FilterCylinderDistance);
// //
// //     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
// //     int NumberHardestPieces = 2;
// //     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
// //     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
// //     PseudoJet FatJet = FatJetFilter(MassDropJet);
// //
// //
// //
//
//
//
//     float FatJetPt = FatJet.pt();
//     Print(2, "FatJet Pt", FatJetPt);
//
//     vector<PseudoJet> FatJetPieceVector = FatJet.pieces();
//     int PieceSum = FatJetPieceVector.size();
//     if (PieceSum != 2) Print(0, "Number of Fat Jet Pieces", PieceSum);
// //     PseudoJet FatJetPiece1 = FatJetPieceVector[0];
// //     PseudoJet FatJetPiece2 = FatJetPieceVector[1];
//
//     float Piece1Eta = FatJetPiece1.eta();
//     float Piece1Phi = FatJetPiece1.phi();
//     float Piece2Eta = FatJetPiece2.eta();
//     float Piece2Phi = FatJetPiece2.phi();
//
//     float DeltaEta = Piece2Eta - Piece1Eta;
//     float DeltaPhi = Piece2Phi - Piece1Phi;
//
//     float PieceDistanceSqr = DeltaEta * DeltaEta + DeltaPhi * DeltaPhi;
//     Print(2, "Piece Distance sqr", PieceDistanceSqr);
//     float DiPolaritySum = 0;
//     float ConstituentPtSum = 0;
//     float ConstituentRSqrSum = 0;
//     float ConstituentNumSqrSum = 0;
//     int ValidConstituents = 0;
//
//     float DiPolarity;
//
//     if (PieceDistanceSqr < 100000000) {
//
//
//         vector<PseudoJet> ConstituentsVector = FatJet.constituents();
//         int ConstituentsSum = ConstituentsVector.size();
//         Print(2, "Number of Fat Jet Constituents", ConstituentsSum);
//
//         for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ConstituentsNumber++) {
//
//             Print(3, "Entering Fat Jet Constituent", ConstituentsNumber);
//             PseudoJet ConstituentJet = ConstituentsVector[ConstituentsNumber];
//
//             float ConstituentPhi = ConstituentJet.phi();
//             Print(3, "Constituent Phi", ConstituentPhi);
//
//             float ConstituentEta = ConstituentJet.eta();
//             Print(3, "Constituent Eta", ConstituentEta);
//
//             float ConstituentDeltaEta = Piece1Eta - ConstituentEta;
//             float ConstituentDeltaPhi = Piece1Phi - ConstituentPhi;
//
//             float DeltaEta1Sqr = pow(ConstituentDeltaEta, 2);
//             float DeltaPhi1Sqr = pow(ConstituentDeltaPhi, 2);
//             float DeltaEta2Sqr = pow(Piece2Eta - ConstituentEta, 2);
//             float DeltaPhi2Sqr = pow(Piece2Phi - ConstituentPhi, 2);
//             float ConstituentDistance1Sqr = DeltaEta1Sqr + DeltaPhi1Sqr;
//             float ConstituentDistance2Sqr = DeltaEta2Sqr + DeltaPhi2Sqr;
//
//             if (ConstituentDistance1Sqr > (PieceDistanceSqr / 2) && ConstituentDistance2Sqr > (PieceDistanceSqr / 2)) {
//
//                 Print(3, "out of cones");
//                 continue;
//
//             }
//             ValidConstituents++;
//
//             float ConstituentPt = ConstituentJet.pt();
//             Print(3, "Constituent Pt", ConstituentPt);
//
//             float ConstituentNumSqr = pow(DeltaEta * ConstituentDeltaPhi - DeltaPhi * ConstituentDeltaEta, 2);
//
//             Print(3, "ConstituentNumSqr", ConstituentNumSqr);
//             float ConstituentRSqr = ConstituentNumSqr / PieceDistanceSqr;
//
//             DiPolaritySum += ConstituentRSqr * ConstituentPt / FatJetPt ;
//             Print(3, "DiPolarity Sum", DiPolaritySum);
//
//             ConstituentPtSum += ConstituentPt;
//
//             ConstituentRSqrSum += ConstituentRSqr;
//
//             ConstituentNumSqrSum += ConstituentNumSqr;
//
//         }
//
//         Print(3, "Fraction of valid Constitueants", 1 - (ConstituentsSum - ValidConstituents) / ConstituentsSum);
//
//         DiPolarity = DiPolaritySum / PieceDistanceSqr;
//
//     }
//
//     if (DiPolarity < 0.01 && DiPolarity > 0) {
//
//         Print(2, "Pt Ratio", ConstituentPtSum / FatJetPt);
//         Print(2, "RSqr Ratio", ConstituentRSqrSum / PieceDistanceSqr);
//         Print(2, "PieceDistanceSqr", PieceDistanceSqr);
//         Print(2, "ConstituentNumSqrSum", ConstituentNumSqrSum);
//         Print(2, "DiPolaritySum", DiPolaritySum);
//         Print(2, "DiPolarity", DiPolarity);
//
//     }
//
//     return DiPolarity;
//
// }
//
//
//
// float hanalysis::HPull::JingDipolarity(const PseudoJet &CandidateJet)
// {
//
//     Print(2, "Jing Dipolarity");
//
//     vector<PseudoJet> SubJetVector = CandidateJet.pieces();
//     if (SubJetVector.size() != 2) Print(0, "not two subjets");
//
//     // Filtering
//     float ParentCylinderDistance = SubJetVector[0].delta_R(SubJetVector[1]);
//     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
//     float MinimalCylinderDistance = 0.35;
//     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
//     JetDefinition MassDropJetDefinition(antikt_algorithm, FilterCylinderDistance);
//
//     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     int NumberHardestPieces = 3;
//     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
//     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
//     PseudoJet FilterJet = FatJetFilter(CandidateJet);
//
//     SubJetVector = FilterJet.pieces();
//     if (SubJetVector.size() != 2) Print(0, "not two subjets");
//
//
//     float Eta1, Eta2, Phi1, Phi2;
//
//     if (SubJetVector[0].eta() < SubJetVector[1].eta()) {
//
//         Eta1 = SubJetVector[0].eta();
//         Phi1 = SubJetVector[0].phi_std();
//         Eta2 = SubJetVector[1].eta();
//         Phi2 = SubJetVector[1].phi_std();
//
//     } else {
//
//         Eta1 = SubJetVector[1].eta();
//         Phi1 = SubJetVector[1].phi_std();
//         Eta2 = SubJetVector[0].eta();
//         Phi2 = SubJetVector[0].phi_std();
//
//     }
//
//     float DeltaR12 = SubJetVector[0].delta_R(SubJetVector[1]);
//
//     float DiPolarity=0;
//
//     for (const auto & Constituent : FilterJet.constituents()){
//
//         const float ConstituentEta = Constituent.eta();
//         float ConstituentPhi = Constituent.phi_std();
//
//         const float DeltaPhi = Phi2 - Phi1;
//         const float DeltaEta = -(Eta2 - Eta1);
//         const float EtaPhi = Eta2 * Phi1 - Eta1 * Phi2;
//
//         const float ConstituentDeltaR1 = Constituent.delta_R(SubJetVector[0]);
//         const float ConstituentDeltaR2 = Constituent.delta_R(SubJetVector[1]);
//         const float ConstituentDeltaR3 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));
//         float Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
//         float Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
//
//         float DeltaR1;
//         if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
//                 || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
//             DeltaR1 = ConstituentDeltaR3;
//         } else {
//             DeltaR1 = min(ConstituentDeltaR1, ConstituentDeltaR2);
//         }
//
//         if (ConstituentPhi < 0) {
//             ConstituentPhi = ConstituentPhi + 2 * Pi();
//         } else {
//             ConstituentPhi = ConstituentPhi - 2 * Pi();
//         }
//
//         Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
//         Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
//
//         const float ConstituntDeltaR4 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));
//
//         float DeltaR2;
//         if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
//                 || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
//             DeltaR2 = ConstituntDeltaR4;
//         } else {
//             DeltaR2 = min(ConstituentDeltaR1, ConstituentDeltaR2);
//         }
//
//         const float DeltaR = min(DeltaR1, DeltaR2);
//
//         const float ConeSize = sqrt(2);
//
//         if (ConstituentDeltaR1 < DeltaR12 / ConeSize || ConstituentDeltaR2 < DeltaR12 / ConeSize) {
//
//         const float deltar = DeltaR / DeltaR12;
// //         float ConstDelR1 = ConstituentDeltaR1 / DeltaR12;
// //         float ConstDelR2 = ConstituentDeltaR2 / DeltaR12;
// //         float PtRatio =  Constituent.perp() / HiggsJet.perp();
//         const float PtRatio =  Constituent.perp() / FilterJet.perp();
//
//         DiPolarity += PtRatio * pow(deltar,2);
//
//         }
//
//     }
//
//     return DiPolarity;
// //     return (DiPolarity / ConstituentSum * 10000);
//
// }
