#ifndef DJPYTHIA_DATA_MODEL_EVENT_H_
#define DJPYTHIA_DATA_MODEL_EVENT_H_
#include <vector>

#include "TObject.h"

#include "d_meson.h"

namespace djpythia {
namespace data_model {
class Event : public TObject {
  std::vector<DMeson> dmesons_;

public:
  /* Create an event from a vector of D mesons. */
  explicit Event(std::vector<DMeson> dmesons);

  Event() = default;

  const std::vector<DMeson> &Dmesons() const { return dmesons_; }

  ClassDef(Event, 1);
};
} // namespace data_model
} // namespace djpythia

#endif // DJPYTHIA_DATA_MODEL_EVENT_H_
