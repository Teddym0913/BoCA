#pragma once

#include "math/LorentzVector.hh"
#include "math/Matrix2.hh"

// *********************************************************************************
// WIMPMASS
// version 1.00
//
// Authors: Hsin-Chia Cheng, John Gunion, Zhenyu Han, Bob McElrath, Dalit Engelhardt
//
// *********************************************************************************
// This package contains two C++ subroutines useful for event
// reconstruction in events with missing particles. The references
// are arXiv: 0707.0030 and arXiv: 0802.4290.
//
// The two functions are given in "topology22.cpp" and "topology33.cpp"
// in the "src/" directory. See the header of the source file for usage.
// "ROOT" (http://root.cern.ch/drupal/) is required for compiling
// topology33.cpp. The directory "examples/" contains a couple of examples
// calling these subroutines. You need to modify the Makefile in the "src"
// directory and "examples" directory to point to the correct ROOT location.

namespace boca
{
class Doublet;
class Quartet22;


namespace wimpmass
{

class Invisible22
{
public:

    Invisible22();

    Invisible22(Quartet22 const& quartet, LorentzVector<Momentum> const& missing);

    Invisible22(LorentzVector<Momentum> const& missing);

    void SetMissingMomentum(LorentzVector<Momentum> const& missing);

    void Set(Quartet22 const& quartet);

    void SetFirstChain(Doublet const& doublet);

    void SetSecondChain(Doublet const& doublet);

    void SetFirstChain(LorentzVector<Momentum> const& first, LorentzVector<Momentum> const& second);

    void SetSecondChain(LorentzVector<Momentum> const& first, LorentzVector<Momentum> const& second);

//

    std::vector<std::pair<LorentzVector<Momentum>, LorentzVector<Momentum>>> Solve(const boca::Mass& heavy, const boca::Mass& light, boca::Mass const& invisible);

    struct event22 {
        double p3[4], p4[4], p5[4], p6[4];
        double pmiss[4];
    };

    void solve22(event22& evt, double mn, double mx, double my, int& nsols, double p1[][4], double p2[][4]);

private:

    void SetMomentum(double momentum[4], LorentzVector<Momentum> const& jet);

    void SetVector(double momentum[4], LorentzVector<Momentum>& jet);
    LorentzVector<Momentum> p3_;
    LorentzVector<Momentum> p4_;
    LorentzVector<Momentum> p5_;
    LorentzVector<Momentum> p6_;
    LorentzVector<Momentum> missing_;

    LorentzVector<double> CoefficientVector1() const;
    LorentzVector<double> CoefficientVector2() const;
    LorentzVector<Momentum> CoefficientVector(const boca::Mass& heavy, const boca::Mass& light, const boca::Mass& invisible) const;
    Matrix2<double> MatrixA(LorentzVector<double> const& ce1, LorentzVector<double> const& ce2);
    Matrix2<double> MatrixB(LorentzVector<double> const& ce1, LorentzVector<double> const& ce2);
    Vector2<Momentum> VectorA(LorentzVector<Momentum> const& c, LorentzVector<double> const& ce1, LorentzVector<double> const& ce2);
    Vector2<Momentum> VectorB(LorentzVector<Momentum> const& c, LorentzVector<double> const& ce1, LorentzVector<double> const& ce2);
    MomentumSquare ScalarA(const boca::LorentzVector< boca::Momentum >& c, const boca::Mass& invisible);
    MomentumSquare ScalarB(LorentzVector<Momentum> const& c, Mass const& invisible);
    std::array<double,5> Coefficients(const boca::Matrix2< double >& ma, const boca::Matrix2< double >& mb, const boca::Vector2< boca::Momentum >& va, const boca::Vector2< boca::Momentum >& vb, const MomentumSquare& a, MomentumSquare const& b);
    Energy Energy1(const boca::Matrix2< double >& ma, const boca::Matrix2< double >& mb, const boca::Vector2< boca::Momentum >& va, const boca::Vector2< boca::Momentum >& vb, const MomentumSquare& a, const MomentumSquare& b, const boca::Energy& energy_2);
};

}

}

// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <cmath>
//
// #include "external/Invisible2.hh"
//
// int main()
// {
//
//   //read a data file in the lhe format
//   //squark pair production.
//   //each squark decays squark->neutralni2-> slepton->neutralino 1, giving 4 lepton + 2 jet per event
//   //the jet information is not used in the 22 topology.
//
//   std::ifstream datafile("sqsq_pythia_events.lhe");
//
//   int MAXEVENT = 3;
//   boca::wimpmass::Invisible22::event22 evt[MAXEVENT];
//   int ievent;
//   for (ievent = 0; ievent < MAXEVENT; ievent ++) {
//     //find the line containing <event>
//     int i = 0;
//     char line [1000];
//     while (i == 0) {
//       datafile.getline(line, 999);
//       if (datafile.eof()) break;
//       if (std::strstr(line, "<event>")) i = 1;
//     }
//     if (datafile.eof()) break;
//     int npar, itemp;
//     double dtemp1, dtemp2, dtemp3, dtemp4;
//
//     //read the first line of an event
//     datafile >> npar >> itemp >> dtemp1 >> dtemp2 >> dtemp3 >> dtemp4;
//
//     //read npar lines
//     int ic1, ic2, ic3, ic4, ic5, ic6;
//     double ic7;
//     double p[6];
//     //         int njet = 0;
//     int nlep = 0;
//     for (int j = 0; j < npar; j ++) {
//       datafile >> ic1 >> ic6 >> ic2 >> ic3 >> ic4 >> ic5 >> p[1] >> p[2] >> p[3] >> p[0] >> p[4] >> p[5] >> ic7;
//       //ic1 is particle ID
//       //ic6=1, stable
//       p[0] = sqrt(p[1] * p[1] + p[2] * p[2] + p[3] * p[3] + p[4] * p[4]);
//       //if ( ic6 != 1 ) continue;
//       //read the momenta of the four leptons
//       if (std::abs(ic1) == 11 || std::abs(ic1) == 13) {
//         if (nlep == 0) for (int i = 0; i < 4; i ++)evt[ievent].p5[i] = p[i];
//         else if (nlep == 1) for (int i = 0; i < 4; i ++) evt[ievent].p3[i] = p[i];
//         else if (nlep == 2) for (int i = 0; i < 4; i ++) evt[ievent].p6[i] = p[i];
//         else if (nlep == 3) for (int i = 0; i < 4; i ++) evt[ievent].p4[i] = p[i];
//         nlep ++;
//       }
//       //read missing momentum
//       if (std::abs(ic1) == 12) for (int i = 0; i < 4; i ++) evt[ievent].pmiss[i] = p[i];
//     }
//   }
//   int nevent = ievent;
//   std::cout << "Read from data file: sqsq_pythia_events.lhe" << std::endl;
//   std::cout << "Number of events  = " << nevent << std::endl << std::endl;
//   datafile.close();
//   //test the first two events by solve22()
//   std::cout << "Now test the 22 algorithm with known masses: 100.4, 143.7, 181.2." << std::endl;
//   std::cout << "Only test the first two events." << std::endl;
//   double mn = 100.42479, mx = 143.70998, my = 181.23681;
//   int nsols;
//   double p1[4][4], p2[4][4];
//
//   //loop over events
//   for (ievent = 0; ievent < MAXEVENT; ievent ++) {
//     std::cout << std::endl << "event " << ievent << std::endl << std::endl;
//     std::cout << "Visible momenta and the missing transverse momentum:" << std::endl;
//     std::cout << "p3 = " << evt[ievent].p3[0] << "   " << evt[ievent].p3[1] << "   " << evt[ievent].p3[2] << "   " << evt[ievent].p3[3] << std::endl;
//     std::cout << "p4 = " << evt[ievent].p4[0] << "   " << evt[ievent].p4[1] << "   " << evt[ievent].p4[2] << "   " << evt[ievent].p4[3] << std::endl;
//     std::cout << "p5 = " << evt[ievent].p5[0] << "   " << evt[ievent].p5[1] << "   " << evt[ievent].p5[2] << "   " << evt[ievent].p5[3] << std::endl;
//     std::cout << "p6 = " << evt[ievent].p6[0] << "   " << evt[ievent].p6[1] << "   " << evt[ievent].p6[2] << "   " << evt[ievent].p6[3] << std::endl;
//     std::cout << "pmiss x,y = " << "   " << evt[ievent].pmiss[1] << "   " << evt[ievent].pmiss[2] << std::endl;
//
//     //         wimpmass::solve22(evt[ievent], mn, mx, my, nsols, p1, p2);
//     boca::wimpmass::Invisible22 inv;
//     inv.solve22(evt[ievent], mn, mx, my, nsols, p1, p2);
//     std::cout << std::endl;
//     std::cout << "number of solutions = " << nsols << std::endl;
//
//     for (int isol = 0; isol < nsols; isol ++) {
//       std::cout << std::endl << "solution " << isol << std::endl;
//       std::cout << "p1 = " << p1[isol][0] << "  " << p1[isol][1] << "  " << p1[isol][2] << "  " << p1[isol][3] << std::endl;
//       std::cout << "p2 = " << p2[isol][0] << "  " << p2[isol][1] << "  " << p2[isol][2] << "  " << p2[isol][3] << std::endl;
//     }
//     std::cout << std::endl;
//   }
// }

