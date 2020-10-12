#include "d_meson.h"

#include <utility>
namespace dm = djpythia::data_model;

dm::DMeson::DMeson(const djpythia::data_model::Particle& particle,
                   std::vector<Particle> daughters)
    : Particle(particle), daughters_(std::move(daughters)) {}
