# ifndef HJetDelphes_hh
# define HJetDelphes_hh

// # include <sstream>

# include "HJet.hh"

struct HConstituent{

  TLorentzVector Momentum;
  TLorentzVector Vertex;
  int MotherId;

};

/**
 * @brief Delphes jets
 *
 */
class hdelphes::HJet : public hanalysis::HJet
{

public:

    /**
     * @brief constructor
     *
     */
    HJet();

    /**
     * @brief Destructor
     *
     */
    ~HJet();

    /**
     * @brief Initialize new event
     *
     * @return void
     */
    void NewEvent(const hanalysis::HClonesArray *const NewClonesArrays);

    float GetScalarHt();

private:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const HJetDetails JetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow(const HJetDetails JetDetails);

    /**
     * @brief Get Tau Tag
     *
     * @return void
     */
    void GetTau(const Jet *const);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();

    template<typename TData>
    void PrintCell(TData const Data) const {

        std::cout << std::right << std::setw(9) << std::setfill(' ') << Data;

    }

    void PrintTruthLevel(const int Severity) const;

    std::string PrintParticle(const int Position) const;

    std::vector<int> Topology;

    std::vector<int *> BranchVector;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);

    HJets TagJets(HJets);

    HJets JetTagger(HJets, HJets, int);

    HJets JetTagger(HJets, HJets);

    template <typename TClone>
    hanalysis::HJetInfo GetJetId(const TClone &Clone) {

        Print(3, "Get Jet Id", Clone->Particles.GetEntriesFast());

        hanalysis::HJetInfo JetInfo;

        for (int ParticleNumber = 0; ParticleNumber < Clone->Particles.GetEntriesFast(); ++ParticleNumber) {

            const TObject *const Object = Clone->Particles.At(ParticleNumber);
            const int MotherId = GetMotherId(Object);
            Print(3, "MotherId", MotherId);


            const GenParticle *const ParticleClone = (GenParticle *) Object;
            JetInfo.AddConstituent(MotherId, std::abs(ParticleClone->PT));

        }

        JetInfo.PrintAllInfos(4);
        return JetInfo;

    }


    template<typename TParticle, typename TEFlow>
    bool GetIsolation(const TEFlow *const EFlowClone, const TClonesArray *const ClonesArray) const {

        bool Isolated = true;

        for (int ParticleNumber = 0; ParticleNumber < ClonesArray->GetEntriesFast(); ++ParticleNumber) {

            TParticle *ParticleClone = (TParticle *) ClonesArray->At(ParticleNumber);
            Isolated = CheckIsolation(EFlowClone, ParticleClone);

        }

        return Isolated;
    }


    int GetMotherId(const TObject *const);

    int GetMotherId(int BranchId, int Position);

    void GetDelphesTags(const Jet *const);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    PseudoJet GetConstituents(const Jet *const JetClone, hanalysis::HJet::HJetDetails JetDetails);

    HConstituent GetConstituent(const TObject *const Object, hanalysis::HJet::HJetDetails JetDetails);

    PseudoJet GetConstituentJet(const TObject *const Object, hanalysis::HJet::HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};

#endif
