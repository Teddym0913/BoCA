# ifndef HQuartet_hh
# define HQuartet_hh

# include "HDoublet.hh"

class hanalysis::HQuartet : public HTag
{

public:

    HQuartet() {}

    HQuartet(const hanalysis::HDoublet &NewDoublet1, const hanalysis::HDoublet &NewDoublet2);

    ~HQuartet();

    float GetDeltaR() const {
        return Doublet1.GetDoubletJet().delta_R(Doublet2.GetDoubletJet());
    }

//     float GetInvariantMass() const {
//         return GetPairJet().m();
//     }

//     inline float GetMassDifference(const int ParticleMass) const {
//       return std::abs(GetPairJet().m() - ParticleMass);
//     }

    inline float GetMassDifference(const HParticleId ParticleId) const {
      return std::abs(GetQuartetJet().m() - GetParticleMass(ParticleId));
    }

    fastjet::PseudoJet GetQuartetJet() const {
        return (Doublet1.GetDoubletJet() + Doublet2.GetDoubletJet());
    }

//     float GetPtSum() const {
//         return (Doublet1.GetDoubletJet().pt() + Doublet2.GetDoubletJet().pt());
//     }

    float GetDeltaRap() const {
        return (std::abs(Doublet1.GetDoubletJet().rap() - Doublet2.GetDoubletJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Doublet1.GetDoubletJet().delta_phi_to(Doublet2.GetDoubletJet()));
    }

    HDoublet GetDoublet1()const {
        return Doublet1;
    }

    HDoublet GetDoublet2()const {
        return Doublet2;
    }

protected:

    virtual inline std::string ClassName() const {
        return "HQuartet";
    };

private:

    HDoublet Doublet1;

    HDoublet Doublet2;

};

#endif
