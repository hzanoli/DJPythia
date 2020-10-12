#include "../include/djp_data_model/particle.h"

djpythia::data_model::Particle::Particle(double px, double py, double pz,
                                         double vertex_x, double vertex_y,
                                         double vertex_z, double eta, double phi,
                                         int pdg_code,
                                         djpythia::data_model::HFSource origin)
    : px_(px), py_(py), pz_(pz), vertex_x_(vertex_x), vertex_y_(vertex_y),
      vertex_z_(vertex_z), eta_(eta), phi_(phi), pdg_code_(pdg_code),
      origin_(origin) {}
