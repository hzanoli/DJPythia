#ifndef DJPYTHIA_DATA_MODEL_D_MESON_H_
#define DJPYTHIA_DATA_MODEL_D_MESON_H_
#include <vector>

#include "particle.h"

namespace djpythia {
namespace data_model {
class DMeson : public Particle {
public:
  /* Constructs a D meson from a given a particle and a vector with its
   * daughters. */
  DMeson(const Particle &particle, std::vector<Particle> daughters);

  /* Constructs an empty D meson */
  DMeson() : Particle(), daughters_(){};

  const std::vector<Particle> &Daughters() const { return daughters_; }

  double DecayLength() const;

private:
  std::vector<Particle> daughters_;
  ClassDef(DMeson, 1);
};

} // namespace data_model
} // namespace djpythia

#endif // DJPYTHIA_DATA_MODEL_D_MESON_H_
