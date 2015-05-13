# ifndef HEventSemiTagger_hh
# define HEventSemiTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HOctet.hh"
# include "HOctet44Event.hh"
# include "HSignatureSemiTagger.hh"

/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class hheavyhiggs::HEventSemiTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventSemiTagger();

    /**
    * @brief Destructor
    *
    */
    ~HEventSemiTagger();

    void SetTagger(
        const hanalysis::BottomTagger &NewBottomTagger,
        const hanalysis::HJetPairTagger &NewJetPairTagger,
        const hanalysis::HWSemiTagger &NewWSemiTagger,
        const hanalysis::WHadronicTagger &NewWTagger,
        const hanalysis::HTopSemiTagger &NewTopSemiTagger,
        const hanalysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
        const HSignatureSemiTagger &NewSignatureSemiTagger);

    std::vector<HEventSemiBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HEventMultiplet< HOctet > > GetBdt(const std::vector< HOctet > &Octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, HEventStruct &EventStruct, const hanalysis::Reader &EventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry);

    HEventSemiBranch GetBranch(const HEventMultiplet< HOctet > &Octet) const;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger WTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;
    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    hanalysis::HJetPairTagger JetPairTagger;
    HSignatureSemiTagger SignatureSemiTagger;

    hanalysis::Reader BottomReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader HeavyHiggsSemiReader;
    hanalysis::Reader JetPairReader;
    hanalysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventSemiTagger";
    }

private:

    void DefineVariables();

    std::vector<HOctet> GetHeavyHiggsEvents(Jets &jets);

    HEventSemiBranch Branch;
    hanalysis::HJetTag JetTag;

};

# endif
