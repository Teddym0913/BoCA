#
# Copyright (C) 2015-2016 Jan Hajer
#
create_dictionary(ExRoot ExRootClasses.cc ExRootClasses.h ExRootAnalysisLinkDef.h exroot)

set(EventExRootSources
Partons.cpp
Leptons.cpp
Hadrons.cpp
)
create_library(EventExRoot EventExRootSources)
