# include "HOctet.hh"
// # include "HTagPrivate.hh"

HOctet::HOctet(const analysis::HSextet &NewSextet, const analysis::Doublet &Newdoublet)
{
    SextetM = NewSextet;
    doubletM = Newdoublet;
    SetBdt(SextetM.Bdt(),doubletM.Bdt());
    SetTag(SextetM.Tag(),doubletM.Tag());
}

// HOctet::HOctet(const analysis::HSextet &NewSextet, const analysis::Doublet &Newdoublet, const EventStruct &Newevent_struct)
// {
//     SextetM = NewSextet;
//     doubletM = Newdoublet;
//     event_structM = Newevent_struct;
//     SetBdt(SextetM.Bdt(),doubletM.Bdt());
//     SetTag(SextetM.Tag(),doubletM.Tag());
// }
