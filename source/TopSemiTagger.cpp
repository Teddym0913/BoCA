# include "TopSemiTagger.hh"

analysis::TopSemiTagger::TopSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (TopMass - WMass) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

void analysis::TopSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.WPt, "WPt");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.WBdt, "WBdt");
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int analysis::TopSemiTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{
    Print(kInformation, "Get Top Tags");

    float pre_cut = 0;

    int WSemiId = w_semi_tagger_.WSemiId(event);
    Jets top_particles = event.partons().Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    top_particles = RemoveIfWrongParticle(top_particles, TopSemiId);

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<analysis::Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    Jets leptons = event.leptons().GetLeptonJets();
    Print(kInformation, "Lepton Number", leptons.size());

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
              Triplet triplet(doublet, Jet);
              triplet.SetTag(tag);
              std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cut,tag);
              if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
            }
        }
    }

    for (const auto & jet : jets) {
        for (const auto & lepton : leptons) {
            Doublet doublet(lepton);
            Triplet triplet(doublet, jet);
            triplet.SetTag(tag);
            std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cut,tag);
            if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
        }
    }

    std::vector<TopSemiBranch> top_semi_branches;
    if (tag == kSignal && triplets.size() > top_particles.size()) {
        std::sort(triplets.begin(), triplets.end(), SortByMass(TopMass));
        triplets.erase(triplets.begin() + top_particles.size(), triplets.end());
    }
    Print(kInformation, "Number triplets", triplets.size());

    return SaveEntries<TopSemiBranch>(triplets);
}

std::vector<analysis::Triplet> analysis::TopSemiTagger::CleanTriplets(const Triplet &triplet, Jets TopQuarks, float pre_cut, const Tag tag) {
    std::vector<analysis::Triplet> triplets;
    for(const auto particle : TopQuarks) JoinVectors(triplets,CleanTriplet(triplet,particle,pre_cut,tag));
    return triplets;
}

std::vector<analysis::Triplet> analysis::TopSemiTagger::CleanTriplet(const Triplet &triplet, fastjet::PseudoJet TopQuark, float pre_cut, const Tag tag) {
    std::vector<analysis::Triplet> triplets;
    if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) return triplets ; // should be enabled again
    if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) return triplets;
    if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) return triplets;
    if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) return triplets;
    triplets.push_back(triplet);
    return triplets;
}


std::vector<analysis::Triplet>  analysis::TopSemiTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<analysis::Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                branch_ = branch<TopSemiBranch>(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
            }
        }
    }

    for (const auto & Jet : jets) {
        for (const auto & Predoublet : doublets) {
            Doublet doublet(Predoublet.Singlet1());
            Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - TopMass) > TopWindow) continue; // reactivate this check
            branch_ = branch<TopSemiBranch>(triplet);
            triplet.SetBdt(Bdt(reader));
            triplets.emplace_back(triplet);
        }
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;
}



float analysis::TopSemiTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float analysis::TopSemiTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
