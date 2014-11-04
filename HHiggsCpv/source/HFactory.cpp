# include "HMvaHiggsCpv.hh"
# include "HFactory.hh"

int main()
{
  hanalysis::HMva *Mva = new hhiggscpv::HMva();

    hanalysis::HFactory *Factory = new hanalysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
