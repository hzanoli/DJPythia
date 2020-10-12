#include "djp_generate/pythia_analysis.h"

namespace dm = djpythia::data_model;

namespace djpythia {
namespace pythia_analysis {
std::vector<int> FindMothers(const Pythia8::Event &event,
                             const std::vector<int> &positions) {
  std::vector<int> list_mothers;
  list_mothers.reserve(event.size());

  for (auto no : positions) {
    auto mothers_current_particle = event[no].motherList();

    list_mothers.insert(list_mothers.end(), mothers_current_particle.begin(),
                        mothers_current_particle.end());

    auto mother_of_mothers = FindMothers(event, mothers_current_particle);

    list_mothers.insert(list_mothers.end(), mother_of_mothers.begin(),
                        mother_of_mothers.end());
  }

  list_mothers.shrink_to_fit();

  return list_mothers;
}

djpythia::data_model::HFSource CheckSource(const Pythia8::Event &event,
                                           int position) {
  auto mother_list = FindMothers(event, {position});

  for (auto mother_no : mother_list) {
    int id = event[mother_no].idAbs();
    if (id == 5)
      return dm::HFSource::kBeauty;
  }

  for (auto mother_no : mother_list) {
    int id = event[mother_no].idAbs();
    if (id == 4)
      return dm::HFSource::kBeauty;
  }

  return dm::HFSource::kNone;
}

djpythia::data_model::Particle MakeParticle(const Pythia8::Particle &particle,
                                            const Pythia8::Event &event) {
  return {particle.px(),    particle.py(),
          particle.pz(),    particle.xProd(),
          particle.yProd(), particle.zProd(),
          particle.eta(),   particle.phi(),
          particle.id(),    CheckSource(event, particle.index())};
}
} // namespace pythia_analysis
} // namespace djpythia
