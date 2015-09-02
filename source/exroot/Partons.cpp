#include "exroot/Partons.hh"

#include "exroot/ExRootAnalysis.hh"
#include "ParticleInfo.hh"
#include "Types.hh"
#include "Debug.hh"

namespace boca {

namespace exroot {

Jets Partons::Particles() const
{
    return Particles(Status::stable);
}

Jets Partons::GenParticles() const
{
    return Particles(Status::generator);
}

Jets Partons::Particles(Status max_status) const
{
    Info(clones_arrays().ParticleSum());
    Jets particles;
    for (auto const& particle_number : Range(clones_arrays().ParticleSum())) {
        TRootLHEFParticle& particle = static_cast<TRootLHEFParticle&>(clones_arrays().Particle(particle_number));
        if (particle.Status < to_int(max_status)) break;
        Family family(particle.PID);
//         Constituent constituent(LorentzVector(particle), family);
        fastjet::PseudoJet jet = PseudoJet(particle);
        jet.set_user_info(new ParticleInfo(family));
        particles.emplace_back(jet);
    }
    return particles;
}

}

}
