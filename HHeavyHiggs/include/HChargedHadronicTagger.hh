# ifndef HChargedHadronicTagger_hh
# define HChargedHadronicTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HChargedHiggsHadronicTagger.hh"
# include "HOctet44.hh"

/**
 *
 * @brief Event BDT tagger for hadronic heavy higgs
 *
 */
class hheavyhiggs::HChargedHadronicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedHadronicTagger(
      const hanalysis::HBottomTagger &NewBottomTagger,
      const hanalysis::HWHadronicTagger &NewWTagger,
      const hanalysis::HTopHadronicTagger &NewTopTagger,
      const hanalysis::HChargedHiggsHadronicTagger &NewHeavyHiggsTagger);

    /**
    * @brief Destructor
    *
    */
    ~HChargedHadronicTagger();

    std::vector<hheavyhiggs::HChargedHadronicBranch *> GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag);

    void FillBranch(const HOctet44 &Octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HChargedHadronicTagger";
    };


private:

  void FillBranch(hheavyhiggs::HChargedHadronicBranch *EventHadronicBranch, const HOctet44 &Octet);

    void DefineVariables();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWHadronicTagger WTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HChargedHiggsHadronicTagger ChargedHiggsHadronicTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader ChargedHiggsHadronicReader;

    hheavyhiggs::HChargedHadronicBranch Branch;

};

# endif
