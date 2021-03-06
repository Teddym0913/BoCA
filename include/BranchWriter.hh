/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "io/FileWriter.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "File.hh"
#include <mutex>

namespace boca
{

template<typename Tagger_>
class BranchWriter
{

public:

    BranchWriter(boca::Phase& phase, boca::File& file, boca::FileWriter& file_writer, Tagger_& tagger) :
        phase_(phase),
        import_file_(file),
        file_writer_(file_writer),
        tagger_(tagger),
        reader_(phase.Stage()) {
        tree_writer_ = &FileWriter().NewTree(Import().Title());
        switch (Phase().Stage()) {
        case Stage::trainer : tagger_.NewBranch(TreeWriter(), Phase().Stage());
            break;
        case Stage::reader : reader_.NewBranch(TreeWriter(), Phase().Stage());
            break;
        }
        tree_branch_ = &(tree_writer_->NewBranch<InfoBranch>(tagger_.WeightBranchName()));
    }

    ~BranchWriter() {
        std::cout << "PreCut ratio: " << RoundToDigits(double(object_sum_) / event_sum_) << std::endl;
        if (object_sum_) TreeWriter().Write();
    }

    void SafeEntry() {
        InfoBranch info_branch(Import());
        info_branch.SetEventNumber(EventSum());
        std::lock_guard<std::mutex> lock(write_mutex);
        TreeBranch().AddEntry(info_branch);
        TreeWriter().Fill();
    }
    void Increment(int number) {
        std::lock_guard<std::mutex> lock(sum_mutex);
        object_sum_ += number;
//         if (number > 0)
          ++event_sum_;
    }

    boca::Reader<Tagger_> Reader() const {
        return reader_;
    }

    Tagger_ Tagger() const {
        return tagger_;
    }

    bool KeepGoing(std::function<long(Stage)> const& event_number_max) const {
      return object_sum_ < event_number_max(Phase().Stage());
    }

    boca::Phase Phase() const {
        return phase_;
    }

    boca::File Import() const {
        return import_file_;
    }

private:

    long EventSum() const {
        return event_sum_;
    }

    boca::FileWriter& FileWriter() {
        return file_writer_;
    }

    boca::TreeBranch& TreeBranch() {
        return *tree_branch_;
    }

    boca::TreeWriter& TreeWriter() {
        return *tree_writer_;
    }

    long object_sum_ = 0;

    long event_sum_ = 0;

    boca::Phase phase_;

    File& import_file_;

    boca::FileWriter& file_writer_;

    Tagger_& tagger_;

    boca::Reader<Tagger_> reader_;

    boca::TreeWriter* tree_writer_;

    boca::TreeBranch* tree_branch_;

    std::mutex sum_mutex;

    std::mutex write_mutex;

};

}


