#include "../include/djp_data_model/particle.h"

ClassImp(djpythia::data_model::Particle)
    djpythia::data_model::Particle::Particle(float px, float py, float pz,
                                             float eta, float phi, int pdg_code,
                                             float vertex_x, float vertex_y,
                                             float vertex_z, float vertex_t,
                                             HFSource origin)
    : px_(px), py_(py), pz_(pz), eta_(eta), phi_(phi), vertex_x_(vertex_x),
      vertex_y_(vertex_y), vertex_z_(vertex_z), vertex_t_(vertex_t),
      pdg_code_(pdg_code), origin_(origin) {}
