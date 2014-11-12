# include "HFile.hh"

hanalysis::HFile::HFile()
{

    Print(1, "Constructor");

    SetVariables();

}

hanalysis::HFile::HFile(const std::string &Process)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

}

hanalysis::HFile::HFile(const std::string &Process, const std::string &Run)
{

    Print(1, "Constructor");

    SetVariables();

    ProcessFolder = Process;

    RunFolder = Run;

}

std::string hanalysis::HFile::GetTitle() const
{

  return (ProcessFolder + "-" + RunFolder);

}

std::string hanalysis::HFile::GetMadGraphFilePath() const
{

    return (BasePath + ProcessFolder + "/Events/" + RunFolder + "/");

}

// TString Analysis::HFile::BasePath = "$HOME/Development/madgraph/";
std::string hanalysis::HFile::BasePath = "$HOME/Development/MadGraph/";

std::string hanalysis::HFile::FileSuffix = "_delphes_events.root";

std::string hanalysis::HFile::TreeName = "Delphes";

bool hanalysis::HFile::SnowMass = 0;

void hanalysis::HFile::SetVariables()
{

    Print(2, "Set Variables");

    //     MadGraphPath = "/data/hajer/MadGraph/";
    //     MadGraphPath = "$HOME/Development/MadGraph/";
//     BasePath = "$HOME/Development/madgraph/";

    RunFolder = "run_01";

    TagName = "tag_1";

//     TreeString = "Delphes";

    Crosssection = 0;

    Error = 0;

}



std::string hanalysis::HFile::GetTreeName() const
{

    Print(2, "Get Tree String");

    return TreeName;
}


std::string hanalysis::HFile::GetFilePath() const
{

    Print(2, "FilePath");

    return (BasePath + ProcessFolder + FileSuffix);

}



ExRootTreeReader *hanalysis::HFile::GetTreeReader()
{

    Print(1, "Get Tree Reader", GetFilePath());

    // Import file
    const std::string ImportPath = GetFilePath();
//   TFile * const
    ImportFile = new TFile(ImportPath.c_str());
    //     TFile ImportFile = TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    const std::string ImportTreeName = GetTreeName();
//   TTree * const
    ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
    //     TTree ImportTree = (TTree)ImportFile.Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    TreeReader = new ExRootTreeReader(ImportTree);

    return TreeReader;

}

hanalysis::HClonesArray *hanalysis::HFile::GetClonesArrays()
{

    Print(1, "Get Clones Arrays");

//     HClonesArray *ClonesArrays;

    if (GetTreeName() == "Delphes") {

        if (SnowMass) {

            ClonesArrays = new hdelphes::HClonesArraySnowmass();

        } else {

            ClonesArrays = new hdelphes::HClonesArray();

        }

    } else if (GetTreeName() == "LHEF") {

        ClonesArrays = new hparton::HClonesArray();

    } else if (GetTreeName() == "LHCO") {

        ClonesArrays = new hpgs::HClonesArray();

    } else {

        Print(0, "unknown Tree String", GetTreeName());

    }

    return ClonesArrays;

}

hanalysis::HEvent *hanalysis::HFile::GetEvent()
{

    Print(1, "Get Event");

//     HEvent *Event;

    if (GetTreeName() == "Delphes") {

        Event = new hdelphes::HEvent();

    } else if (GetTreeName() == "LHEF") {

        Event = new hparton::HEvent();

    } else if (GetTreeName() == "LHCO") {

        Event = new hpgs::HEvent();

    } else {

        Print(0, "unknown Tree String", GetTreeName());

    }

    return Event;

}



hanalysis::HFile::~HFile()
{

    Print(1, "Destructor");

    delete ImportFile;
    delete ImportTree;
    delete TreeReader;
    delete ClonesArrays;
    delete Event;

}
