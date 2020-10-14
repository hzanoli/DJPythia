#include "../include/djp_data_model/d_meson.h"

#include <cmath>
#include <utility>
namespace dm = djpythia::data_model;

ClassImp(dm::DMeson)

    dm::DMeson::DMeson(const djpythia::data_model::Particle &particle,
                       std::vector<Particle> daughters)
    : Particle(particle), daughters_(std::move(daughters)) {}

double dm::DMeson::DecayLength() const {
  if (Daughters().empty())
    return -999;

  auto d_vertex = Vertex();
  auto daughter_vertex = Daughters()[0].Vertex();

  return std::sqrt(std::pow(d_vertex[0] - daughter_vertex[0], 2) +
                   std::pow(d_vertex[1] - daughter_vertex[1], 2) +
                   std::pow(d_vertex[2] - daughter_vertex[2], 2));
}