# ifndef HMvaHiggsTagger_hh
# define HMvaHiggsTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
# include "HBottomTagger.hh"
# include "HSuperStructure.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HMvaHiggsTagger : public hmva::HMva
{

public:

    HMvaHiggsTagger();

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, HBottomTagger *BottomTagger);

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){ HReaderStruct ReaderStruct; return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};

    float GetBdt(TObject *Branch, TMVA::Reader *Reader);

    //     std::vector<HLeptonicTopBranch *> GetBottomTag(hanalysis::HEvent *const Event, const HState State);


//     template<typename TMva>
    void SetMva() {

        Print(HNotification,"Set Mva");

        Reader = new hmva::HReader(this);
        Reader->AddVariable();
        Reader->BookMVA();

    }

    float GetHiggsBdt(const hdelphes::HSuperStructure &Higgs);

private:

    hmva::HReader *Reader;

    HHiggsBranch *Higgs;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    void FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHiggsBranch *HiggsTagger);

//     float GetDeltaR(const fastjet::PseudoJet &Jet);


    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

#endif
