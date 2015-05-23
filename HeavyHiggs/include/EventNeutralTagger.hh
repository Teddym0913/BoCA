# pragma once

# include "Branch.hh"
# include "Octet62.hh"
# include "MultipletEvent.hh"
# include "SignatureNeutralTagger.hh"

namespace heavyhiggs {

/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventNeutralTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventNeutralTagger();

    /**
    * @brief Destructor
    *
    */
    ~EventNeutralTagger();

    void SetTagger(
        const analysis::BottomTagger &NewBottomTagger,
        const analysis::HJetPairTagger &NewJetPairTagger,
        const analysis::WSemiTagger &Neww_semi_tagger,
        const analysis::WHadronicTagger &NewWTagger,
        const analysis::TopSemiTagger &Newtop_semi_tagger,
        const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
        const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger,
        const SignatureNeutralTagger &NewSignatureSemiTagger);

    std::vector<EventNeutralBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< analysis::MultipletEvent< Octet62 > > GetBdt(const std::vector< Octet62 > &octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, analysis::GlobalObservables &global_observables, const analysis::Reader &eventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventNeutralBranch GetBranch(const analysis::MultipletEvent< Octet62 > &octet) const;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger WTagger;
    analysis::TopSemiTagger top_semi_tagger;
    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;
    analysis::HJetPairTagger JetPairTagger;
    SignatureNeutralTagger SignatureSemiTagger;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader JetPairReader;
    analysis::Reader SignatureSemiReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventNeutralTagger";
    }

private:

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    EventNeutralBranch Branch;
    analysis::JetTag jet_tag;

};

}
