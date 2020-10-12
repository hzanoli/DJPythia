#ifndef DJPYTHIA_PYTHIA_ANALYSIS_PYTHIA_ANALYSIS_H_
#define DJPYTHIA_PYTHIA_ANALYSIS_PYTHIA_ANALYSIS_H_

#include "Pythia8/Pythia.h"
#include "djp_data_model/origin.h"
#include "djp_data_model/particle.h"

namespace djpythia {
namespace pythia_analysis {

/* Given an event and a list of the position of the particles in this event,
 * finds their mothers, recursively. Returns a vector with the position of
 * all the chain of mother of the given particles.
 */
std::vector<int> FindMothers(const Pythia8::Event &event,
                             const std::vector<int> &positions);

/* Receives an event and the position of one particle in this event as input and
 * checks the source of this particle in the event.
 * Returns kCharm if this particle comes from charm, kBeauty if it comes from
 * beauty or kNone otherwise. */
djpythia::data_model::HFSource CheckSource(const Pythia8::Event &event,
                                           int position);

djpythia::data_model::Particle MakeParticle(const Pythia8::Particle &particle,
                                            const Pythia8::Event &event);

} // namespace pythia_analysis
} // namespace djpythia

#endif // DJPYTHIA_PYTHIA_ANALYSIS_PYTHIA_ANALYSIS_H_
