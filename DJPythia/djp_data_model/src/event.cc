
#include "../include/djp_data_model/event.h"

#include <utility>
ClassImp(djpythia::data_model::Event)

djpythia::data_model::Event::Event(std::vector<DMeson> dmesons)
    : dmesons_(std::move(dmesons)) {}
