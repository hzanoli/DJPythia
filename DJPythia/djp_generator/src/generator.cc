#include "djp_generate/generator.h"

#include <utility>
djpythia::generator::PythiaGenerator::PythiaGenerator(std::string config_file,
                                                      int seed, int n_events)
    : pythia_(),
      config_file_(std::move(config_file)),
      seed_(seed),
      n_events_(n_events) {
  pythia_.readFile(config_file_);
  pythia_.readString("Random:setSeed = on");
  pythia_.readString("Random:seed = " + std::to_string(seed));
  pythia_.init();
}

djpythia::generator::PythiaGenerator::Iterator::Iterator(
    djpythia::generator::PythiaGenerator& generator, long int position):
    generator_{&generator}, position_{position}{}
