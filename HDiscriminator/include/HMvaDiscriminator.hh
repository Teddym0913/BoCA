# ifndef HMvaDiscriminator_hh
# define HMvaDiscriminator_hh


# include "HMva.hh"
# include "HBranchDiscriminator.hh"

/**
 * \class HMvaDiscriminator
 *
 * @brief Prepares multivariant analysis
 *
 */
class hcpvhiggs::HMva : public hmva::HMva
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

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *);

protected:


private:

      HCandidateBranch *Candidate;

    void DefineVariables();

    virtual inline std::string ClassName() const {
        return "HiggsCPV: HMva";
    };


};

# endif
