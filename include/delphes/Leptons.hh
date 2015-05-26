# pragma once

# include "../Leptons.hh"
# include "JetInfo.hh"

namespace analysis
{

namespace delphes
{

/**
 * @brief Delphes leptons
 *
 */
class Leptons : public analysis::Leptons
{

public:


    /**
     * @brief constructor
     *
     */
    Leptons();

private:

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetElectrons();

    bool GetElectrons(JetDetail jet_detail);

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    bool GetMuons();

    bool GetMuons(JetDetail jet_detail);

//   Jets GetLeptons(Hjet_detail jet_detail);

    inline std::string NameSpaceName() const {
        return "delphes";
    }

};

}

}