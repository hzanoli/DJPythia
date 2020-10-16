#ifndef DJPYTHIA_DATA_MODEL_PARTICLE_H_
#define DJPYTHIA_DATA_MODEL_PARTICLE_H_
#include <cmath>

#include "TObject.h"
#include "origin.h"

namespace djpythia {
namespace data_model {
/* Class to represent a particle in the simulation. The variables called "p" are
 * a reference to the momentum of the particle. */
class Particle : public TObject {
public:
  /* Constructs a particle from the provided information. */
  Particle(float px, float py, float pz, float eta, float phi, int pdg_code,
           float vertex_x, float vertex_y, float vertex_z, float vertex_t,
           HFSource origin);

  /* Default constructor. Creates an empty particle. */
  Particle() = default;

  float Px() const { return px_; }
  float Py() const { return py_; }
  float Pz() const { return pz_; }
  float Pt() const { return std::sqrt(Px() * Px() + Py() * Py()); };
  float P() const {
    return std::sqrt(Px() * Px() + Py() * Py() + Pz() * Pz());
  };

  float VertexX() const { return vertex_x_; }
  float VertexY() const { return vertex_y_; }
  float VertexZ() const { return vertex_z_; }
  float VertexT() const { return vertex_t_; }
  std::vector<float> Vertex() const {
    return {VertexX(), VertexY(), VertexZ()};
  };

  float Eta() const { return eta_; }
  float Phi() const { return phi_; }
  int PdgCode() const { return pdg_code_; }
  HFSource Origin() const { return origin_; }

private:
  float px_{-999.};
  float py_{-999.};
  float pz_{-999.};

  float eta_{-999.};
  float phi_{-999.};

  float vertex_x_{-999.};
  float vertex_y_{-999.};
  float vertex_z_{-999.};
  float vertex_t_{-999.};

  int pdg_code_{-999};
  HFSource origin_{HFSource::kNone};

  ClassDef(Particle, 1);
};

} // namespace data_model
} // namespace djpythia

#endif // DJPYTHIA_DATA_MODEL_PARTICLE_H_
