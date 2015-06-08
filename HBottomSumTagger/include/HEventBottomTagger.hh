# pragma once

# include "BottomTagger.hh"
# include "Reader.hh"

namespace hbottomsumtagger
{

class EventBottomMultiplet : public analysis::Identification
{
public:

//     float Bdt() const {
//       float bdt =0;
//       for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
//       return bdt;
//     }


    inline float TotalBottomBdt(const unsigned Number) const {
        if (jets_.size() < Number) return 0;
        return jets_.at(Number - 1).user_info<analysis::JetInfo>().Bdt();
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2) const {
        return TotalBottomBdt(Number1) + TotalBottomBdt(Number2);
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2, const unsigned Number3) const {
        return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3);
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2, const unsigned Number3, const unsigned Number4) const {
        return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3) + TotalBottomBdt(Number4);
    }

    void SetJets(const analysis::Jets &NewJets) {
        jets_ = NewJets;
        float bdt = 0;
        for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
        SetBdt(bdt);
    }

private:

    analysis::Jets jets_;

};


/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventBottomTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventBottomTagger();

    bool TruthLevelCheck(const analysis::Jets &NewJets, analysis::Event &event, const analysis::Object::Tag Tag);

    void SetTagger(const analysis::BottomTagger &NewBottomTagger);

    std::vector<analysis::EventBottomTaggerBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector<EventBottomMultiplet> GetBdt(const analysis::Jets &jets, const analysis::Reader &eventSemiReader);

//     std::vector<int> ApplyBdt2(const exroot::TreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    analysis::EventBottomTaggerBranch GetBranch(const hbottomsumtagger::EventBottomMultiplet &event) const;

    analysis::BottomTagger bottom_tagger_;

    analysis::Reader BottomReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventBottomTagger";
    }

private:

    virtual TClass &Class() const {
        return *analysis::EventBottomTaggerBranch::Class();
    }

    void DefineVariables();

    analysis::EventBottomTaggerBranch branch_;

};

}
