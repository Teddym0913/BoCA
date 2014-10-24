# include "HAnalysis.hh"

Analysis::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

//     DebugLevel=4;

}

void Analysis::HAnalysis::AnalysisLoop()
{

    Print(1, "Analysis Loop");

    for (const auto & StudyName : GetStudyNames()) {

        Print(1, "Analysing Mva Sample", StudyName);

        HClonesArray *const ClonesArrays = GetClonesArrays(StudyName);

        HEvent *const Event = GetEvent(StudyName);

        TFile *const ExportFile = GetExportFile(StudyName);

        for (const auto * const File : GetFiles(StudyName)) {

            bool AnalysisNotEmpty = 0;

            ExRootTreeWriter *const TreeWriter = GetTreeWriter(ExportFile, File->Title());

            ExRootTreeBranch *const InfoBranch = TreeWriter->NewBranch("Info", HInfoBranch::Class());

            const ExRootTreeReader *const TreeReader = GetTreeReader(File, ClonesArrays);

            ExRootProgressBar ProgressBar(GetEventSum(TreeReader));

            Print(2,"Sum",GetEventSum(TreeReader));

            for (const int EventNumber : HRange(GetEventSum(TreeReader))) {

                Print(2,"Event Number",EventNumber);

                Event->NewEvent(ClonesArrays);

                const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

                const bool Successfull = Analysis(Event, StudyName);

                if (Successfull) {

                    AnalysisNotEmpty = 1;

                    FillInfoBranch(TreeReader, InfoBranch, File);

                    TreeWriter->Fill();

                }

                TreeWriter->Clear();


//                 ProgressBar.Update(EventNumber);
            }

            Print(1, "All Events analysed", GetEventSum(TreeReader));

            ProgressBar.Finish();

            if (AnalysisNotEmpty) TreeWriter->Write();

            ClonesArrays->ResetBranches();

            delete TreeReader;

            delete TreeWriter;

            if (DebugLevel > 0) cout << endl;

        }

        ExportFile->Close();

        delete ExportFile;

        delete Event;

        delete ClonesArrays;

    }

    Print(1, "All Samples analysed");

}

void Analysis::HAnalysis::FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File)
{

    HInfoBranch *Info = static_cast<HInfoBranch *>(InfoBranch->NewEntry());
    Info->Crosssection = File->Crosssection;
    Info->Error = File->Error;
    Info->EventNumber = GetEventSum(TreeReader);

}

Analysis::HClonesArray *Analysis::HAnalysis::GetClonesArrays(const string StudyName) const
{

    Print(1, "Get Clones Arrays", StudyName);

    vector<HFile *> Files = GetFiles(StudyName);

    HClonesArray *ClonesArrays;

    if (Files.front()->GetTreeName() == "Delphes") {

        if (Files.front()->Snowmass) {

            ClonesArrays = new HDelphes::HClonesArraySnowmass();

        } else {

          ClonesArrays = new HDelphes::HClonesArray();

        }

    } else if (Files.front()->GetTreeName() == "LHEF") {

        ClonesArrays = new HParton::HClonesArray();

    } else if (Files.front()->GetTreeName() == "LHCO") {

        ClonesArrays = new HPgs::HClonesArray();

    } else {

        Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }

    DeleteFiles(Files);

    return ClonesArrays;

}

Analysis::HEvent *Analysis::HAnalysis::GetEvent(const string StudyName) const
{

    Print(1, "Get Event");

    vector<HFile *> Files = GetFiles(StudyName);

    HEvent *Event;

    if (Files.front()->GetTreeName() == "Delphes") {

      Event = new HDelphes::HEvent();

    } else if (Files.front()->GetTreeName() == "LHEF") {

        Event = new HParton::HEvent();

    } else if (Files.front()->GetTreeName() == "LHCO") {

        Event = new HPgs::HEvent();

    } else {

        Print(0, "unknown Tree String", Files.front()->GetTreeName());

    }

    DeleteFiles(Files);

    return Event;

}

TFile *Analysis::HAnalysis::GetExportFile(const string StudyName) const
{

    const string ExportName = GetProjectName() + "/" + StudyName + ".root";

    Print(1, "ExportFile", ExportName);

    return (new TFile(ExportName.c_str(), "Recreate"));

}


ExRootTreeWriter *Analysis::HAnalysis::GetTreeWriter(TFile *const ExportFile, const string ExportTreeName)
{

    Print(1, "Get Tree Writer", ExportTreeName.c_str());

    ExRootTreeWriter *const TreeWriter = new ExRootTreeWriter(ExportFile, ExportTreeName.c_str());

    NewBranches(TreeWriter);

    return TreeWriter;

}


ExRootTreeReader *Analysis::HAnalysis::GetTreeReader(const HFile *const File, HClonesArray *const ClonesArrays)
{

    Print(1, "Get Tree Reader",File->GetFilePath());

    // Import file
    const string ImportPath = File->GetFilePath();
    TFile * const ImportFile = new TFile(ImportPath.c_str());
//     TFile ImportFile = TFile(ImportPath.c_str());
    Print(1, "File", ImportPath);

    // Import tree
    const string ImportTreeName = File->GetTreeName();
    TTree * const ImportTree = (TTree *)ImportFile->Get(ImportTreeName.c_str());
//     TTree ImportTree = (TTree)ImportFile.Get(ImportTreeName.c_str());
    Print(1, "Tree", ImportTreeName);

    // TreeReader
    ExRootTreeReader * const TreeReader = new ExRootTreeReader(ImportTree);

    ClonesArrays->GetBranches(TreeReader);

//     delete ImportFile; // FIXME Possible?
//     delete ImportTree; // FIXME Possible?

    return TreeReader;

}


Analysis::HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

}

void Analysis::HAnalysis::DeleteFiles(const std::vector< HFile * > Files) const
{

    for (const auto * File : Files) {

        delete File;

    }

}
