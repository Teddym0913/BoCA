# ifndef HMvaBTagger_hh
# define HMvaBTagger_hh


# include "Tagger.hh"
# include "HBranchBTagger.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hbtagger::HMva : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HMva();

    /**
    * @brief Destructor
    *
    */
    ~HMva();

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);


    float GetBdt(TObject *, const TMVA::Reader &){ return 0;};

protected:


private:

      HBTaggerBranch *Candidate;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMvaBTagger";
    };


};

# endif
