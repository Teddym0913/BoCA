#pragma once

#include "Event.hh"
#include "Singlet.hh"

namespace analysis {

class GlobalObservables {

public:

    void SetEvent(const Event& event, const analysis::Jets& jets);

    int LeptonNumber() const;

    int JetNumber() const;

    int BottomNumber() const;

    float BottomBdt() const;

    float BottomBdt(const int number) const;

    float BottomBdt(const int number_1, const int number_2) const;

    float ScalarHt() const;

    float LeptonHt() const;

    float JetHt() const;

    float MissingEt() const;

    analysis::Singlet Singlet() const;

    analysis::Jets Jets() const;

    void SetJets(const analysis::Jets jets);

private:

    analysis::Jets leptons_;
    float scalar_ht_;
    float missing_et_;
    analysis::Jets jets_;

};

}
