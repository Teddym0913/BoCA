# pragma once

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ClonesArrays.hh"
# include "Event.hh"

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class analysis::File : public Object
{

public:

    /**
     * @brief constructor
     *
     */
    File();

    File(const std::string &process);

    File(const std::string &process, const float crosssection);

    File(const std::string &process, const float crosssection, const float mass);

    File(const std::string &process, const std::string &run_folder);

    File(const Strings &processes);

    File(const Strings &processes, const float crosssection);

    File(const Strings &processes, const float crosssection, const float mass);

    File(const std::string &process, const std::string &run_folder, const std::string &file_suffix);

    /**
     * @brief destructor
     *
     */
    ~File();

    ExRootTreeReader TreeReader();

    analysis::ClonesArrays clones_arrays();

    analysis::Event event();

    /**
     * @brief Name of Process
     *
     */
    std::string Title() const;

    float crosssection() const {
        return crossection_;
    }

    void set_crosssection(const float crosssection) {
        crossection_ = crosssection;
    }

    void set_crosssection_error(const float crosssection_error) {
        crosssection_error_ = crosssection_error;
    }

    void set_mass(const float mass) {
        mass_ = mass;
    }

    std::string file_suffix() const;

    float crosssection_error() const {
        return crosssection_error_;
    }

    float mass() const {
        return mass_;
    }
    ClonesArrays::Source source() const {
        return source_;
    }

    std::string tree_name() const;

    Strings Paths() const;

protected:

    void  SetVariables();

    std::string MadGraphFilePath() const;

    virtual inline std::string ClassName() const {
        return "File";
    }

private:

    std::string base_path_ = "$HOME/Development/MadGraph/";

    Strings process_folders_;

    std::string run_folder_;

    std::string tag_name_;

    std::string tree_name_;

    float crossection_ = 1;

    float crosssection_error_ = 0;

    float mass_ = 0;

    std::string file_suffix_ = ".root";

    ClonesArrays::Source source_ = ClonesArrays::ClonesArrays::kDelphes;

    TChain *chain_ = NULL;

};