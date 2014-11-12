# ifndef HEventDelphes_hh
# define HEventDelphes_hh

# include "HEvent.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"
# include "HJetDelphes.hh"

/**
 * @brief event topology for Delphes events
 *
 */
class hdelphes::HEvent  : public hanalysis::HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEvent();

    /**
     * @brief destructor
     *
     */
    ~HEvent();

    void NewEvent(const hanalysis::HClonesArray * const ClonesArrays);

    HJets GetTops(hanalysis::HJetTag *const JetTag);

    PseudoJet GetHiggs();

    HJets GetCandidates(hanalysis::HJetTag *const JetTag);

protected:

  inline std::string NameSpaceName() const
  {
    return "HDelphes";
  }

    inline std::string ClassName() const {
        return "HEvent";
    };

private:

};

#endif

