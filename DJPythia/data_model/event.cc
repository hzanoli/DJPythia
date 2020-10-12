
#include "event.h"

#include <utility>
djpythia::data_model::Event::Event(std::vector<DMeson> dmesons)
    : dmesons_(std::move(dmesons)) {}
