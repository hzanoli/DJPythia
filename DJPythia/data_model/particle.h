#ifndef DJPYTHIA_DATA_MODEL_PARTICLE_H_
#define DJPYTHIA_DATA_MODEL_PARTICLE_H_
#include "origin.h"

namespace djpythia {
namespace data_model {
/* Class to represent a particle in the simulation. The variables called "p" are
 * a reference to the momentum of the particle. */
class Particle {
public:
  /* Constructs a particle from the provided information. */
  Particle(double px, double py, double pz, double vertex_x, double vertex_y,
           double vertex_z, double eta, double phi, int pdg_code, HFSource origin);

  /* Default constructor. Creates an empty particle. */
  Particle() = default;

  double Px() const { return px_; }
  double Py() const { return py_; }
  double Pz() const { return pz_; }

  double VertexX() const { return vertex_x_; }
  double VertexY() const { return vertex_y_; }
  double VertexZ() const { return vertex_z_; }

  double Eta() const { return eta_; }
  double Phi() const { return phi_; }
  int PdgCode() const { return pdg_code_; }
  HFSource Origin() const { return origin_; }

private:
  double px_{-999.};
  double py_{-999.};
  double pz_{-999.};

  double vertex_x_{-999.};
  double vertex_y_{-999.};
  double vertex_z_{-999.};

  double eta_{-999.};
  double phi_{-999.};

  int pdg_code_{-999};
  HFSource origin_{HFSource::kNone};
};

} // namespace data_model
} // namespace djpythia

#endif // DJPYTHIA_DATA_MODEL_PARTICLE_H_
