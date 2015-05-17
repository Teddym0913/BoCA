# ifndef HHiggsTagger_hh
# define HHiggsTagger_hh

# include "fastjet/tools/Filter.hh"

# include "HReconstruction.hh"

/**
 * @brief Higgs tagger as described in arXiv:0802.2470
 *
 * based on fastjet example 12
 *
 */
class analysis::HHiggsTagger : public HReconstruction
{

public:

    /**
     * @brief dipolarity of the HiggsJet
     *
     */
//     float DiPolarity;

    /**
     * @brief Jet tagged as Higgs
     *
     */
    fastjet::PseudoJet HiggsJet;

    /**
     * @brief Originial fat jet
     *
     */
//     fastjet::PseudoJet FatJet;

    /**
     * @brief Reconstruct the higgs fat jet
     * 
     */
    fastjet::PseudoJet GetHiggsJet(const Jets&, const Jets&, const Jets&);

    /**
     * @brief constructor
     *
     */
    HHiggsTagger();

    /**
     * @brief destructor
     *
     */
    ~HHiggsTagger();

    void NewEvent();

private:

    /**
     * @brief Initial value
     *
     */
    int InitialValue;

    /**
     * @brief abitry user index used to identify bottoms
     *
     */
    int BottomUserIndex;

    /**
     * @brief abitry user index used to identify charms
     *
     */
    int CharmUserIndex;

    /**
     * @brief Vector of Fat Jet Pieces
     *
     */
    Jets FilteredJetPieces;
    
    /**
     * @brief Filter Jets
     * 
     */
    fastjet::PseudoJet GetFilteredJet(const fastjet::PseudoJet&, const fastjet::JetAlgorithm&, const int);

    /**
     * @brief Compare subjets with particle quarks
     * 
     */
    void GetSubJetSource(const Jets&, const int);

    /**
     * @brief Apply Bottom tagger
     * 
     */
    int BTagger();

    /**
     * @brief Get Dipolarity
     * 
     */
    float GetDipolarity(const fastjet::PseudoJet &);

    /**
     * @brief Rap of Subjets and constituent
     *
     */
    float Rap0, Rap1, Rap2;

    /**
     * @brief Phi of Subjets and constituent
     *
     */
    float Phi0, Phi1, Phi2;

    /**
     * @brief Delta R between Subjets and constituent
     *
     */
    float DeltaR01, DeltaR02, DeltaR12;

    float DeltaR12Sqr() {
        return pow(DeltaR12, 2);
    }

    float DeltaPhi() {
        return (Phi2 - Phi1);
    }

    float DeltaPhiSqr() {
        return pow(DeltaPhi(), 2);
    }

    float DeltaRap() {
        return -(Rap2 - Rap1);
    }

    float DeltaRapSqr() {
        return pow(DeltaRap(), 2);
    }

    float RapPhi() {
        return Rap2 * Phi1 - Rap1 * Phi2;
    }

    float DeltaRapPhi() {
        return DeltaPhi() * DeltaRap();
    }

    float DeltaPhiRap0() {
        return DeltaPhi() * Rap0;
    }

    float DeltaRapPhi0() {
        return DeltaRap() * Phi0;
    }

    void SetRapPhi(fastjet::PseudoJet &SubJet1, fastjet::PseudoJet &SubJet2);

    float GetSubDeltaR();

    inline std::string ClassName() const {
        return ("HHiggsTagger");
    };

};

# endif
