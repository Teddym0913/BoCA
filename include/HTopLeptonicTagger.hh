# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"

/**
 * @brief Top leptonic BDT tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public Tagger
{

public:

    HTopLeptonicTagger();

    HTopLeptonicTagger(const HBottomTagger &NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector< HTopLeptonicBranch > GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< HDoublet> GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::Reader & Reader);

    HTopLeptonicBranch GetBranch(const hanalysis::HDoublet &Doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const HDoublet &Doublet);

    HBottomTagger BottomTagger;

    Reader BottomReader;

    HTopLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
