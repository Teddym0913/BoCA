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

    std::vector<EventNeutralBranch> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag){
      Print(kError, "get branches","depreciated");
      std::vector<EventNeutralBranch>{};
    }

    int Train(analysis::Event &event, const Tag tag);

    std::vector< analysis::MultipletEvent< Octet62 > > GetBdt(const std::vector< Octet62 > &octets, const Jets &jets, const Jets &SubJets, const Jets &Leptons, analysis::GlobalObservables &global_observables, const analysis::Reader &eventSemiReader){
      Print(kError, "get bdt","depreciated");
      std::vector< analysis::MultipletEvent< Octet62 > >{};
    }

    std::vector< analysis::MultipletEvent< Octet62 > > OctetEvent(analysis::Event &event, const TMVA::Reader &reader);

    float ReadBdt(const TClonesArray& clones_array, const int entry);

//     analysis::GlobalObservables global_observables(analysis::Event &event);

    EventNeutralBranch GetBranch(const analysis::MultipletEvent< Octet62 > &octet) const;

    SignatureNeutralTagger signature_neutral_tagger_;

    analysis::Reader signature_neutral_reader_;

    TClass &Class() const {
      return *EventNeutralBranch::Class();
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "heavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "EventNeutralTagger";
    }

private:


  int SaveEntries(const std::vector<analysis::MultipletEvent<Octet62>> &events) {
    for (const auto & event : events) static_cast<EventNeutralBranch &>(*tree_branch().NewEntry()) = GetBranch(event);
    return events.size();
  }

    void DefineVariables();

    std::vector<Octet62> GetHeavyHiggsevents(Jets &jets);

    EventNeutralBranch branch_;

};

}
