# include "HEventHadronicTagger.hh"

hheavyhiggs::EventHadronicTagger::EventHadronicTagger()
{
  Print(kNotification , "Constructor");
  set_tagger_name("Hadronicevent");
}

hheavyhiggs::EventHadronicTagger::EventHadronicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::WHadronicTagger &NewWTagger, const analysis::TopHadronicTagger &NewTopTagger,const  analysis::HHeavyHiggsHadronicTagger &NewHeavyHiggsTagger)
{

    Print(kNotification , "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    WTagger = NewWTagger;
    WReader.set_tagger(WTagger);
    top_hadronic_tagger = NewTopTagger;
    TopHadronicReader.set_tagger(top_hadronic_tagger);
    HeavyHiggsHadronicTagger = NewHeavyHiggsTagger;
    HeavyHiggsHadronicReader.set_tagger(HeavyHiggsHadronicTagger);

    set_tagger_name("Hadronicevent");

//     Branch = new hheavyhiggs::EventHadronicBranch();

    DefineVariables();

}

hheavyhiggs::EventHadronicTagger::~EventHadronicTagger()
{

    Print(kNotification , "Constructor");

    // delete Branch;
//     delete BottomReader;
//     delete TopHadronicReader;
//     delete HeavyHiggsHadronicReader;

}

void hheavyhiggs::EventHadronicTagger::FillBranch(hheavyhiggs::EventHadronicBranch *eventHadronicBranch, const HOctet &Octet)
{
    Print(kInformation, "FillPairTagger", Octet.Bdt());

//     eventHadronicBranch->LeptonNumber = Octet.LeptonNumber();
//     eventHadronicBranch->JetNumber = Octet.JetNumber();
//     eventHadronicBranch->BottomNumber = Octet.BottomNumber();

//     eventHadronicBranch->ScalarHt = Octet.ScalarHt();
    eventHadronicBranch->HeavyParticleBdt = Octet.Bdt();

    eventHadronicBranch->HeavyHiggsBdt = Octet.sextet().Bdt();
    eventHadronicBranch->HeavyHiggsMass = Octet.sextet().Jet().m();
    eventHadronicBranch->HeavyHiggsPt = Octet.sextet().Jet().pt();

    eventHadronicBranch->BottomSumPt = Octet.doublet_jet().pt();
    eventHadronicBranch->BottomDeltaPt = Octet.doublet().DeltaPt();

    eventHadronicBranch->BottomDeltaRap = Octet.doublet().DeltaRap();
    eventHadronicBranch->BottomDeltaPhi = Octet.doublet().DeltaPhi();
    eventHadronicBranch->BottomDeltaR = Octet.doublet().DeltaR();

    eventHadronicBranch->HbSumDeltaRap = Octet.DeltaRap();
    eventHadronicBranch->HbSumDeltaPhi = Octet.DeltaPhi();
    eventHadronicBranch->HbSumDeltaR = Octet.DeltaR();

    eventHadronicBranch->HbDeltaDeltaRap = Octet.HbDeltaDeltaRap();
    eventHadronicBranch->HbDeltaDeltaPhi = Octet.HbDeltaDeltaPhi();
    eventHadronicBranch->HbDeltaDeltaR = Octet.HbDeltaDeltaR();

    eventHadronicBranch->eventTag = Octet.Tag();
}

void hheavyhiggs::EventHadronicTagger::FillBranch(const HOctet &Octet)
{
    Print(kInformation, "FillPairTagger");
    FillBranch(&Branch, Octet);
}

void hheavyhiggs::EventHadronicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(Branch.LeptonNumber, "LeptonNumber");
    AddVariable(Branch.JetNumber, "JetNumber");
    AddVariable(Branch.BottomNumber, "BottomNumber");

    AddVariable(Branch.ScalarHt, "ScalarHt");
    AddVariable(Branch.HeavyParticleBdt, "HeavyParticleBdt");

    AddVariable(Branch.HeavyHiggsBdt, "HeavyHiggsBdt");
    AddVariable(Branch.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(Branch.BottomSumPt, "BottomSumPt");
    AddVariable(Branch.BottomDeltaPt, "BottomDeltaPt");

    AddVariable(Branch.BottomDeltaRap, "BottomDeltaRap");
    AddVariable(Branch.BottomDeltaPhi, "BottomDeltaPhi");
    AddVariable(Branch.BottomDeltaR, "BottomDeltaR");

    AddVariable(Branch.HbSumDeltaRap, "HbSumDeltaRap");
    AddVariable(Branch.HbSumDeltaPhi, "HbSumDeltaPhi");
    AddVariable(Branch.HbSumDeltaR, "HbSumDeltaR");

    AddVariable(Branch.HbDeltaDeltaRap, "HbDeltaDeltaRap");
    AddVariable(Branch.HbDeltaDeltaPhi, "HbDeltaDeltaPhi");
    AddVariable(Branch.HbDeltaDeltaR, "HbDeltaDeltaR");

    AddSpectator(Branch.eventTag, "eventTag");
    AddSpectator(Branch.HeavyHiggsMass, "HeavyHiggsMass");

    Print(kNotification, "Variables defined");

}

std::vector<hheavyhiggs::EventHadronicBranch * > hheavyhiggs::EventHadronicTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    std::vector<hheavyhiggs::EventHadronicBranch *> eventHadronicBranches;

    Jets jets = event.hadrons().GetStructuredJets();
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    if (jets.size() < 8) return eventHadronicBranches;

    std::vector<analysis::Doublet> doublets = WTagger.GetBdt(jets, WReader);
    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
    std::vector<analysis::Sextet> sextets = HeavyHiggsHadronicTagger.GetBdt(triplets, HeavyHiggsHadronicReader);

    std::vector<HOctet> Octets;

    for (const auto & Jet1 : jets)
        for (const auto & Jet2 : jets)  {
            if (Jet1 == Jet2) continue;
            analysis::Doublet doublet(Jet1,Jet2);
            for (const auto & sextet : sextets) {
                if (Jet1 == sextet.triplet1().singlet()) continue;
                if (Jet1 == sextet.triplet1().doublet().Singlet1()) continue;
                if (Jet1 == sextet.triplet1().doublet().Singlet2()) continue;
                if (Jet1 == sextet.triplet2().singlet()) continue;
                if (Jet1 == sextet.triplet2().doublet().Singlet1()) continue;
                if (Jet1 == sextet.triplet2().doublet().Singlet2()) continue;
                if (Jet2 == sextet.triplet1().singlet()) continue;
                if (Jet2 == sextet.triplet1().doublet().Singlet1()) continue;
                if (Jet2 == sextet.triplet1().doublet().Singlet2()) continue;
                if (Jet2 == sextet.triplet2().singlet()) continue;
                if (Jet2 == sextet.triplet2().doublet().Singlet1()) continue;
                if (Jet2 == sextet.triplet2().doublet().Singlet2()) continue;
                Octets.emplace_back(HOctet(sextet, doublet));
            }
        }

    if (Octets.size() > 1) {
      std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    for (auto & Octet : Octets) {
        hheavyhiggs::EventHadronicBranch *eventHadronicBranch = new hheavyhiggs::EventHadronicBranch();
//         Octet.SetLeptonNumber(event.leptons().GetLeptonJets().size());
//         Octet.SetJetNumber(event.hadrons().GetJets().size());
//         Octet.SetBottomNumber(event.hadrons().GetBottomJets().size());
//         Octet.SetScalarHt(event.hadrons().GetScalarHt());
        Octet.SetTag(Tag);
        FillBranch(eventHadronicBranch, Octet);
        eventHadronicBranches.emplace_back(eventHadronicBranch);
    }

    return eventHadronicBranches;

}
