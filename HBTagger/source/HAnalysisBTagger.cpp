# include "HAnalysisBTagger.hh"


void hbtagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag Tag)
{
    Print(HNotification, "Set File Vector", Tag);

//     std::vector<hanalysis::HFile> SignalFiles;
//     std::vector<hanalysis::HFile> BackgroundFiles;

    NewSignalFile(bb);
//     NewSignalFile(Hbb);
//     NewSignalFile(ttbb);
//     NewSignalFile(ttlep);
//     NewSignalFile(tthad);
//     NewSignalFile(tt);

//     NewBackgroundFile(bb);
    NewBackgroundFile(cc);
//     NewBackgroundFile(jj);
//     NewBackgroundFile(tt);
//         NewBackgroundFile(ttcc);
//         NewBackgroundFile(ttjj);
    NewBackgroundFile(qq);
    NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
//     NewBackgroundFile(ww);

//     std::vector<hanalysis::HFile> NewFiles;

//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SignalFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = BackgroundFiles;
//             break;
//         }


//     NewFiles.front().SetBasePath("~/Projects/BTagging/"); // FIXME implement this info
//     NewFiles.front().SetFileSuffix(".root"); // FIXME implement this info
//     SetTrees();
//     return NewFiles;
}


// void hbtagger::HAnalysis::SetTrees()
// {
//
//     HStrings SignalTrees {
//         TreeName(bb),
// //         TreeName(Hbb),
// //         TreeName(ttbb),
// //         TreeName(ttlep),
// //         TreeName(tthad),
//     };
//
//     HStrings BackgroundTrees {
// //         TreeName(bb),
//         TreeName(cc),
// //         TreeName(jj),
// //         TreeName(tt),
//         TreeName(qq),
//         TreeName(gg),
// //         TreeName(hh),
// //         TreeName(ww),
// //         TreeName(ttcc),
// //         TreeName(ttjj),
//     };
//
//     tagger_.SetSignalTreeNames(SignalTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundTrees);
//
// }



bool hbtagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{
    Print(HInformation, "Analysis");
    ++event_sum_;
    return tagger_.GetBranches(event, stage, tag);
}
