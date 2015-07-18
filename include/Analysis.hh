#pragma once

#include "AnalysisBase.hh"
#include "Reader.hh"
#include "Branches.hh"
#include <sys/stat.h>

namespace analysis {

class Files {
public:

    Files(const std::string name, Stage stage, Tag tag) : export_file_ {name.c_str(), "Recreate"} {
        stage_ = stage;
        tag_ = tag;
    }
    TFile& export_file()
    {
        return export_file_;
    }
    File& file()
    {
        return *file_;
    }
    Stage stage() const
    {
        return stage_;
    }
    Tag tag() const
    {
        return tag_;
    }
    void file(File& file)
    {
        file_ = &file;
    }
private:
    TFile export_file_;
    File* file_;
    Stage stage_;
    Tag tag_;
};

class Trees {
public:

    Trees(Files& files) :
        clones_arrays_(files.file().clones_arrays()),
        event_(files.file().event()),
        tree_writer_(exroot::TreeWriter(&(files.export_file()), files.file().Title().c_str())
                    ) {}

    void WriteTree()
    {
        if (!analysis_empty_)
            tree_writer_.Write();
    }

    void UseBranches(File& file, const std::string& name, long event_number_max)
    {
        tree_branch_ = tree_writer_.NewBranch(name.c_str(), InfoBranch::Class());
        tree_reader_ = file.TreeReader();
        clones_arrays_.UseBranches(tree_reader_);
        info_branch_ = FillInfoBranch(tree_reader_, file, event_number_max);
    }

    void NewEvent(const int mass)
    {
        tree_reader_.ReadEntry(event_number_);
        event_.NewEvent(clones_arrays_);
        event_.SetMass(mass);
    }

    void SaveAnalysis(const int object_number)
    {
        if (object_number == 0)
            return;
        object_sum_ += object_number;
        info_branch_.PreCutNumber = event_number_;
        analysis_empty_ = false;
        static_cast<InfoBranch&>(*tree_branch_->NewEntry()) = info_branch_;
        tree_writer_.Fill();
    }

    InfoBranch FillInfoBranch(const exroot::TreeReader& tree_reader, const File& file, long int event_number_max)
    {
        InfoBranch info_branch;
        info_branch.Crosssection = file.crosssection();
        info_branch.CrosssectionError = file.crosssection_error();
        info_branch.Mass = file.mass();
        info_branch.EventNumber = std::min((long)tree_reader.GetEntries(), event_number_max);
        info_branch.Name = file.nice_name();
//         info_branch.NiceName = file.nice_name();
        return info_branch;
    }
    void AddPreCut(const int number)
    {
        pre_cut_sum_ += number;
    }
    exroot::TreeReader& tree_reader()
    {
        return tree_reader_;
    }
    exroot::TreeWriter& tree_writer()
    {
        return tree_writer_;
    }
    Event& event()
    {
        return event_;
    }

    long& object_sum()
    {
        return object_sum_;
    }
    int event_number_ = 0;
private:
    exroot::TreeReader tree_reader_;
    exroot::TreeBranch* tree_branch_;
    exroot::TreeWriter tree_writer_;
    ClonesArrays clones_arrays_;
    Event event_;
    InfoBranch info_branch_;
    int pre_cut_sum_ = 0;
    long object_sum_ = 0;
    bool analysis_empty_ = true;
};

/**
 * @brief Base for analyses
 *
 */
template<typename Tagger>
class Analysis : public AnalysisBase {

public:

    void AnalysisLoop(const Stage stage) final {
        mkdir(ProjectName().c_str(), 0700);
        Reader<Tagger> reader(stage);
        tagger_.ClearTreeNames();
        for (const auto& tag : std::vector<Tag> {Tag::signal, Tag::background})
        {
            Files files(ExportName(stage, tag), stage, tag);
            ClearFiles();
            SetFiles(tag);
            for (auto& file : this->files(tag)) {
                files.file(file);
                AnalyseFile(files, reader);
            }
            files.export_file().Close();
        }
    }


protected:

    void AnalyseFile(Files& files, Reader<Tagger>& reader)
    {
        Trees trees(files);
        SetTreeBranch(files.stage(), trees.tree_writer(), reader);
        trees.UseBranches(files.file(), tagger_.weight_branch_name(), EventNumberMax());
        if (files.stage() == Stage::reader) {
            trees.event_number_ = std::min((long)trees.tree_reader().GetEntries(), EventNumberMax()) / 2;    // TODO fix corner cases
        }
        for (; trees.event_number_ < trees.tree_reader().GetEntries(); ++trees.event_number_) {
            DoAnalysis(files, trees, reader);
            if (trees.object_sum() >= EventNumberMax())
                break;
        }
        trees.WriteTree();
    }

    void SetTreeBranch(const Stage& stage, exroot::TreeWriter& tree_writer, Reader<Tagger>& reader)
    {
        switch (stage) {
        case Stage::trainer :
            tagger_.SetTreeBranch(tree_writer, stage);
            break;
        case Stage::reader :
            reader.tagger().SetTreeBranch(tree_writer, stage);
            break;
        }
    }

    void DoAnalysis(Files& files, Trees& trees, Reader<Tagger>& reader)
    {
        trees.NewEvent(files.file().mass());
        int pre_cut = PassPreCut(trees.event());
        if (pre_cut > 0) {
            trees.AddPreCut(pre_cut);
            trees.SaveAnalysis(RunAnalysis(trees.event(), reader, files.stage(), files.tag()));
        }
        trees.tree_writer().Clear();
    }

    int RunAnalysis(const Event& event, const Reader<Tagger>& reader, const Stage stage, const Tag tag)
    {
        switch (stage) {
        case Stage::trainer :
            return tagger_.Train(event, pre_cuts(), tag);
        case Stage::reader :
            return reader.Bdt(event, pre_cuts());
        default :
            return 0;
        }
    }

    const Tagger& tagger() const final
    {
        return tagger_;
    }

    Tagger& tagger() final {
        return tagger_;
    }

private:

    Tagger tagger_;

};

}
